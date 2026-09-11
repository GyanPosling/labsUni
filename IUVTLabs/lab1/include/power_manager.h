
#pragma once

#include <QObject>
#include <QDateTime>
#include <QList>
#include <QString>
#include <QStringList>
#include <QAbstractNativeEventFilter>
#include <windows.h>

struct PowerInfo
{
    bool acConnected = false;
    bool charging = false;
    int batteryPercent = -1;
    qint64 remainingSeconds = -1;

    QString batteryType = "Неизвестно";
    qint64 designedCapacityMWh = -1;
    qint64 fullChargeCapacityMWh = -1;
    int wearPercent = -1;

    bool sleepSupported = false;
    bool modernStandbySupported = false;
    bool hibernateSupported = false;
};

struct LogEntry
{
    QDateTime time;
    QString type;
    QString message;
};

class PowerManager final : public QObject, public QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    explicit PowerManager(QObject *parent = nullptr);
    ~PowerManager() override;

    const PowerInfo &info() const;
    const QList<LogEntry> &log() const;

    bool sleep();
    bool hibernate();

    bool isAutostartEnabled() const;
    bool enableAutostart();
    bool setAutostartEnabled(bool enabled);

    void setWindowHandle(HWND hwnd);

    bool nativeEventFilter(const QByteArray &eventType,
                           void *message,
                           qintptr *result) override;

public slots:
    void update();

signals:
    void informationChanged();
    void newLogEntry();

private:
    void registerPowerNotifications();
    void unregisterPowerNotifications();

    void addLog(const QString &type, const QString &message);
    void appendLogToFile(const LogEntry &entry);

    bool readBatteryDetails(PowerInfo &info) const;
    bool enableShutdownPrivilege();

    PowerInfo m_info;
    QList<LogEntry> m_log;

    HWND m_window = nullptr;
    HPOWERNOTIFY m_acdcNotification = nullptr;
    HPOWERNOTIFY m_batteryNotification = nullptr;
    HPOWERNOTIFY m_savingNotification = nullptr;
    HPOWERNOTIFY m_monitorNotification = nullptr;
    HPOWERNOTIFY m_suspendResumeNotification = nullptr;

    enum class PowerTransition
    {
        None,
        Sleep,
        Hibernate
    };

    PowerTransition m_transition = PowerTransition::None;
    bool m_transitionLogged = false;
    bool m_sleepSessionActive = false;
    bool m_suspendConfirmed = false;
};
