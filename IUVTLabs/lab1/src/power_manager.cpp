#include "power_manager.h"

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QSettings>
#include <QStandardPaths>
#include <QTextStream>
#include <QTimer>

#include <powrprof.h>
#include <setupapi.h>
#include <batclass.h>

static const GUID kGuidPowerSavingStatus =
    {0xE00958C0, 0xC213, 0x4ACE,
     {0xAC, 0x77, 0xFE, 0xCC, 0xED, 0x2E, 0xEE, 0xA5}};

static const GUID kGuidBatteryDeviceClass =
    {0x72631E54, 0x78A4, 0x11D0,
     {0xBC, 0xF7, 0x00, 0xAA, 0x00, 0xB7, 0xB3, 0x2A}};

HPOWERNOTIFY registerSuspendResumeNotification(HWND hwnd)  // Регистрирует уведомления о переходе системы в сон и выходе из него

{
    HMODULE user32 = GetModuleHandleW(L"user32.dll");
    if (!user32)
        return nullptr;

    using RegisterFn = HPOWERNOTIFY (WINAPI *)(HANDLE, DWORD);
    auto fn = reinterpret_cast<RegisterFn>(
        GetProcAddress(user32, "RegisterSuspendResumeNotification"));

    return fn
        ? fn(hwnd, DEVICE_NOTIFY_WINDOW_HANDLE)
        : nullptr;
}

void unregisterSuspendResumeNotification(HPOWERNOTIFY handle)   // Отменяет регистрацию уведомлений о переходе системы в сон и выходе из него
{
    if (!handle)
        return;

    HMODULE user32 = GetModuleHandleW(L"user32.dll");
    if (!user32)
        return;

    using UnregisterFn = BOOL (WINAPI *)(HPOWERNOTIFY);
    auto fn = reinterpret_cast<UnregisterFn>(
        GetProcAddress(user32, "UnregisterSuspendResumeNotification"));

    if (fn)
        fn(handle);
}

#pragma comment(lib, "PowrProf.lib")
#pragma comment(lib, "Setupapi.lib")
#pragma comment(lib, "Advapi32.lib")

namespace
{
QString logFilePath()   // Возвращает путь к файлу журнала приложения
{
    const QString dir =
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    QDir().mkpath(dir);
    return QDir(dir).filePath("power.log");
}
}

PowerManager::PowerManager(QObject *parent)     // Создаёт менеджер энергопитания и запускает первое обновление информации
    : QObject(parent)
{
    QCoreApplication::instance()->installNativeEventFilter(this);
    update();
}

PowerManager::~PowerManager()   // Освобождает ресурсы и отключает обработку системных сообщений
{
    unregisterPowerNotifications();
    QCoreApplication::instance()->removeNativeEventFilter(this);
}

const PowerInfo &PowerManager::info() const     // Возвращает текущую информацию о состоянии энергопитания
{
    return m_info;
}

const QList<LogEntry> &PowerManager::log() const    // Возвращает список записей журнала
{
    return m_log;
}

void PowerManager::setWindowHandle(HWND hwnd)       // Устанавливает дескриптор окна и регистрирует уведомления Windows
{
    unregisterPowerNotifications();
    m_window = hwnd;
    registerPowerNotifications();
}

void PowerManager::registerPowerNotifications()     // Регистрирует уведомления Windows об изменениях состояния питания
{
    if (!m_window)
        return;

    m_acdcNotification = RegisterPowerSettingNotification(
        m_window,
        &GUID_ACDC_POWER_SOURCE,
        DEVICE_NOTIFY_WINDOW_HANDLE);

    m_batteryNotification = RegisterPowerSettingNotification(
        m_window,
        &GUID_BATTERY_PERCENTAGE_REMAINING,
        DEVICE_NOTIFY_WINDOW_HANDLE);

    m_savingNotification = RegisterPowerSettingNotification(
        m_window,
        &kGuidPowerSavingStatus,
        DEVICE_NOTIFY_WINDOW_HANDLE);

    m_monitorNotification = RegisterPowerSettingNotification(
        m_window,
        &GUID_MONITOR_POWER_ON,
        DEVICE_NOTIFY_WINDOW_HANDLE);

    m_suspendResumeNotification =
        registerSuspendResumeNotification(m_window);
}

void PowerManager::unregisterPowerNotifications()       // Отменяет все ранее зарегистрированные уведомления Windows
{
    if (m_acdcNotification) {
        UnregisterPowerSettingNotification(m_acdcNotification);
        m_acdcNotification = nullptr;
    }

    if (m_batteryNotification) {
        UnregisterPowerSettingNotification(m_batteryNotification);
        m_batteryNotification = nullptr;
    }

    if (m_savingNotification) {
        UnregisterPowerSettingNotification(m_savingNotification);
        m_savingNotification = nullptr;
    }

    if (m_monitorNotification) {
        UnregisterPowerSettingNotification(m_monitorNotification);
        m_monitorNotification = nullptr;
    }

    if (m_suspendResumeNotification) {
        unregisterSuspendResumeNotification(m_suspendResumeNotification);
        m_suspendResumeNotification = nullptr;
    }
}

void PowerManager::update()     // Получает актуальное состояние питания и батареи
{
    SYSTEM_POWER_STATUS status{};

    if (!GetSystemPowerStatus(&status))
        return;

    const PowerInfo old = m_info;

    m_info.acConnected = status.ACLineStatus == 1;
    m_info.charging = (status.BatteryFlag & 8) != 0;
    m_info.batteryPercent =
        status.BatteryLifePercent == 255
            ? -1
            : static_cast<int>(status.BatteryLifePercent);

    m_info.remainingSeconds =
        status.BatteryLifeTime == DWORD(-1)
            ? -1
            : static_cast<qint64>(status.BatteryLifeTime);

    SYSTEM_POWER_CAPABILITIES capabilities{};
    if (GetPwrCapabilities(&capabilities)) {
        m_info.modernStandbySupported =
            !capabilities.SystemS1 &&
            !capabilities.SystemS2 &&
            !capabilities.SystemS3;
        m_info.sleepSupported = m_info.modernStandbySupported ||
                                capabilities.SystemS1 ||
                                capabilities.SystemS2 ||
                                capabilities.SystemS3;

        m_info.hibernateSupported =
            capabilities.SystemS4 &&
            capabilities.HiberFilePresent;
    }

    readBatteryDetails(m_info);

    if (old.batteryPercent >= 0 &&
        m_info.batteryPercent != old.batteryPercent) {
        addLog(
            "Изменение заряда",
            QString("Уровень заряда: %1% -> %2%")
                .arg(old.batteryPercent)
                .arg(m_info.batteryPercent));
    }

    if (old.acConnected != m_info.acConnected) {
        addLog(
            "Подключение ЗУ",
            m_info.acConnected
                ? "Зарядное устройство подключено"
                : "Зарядное устройство отключено");
    }

    emit informationChanged();
}

bool PowerManager::enableShutdownPrivilege()    // Получает привилегию Windows для выполнения операций с питанием
{
    HANDLE token = nullptr;

    if (!OpenProcessToken(
            GetCurrentProcess(),
            TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
            &token)) {
        return false;
    }

    LUID luid{};

    if (!LookupPrivilegeValueW(
            nullptr,
            SE_SHUTDOWN_NAME,
            &luid)) {
        CloseHandle(token);
        return false;
    }

    TOKEN_PRIVILEGES privileges{};
    privileges.PrivilegeCount = 1;
    privileges.Privileges[0].Luid = luid;
    privileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    SetLastError(ERROR_SUCCESS);

    const BOOL ok = AdjustTokenPrivileges(
        token,
        FALSE,
        &privileges,
        sizeof(privileges),
        nullptr,
        nullptr);

    const bool success = ok && GetLastError() == ERROR_SUCCESS;

    CloseHandle(token);
    return success;
}

bool PowerManager::sleep()      // Переводит компьютер в спящий режим
{
    m_transition = PowerTransition::Sleep;
    m_transitionLogged = false;
    m_sleepSessionActive = true;
    m_suspendConfirmed = false;

    addLog(
        "Переход в сон",
        "Система переходит в спящий режим");
    m_transitionLogged = true;

    if (!m_info.sleepSupported) {
        m_transition = PowerTransition::None;
        m_transitionLogged = false;
        m_sleepSessionActive = false;
        return false;
    }

    if (!enableShutdownPrivilege()) {
        m_transition = PowerTransition::None;
        m_transitionLogged = false;
        m_sleepSessionActive = false;
        return false;
    }

    const BOOL success = SetSuspendState(
        FALSE,
        FALSE,
        FALSE);

    if (!success) {
        m_transition = PowerTransition::None;
        m_transitionLogged = false;
        m_sleepSessionActive = false;
    }

    return success != FALSE;
}

bool PowerManager::hibernate()  // Переводит компьютер в режим гибернации
{
    m_transition = PowerTransition::Hibernate;
    m_transitionLogged = false;
    m_sleepSessionActive = true;
    m_suspendConfirmed = false;

    if (!m_info.hibernateSupported) {
        m_transition = PowerTransition::None;
        m_sleepSessionActive = false;
        return false;
    }

    if (!enableShutdownPrivilege()) {
        m_transition = PowerTransition::None;
        m_sleepSessionActive = false;
        return false;
    }

    addLog(
        "Гибернация",
        "Система переходит в режим гибернации");
    m_transitionLogged = true;

    const BOOL success = SetSuspendState(
        TRUE,
        FALSE,
        FALSE);

    if (!success) {
        m_transition = PowerTransition::None;
        m_transitionLogged = false;
    }

    return success != FALSE;
}

bool PowerManager::enableAutostart()
{
    return setAutostartEnabled(true);
}

bool PowerManager::isAutostartEnabled() const
{
    QSettings settings(
        "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run",
        QSettings::NativeFormat);

    const QString applicationPath =
        QDir::toNativeSeparators(
            QCoreApplication::applicationFilePath());

    const QString expectedValue =
        QString("\"%1\"").arg(applicationPath);

    return settings.value("PowerMonitorA4").toString() == expectedValue;
}

bool PowerManager::setAutostartEnabled(bool enabled)
{
    QSettings settings(
        "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run",
        QSettings::NativeFormat);

    const QString applicationPath =
        QDir::toNativeSeparators(
            QCoreApplication::applicationFilePath());

    if (enabled) {
        settings.setValue(
            "PowerMonitorA4",
            QString("\"%1\"").arg(applicationPath));
    } else {
        settings.remove("PowerMonitorA4");
    }

    settings.sync();

    return settings.status() == QSettings::NoError;
}

void PowerManager::addLog(      // Создаёт новую запись журнала и сохраняет её в память и файл
    const QString &type,
    const QString &message)
{
    const LogEntry entry{
        QDateTime::currentDateTime(),
        type,
        message
    };

    m_log.append(entry);
    appendLogToFile(entry);

    emit newLogEntry();
}

void PowerManager::appendLogToFile(const LogEntry &entry)       // Добавляет запись события в текстовый файл журнала
{
    QFile file(logFilePath());

    if (!file.open(QIODevice::Append | QIODevice::Text))
        return;

    QTextStream stream(&file);

    stream << entry.time.toString("yyyy-MM-dd HH:mm:ss")
           << " | "
           << entry.type
           << " | "
           << entry.message
           << '\n';
}

bool PowerManager::readBatteryDetails(PowerInfo &info) const        // Получает характеристики аккумулятора через системный интерфейс Windows.
{
    HDEVINFO devices = SetupDiGetClassDevs(
        &kGuidBatteryDeviceClass,
        nullptr,
        nullptr,
        DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

    if (devices == INVALID_HANDLE_VALUE)
        return false;

    SP_DEVICE_INTERFACE_DATA interfaceData{};
    interfaceData.cbSize = sizeof(interfaceData);

    bool found = false;

    for (DWORD index = 0;
         SetupDiEnumDeviceInterfaces(
             devices,
             nullptr,
             &kGuidBatteryDeviceClass,
             index,
             &interfaceData);
         ++index) {

        DWORD required = 0;

        SetupDiGetDeviceInterfaceDetailW(
            devices,
            &interfaceData,
            nullptr,
            0,
            &required,
            nullptr);

        if (required == 0)
            continue;

        QByteArray buffer(static_cast<int>(required), '\0');

        auto *detail =
            reinterpret_cast<SP_DEVICE_INTERFACE_DETAIL_DATA_W *>(
                buffer.data());

        detail->cbSize =
            sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA_W);

        if (!SetupDiGetDeviceInterfaceDetailW(
                devices,
                &interfaceData,
                detail,
                required,
                nullptr,
                nullptr)) {
            continue;
        }

        HANDLE battery = CreateFileW(
            detail->DevicePath,
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            nullptr,
            OPEN_EXISTING,
            0,
            nullptr);

        if (battery == INVALID_HANDLE_VALUE)
            continue;

        DWORD tag = 0;
        DWORD bytesReturned = 0;

        if (!DeviceIoControl(
                battery,
                IOCTL_BATTERY_QUERY_TAG,
                nullptr,
                0,
                &tag,
                sizeof(tag),
                &bytesReturned,
                nullptr)) {

            CloseHandle(battery);
            continue;
        }

        BATTERY_QUERY_INFORMATION query{};
        query.BatteryTag = tag;
        query.InformationLevel = BatteryInformation;

        BATTERY_INFORMATION batteryInfo{};

        if (DeviceIoControl(
                battery,
                IOCTL_BATTERY_QUERY_INFORMATION,
                &query,
                sizeof(query),
                &batteryInfo,
                sizeof(batteryInfo),
                &bytesReturned,
                nullptr)) {

            info.designedCapacityMWh =
                static_cast<qint64>(batteryInfo.DesignedCapacity);

            info.fullChargeCapacityMWh =
                static_cast<qint64>(batteryInfo.FullChargedCapacity);

            if (info.designedCapacityMWh > 0 &&
                info.fullChargeCapacityMWh >= 0) {

                const double health =
                    100.0 *
                    static_cast<double>(info.fullChargeCapacityMWh) /
                    static_cast<double>(info.designedCapacityMWh);

                info.wearPercent =
                    qBound(0, 100 - qRound(health), 100);
            }

            info.batteryType =
                batteryInfo.Technology == 1
                    ? "Перезаряжаемая"
                    : "Неперезаряжаемая";

            found = true;
        }

        CloseHandle(battery);

        if (found)
            break;
    }

    SetupDiDestroyDeviceInfoList(devices);
    return found;
}

bool PowerManager::nativeEventFilter(
    const QByteArray &eventType,
    void *message,
    qintptr *result)
{
    Q_UNUSED(result);

    if (eventType != "windows_generic_MSG" &&
        eventType != "windows_dispatcher_MSG") {
        return false;
    }

    auto *msg = static_cast<MSG *>(message);

    if (!msg || msg->message != WM_POWERBROADCAST)
        return false;

    switch (msg->wParam) {
    case PBT_APMPOWERSTATUSCHANGE:
        update();
        break;

    case PBT_APMSUSPEND:

        if (m_sleepSessionActive) {
            m_suspendConfirmed = true;
        }
        break;

    case PBT_APMRESUMEAUTOMATIC:

        break;

    case PBT_APMRESUMESUSPEND:

        if (m_sleepSessionActive && m_suspendConfirmed) {
            m_sleepSessionActive = false;

            const bool wasHibernate =
                m_transition == PowerTransition::Hibernate;

            addLog(
                wasHibernate ? "Гибернация" : "Переход в сон",
                wasHibernate
                    ? "Система возобновила работу после гибернации"
                    : "Система возобновила работу");

            m_transition = PowerTransition::None;
            m_transitionLogged = false;
            m_suspendConfirmed = false;


            QTimer::singleShot(1000, this, &PowerManager::update);
        }
        break;

    case PBT_POWERSETTINGCHANGE:
    {
        auto *setting =
            reinterpret_cast<POWERBROADCAST_SETTING *>(
                msg->lParam);

        if (!setting)
            break;

        if (IsEqualGUID(
                setting->PowerSetting,
                GUID_ACDC_POWER_SOURCE)) {

            update();

        } else if (IsEqualGUID(
                       setting->PowerSetting,
                       GUID_BATTERY_PERCENTAGE_REMAINING)) {

            update();

        } else if (IsEqualGUID(
                       setting->PowerSetting,
                       kGuidPowerSavingStatus)) {

            update();
        } else if (IsEqualGUID(
                       setting->PowerSetting,
                       GUID_MONITOR_POWER_ON)) {

            const auto *data =
                reinterpret_cast<const DWORD *>(
                    reinterpret_cast<const BYTE *>(setting) +
                    sizeof(setting->PowerSetting));

            if (data && *data != 0) {

                if (m_sleepSessionActive && m_suspendConfirmed) {
                    m_sleepSessionActive = false;

                    const bool wasHibernate =
                        m_transition == PowerTransition::Hibernate;

                    addLog(
                        wasHibernate ? "Гибернация" : "Переход в сон",
                        wasHibernate
                            ? "Система возобновила работу после гибернации"
                            : "Система возобновила работу");

                    m_transition = PowerTransition::None;
                    m_transitionLogged = false;
                    m_suspendConfirmed = false;
                    QTimer::singleShot(1000, this, &PowerManager::update);
                }
            }
        }

        break;
    }

    default:
        break;
    }

    return false;
}
