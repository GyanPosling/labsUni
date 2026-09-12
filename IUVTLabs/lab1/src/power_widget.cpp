
#include "power_widget.h"
#include "log_window.h"

#include <QAction>
#include <QContextMenuEvent>
#include <QFont>
#include <QMenu>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPolygonF>
#include <QScreen>
#include <QTime>

PowerWidget::PowerWidget(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(300, 200);

    setWindowFlags(
        Qt::Window |
        Qt::FramelessWindowHint |
        Qt::WindowStaysOnTopHint);

    setAttribute(Qt::WA_TranslucentBackground);

    connect(
        &m_timer,
        &QTimer::timeout,
        this,
        &PowerWidget::refreshView);

    connect(
        &m_manager,
        &PowerManager::informationChanged,
        this,
        &PowerWidget::refreshView);

    m_timer.start(2000);

    m_manager.setWindowHandle(
        reinterpret_cast<HWND>(winId()));

    if (QScreen *screen = this->screen()) {
        const QRect available = screen->availableGeometry();
        move(available.center() - rect().center());
    }

    refreshView();
}

PowerWidget::~PowerWidget()
{
    delete m_logWindow;
}

QColor PowerWidget::colorForBattery(int percent) const
{
    if (percent < 0)
        return QColor("#64748b");

    if (percent < 20)
        return QColor("#ef4444");

    if (percent < 50)
        return QColor("#f59e0b");

    return QColor("#22c55e");
}

QString PowerWidget::remainingTime(qint64 seconds) const
{
    if (seconds < 0)
        return "Осталось: нет данных";

    const qint64 hours = seconds / 3600;
    const qint64 minutes = (seconds % 3600) / 60;

    if (hours > 0)
        return QString("Осталось: %1 ч %2 мин")
            .arg(hours)
            .arg(minutes);

    return QString("Осталось: %1 мин")
        .arg(minutes);
}

void PowerWidget::drawBatteryIcon(QPainter &painter, const QRectF &area, const PowerInfo &info) const
{
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing);

    const int percent = info.batteryPercent < 0
        ? 0
        : qBound(0, info.batteryPercent, 100);
    const QColor accent = colorForBattery(info.batteryPercent);

    painter.setPen(Qt::NoPen);
    QLinearGradient shadow(area.topLeft(), area.bottomRight());
    shadow.setColorAt(0.0, QColor(37, 47, 63, 180));
    shadow.setColorAt(1.0, QColor(8, 12, 19, 40));
    painter.setBrush(shadow);
    painter.drawRoundedRect(area.adjusted(0, 10, 0, -8), 14, 14);

    const QRectF body(area.left() + 10, area.top() + 34, area.width() - 28, 58);
    const QRectF cap(body.right() + 1, body.top() + 17, 10, 24);
    const QRectF fill = body.adjusted(8, 8, -8, -8);
    const QRectF filled(fill.left(),
                        fill.top(),
                        fill.width() * percent / 100.0,
                        fill.height());

    painter.setPen(QPen(QColor("#526071"), 3));
    painter.setBrush(QColor("#121923"));
    painter.drawRoundedRect(body, 9, 9);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#526071"));
    painter.drawRoundedRect(cap, 4, 4);

    QLinearGradient fillGradient(fill.topLeft(), fill.topRight());
    fillGradient.setColorAt(0.0, accent.darker(135));
    fillGradient.setColorAt(1.0, accent);
    painter.setBrush(fillGradient);
    painter.drawRoundedRect(filled, 5, 5);

    painter.setPen(QPen(QColor(255, 255, 255, 35), 1));
    painter.drawLine(QPointF(fill.left(), fill.top() + 7),
                     QPointF(fill.right(), fill.top() + 7));

    if (info.charging) {
        QPolygonF bolt;
        bolt << QPointF(body.center().x() + 3, body.top() + 8)
             << QPointF(body.center().x() - 15, body.center().y() + 3)
             << QPointF(body.center().x() - 1, body.center().y() + 3)
             << QPointF(body.center().x() - 9, body.bottom() - 5)
             << QPointF(body.center().x() + 17, body.center().y() - 2)
             << QPointF(body.center().x() + 3, body.center().y() - 2);
        painter.setBrush(QColor("#f8fafc"));
        painter.setPen(QPen(QColor("#020617"), 1));
        painter.drawPolygon(bolt);
    }

    QFont labelFont = font();
    labelFont.setPointSize(8);
    labelFont.setBold(true);
    painter.setFont(labelFont);
    painter.setPen(QColor("#94a3b8"));
    painter.drawText(QRectF(area.left(), area.bottom() - 24, area.width(), 18),
                     Qt::AlignCenter,
                     info.charging ? "CHARGING" : (info.acConnected ? "AC POWER" : "BATTERY"));

    painter.restore();
}

void PowerWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QLinearGradient background(rect().topLeft(), rect().bottomRight());
    background.setColorAt(0.0, QColor("#172033"));
    background.setColorAt(1.0, QColor("#070a10"));
    painter.setPen(QPen(QColor("#334155"), 1));
    painter.setBrush(background);
    painter.drawRoundedRect(rect().adjusted(1, 1, -1, -1), 14, 14);

    const PowerInfo &info = m_manager.info();

    drawBatteryIcon(painter, QRectF(10, 35, 82, 124), info);

    // Battery ring centered vertically between the top and bottom content boundaries.
    const QRectF circle(105, 58, 82, 82);
    QPen backgroundPen(QColor("#273244"), 8);
    backgroundPen.setCapStyle(Qt::RoundCap);
    painter.setPen(backgroundPen);
    painter.drawArc(circle, 90 * 16, -360 * 16);

    const int percent = info.batteryPercent < 0
        ? 0 : qBound(0, info.batteryPercent, 100);

    QPen valuePen(colorForBattery(info.batteryPercent), 8);
    valuePen.setCapStyle(Qt::RoundCap);
    painter.setPen(valuePen);
    painter.drawArc(circle, 90 * 16,
                    -static_cast<int>(360.0 * percent / 100.0 * 16.0));

    QFont percentFont = font();
    percentFont.setPointSize(16);
    percentFont.setBold(true);
    painter.setFont(percentFont);
    painter.setPen(QColor("#f8fafc"));
    painter.drawText(circle, Qt::AlignCenter,
                     info.batteryPercent >= 0
                         ? QString::number(info.batteryPercent) + "%"
                         : "—");

    // Three compact information rows, vertically centered in the widget.
    const qreal x = 197;
    QFont smallFont = font();
    smallFont.setPointSize(8);
    painter.setFont(smallFont);

    painter.setPen(QColor("#cbd5e1"));
    painter.drawText(QRectF(x, 62, 90, 18), Qt::AlignLeft | Qt::AlignVCenter,
                     info.charging ? "Заряжается" :
                     (info.acConnected ? "Питание: сеть" : "Питание: батарея"));

    painter.setPen(QColor("#94a3b8"));
    painter.drawText(QRectF(x, 85, 90, 18), Qt::AlignLeft | Qt::AlignVCenter,
                     remainingTime(info.remainingSeconds).replace("Осталось: ", ""));

    painter.drawText(QRectF(x, 108, 90, 18), Qt::AlignLeft | Qt::AlignVCenter,
                     QTime::currentTime().toString("HH:mm:ss"));

    painter.setPen(Qt::NoPen);
    painter.setBrush(colorForBattery(info.batteryPercent));
    painter.drawRoundedRect(QRectF(18, 156, 264, 4), 2, 2);

    QFont hintFont = font();
    hintFont.setPointSize(8);
    painter.setFont(hintFont);
    painter.setPen(QColor("#64748b"));
    painter.drawText(QRectF(15, 171, 270, 18), Qt::AlignCenter,
                     QString::fromUtf8("ПКМ — меню"));
}

void PowerWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragging = true;
        m_dragOffset =
            event->globalPosition().toPoint() -
            frameGeometry().topLeft();

        event->accept();
    }
}

void PowerWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_dragging &&
        (event->buttons() & Qt::LeftButton)) {

        move(
            event->globalPosition().toPoint() -
            m_dragOffset);

        event->accept();
    }
}

void PowerWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragging = false;
        event->accept();
    }
}

void PowerWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.setStyleSheet(R"QSS(
        QMenu {
            background: #111827;
            border: 1px solid #334155;
            border-radius: 10px;
            padding: 7px;
            color: #e5e7eb;
            font-family: "Segoe UI Emoji", "Segoe UI";
            font-size: 12pt;
        }
        QMenu::item {
            padding: 10px 20px;
            margin: 2px;
            border-radius: 6px;
            min-width: 205px;
        }
        QMenu::item:selected {
            background: #1f2937;
            color: #22c55e;
        }
        QMenu::separator {
            height: 1px;
            background: #334155;
            margin: 5px 10px;
        }
    )QSS");

    QAction *sleepAction = menu.addAction(QString::fromUtf8("🌙  Спящий режим"));
    QAction *hibernateAction = menu.addAction(QString::fromUtf8("💗  Гибернация"));
    menu.addSeparator();
    QAction *batteryInfoAction = menu.addAction(QString::fromUtf8("Информация о батарее"));
    QAction *logAction = menu.addAction(QString::fromUtf8("📖  Показать полный журнал"));
    menu.addSeparator();
    QAction *autostartAction = menu.addAction(QString::fromUtf8("Автозапуск при старте Windows"));
    autostartAction->setCheckable(true);
    autostartAction->setChecked(m_manager.isAutostartEnabled());

    connect(sleepAction, &QAction::triggered, this, &PowerWidget::sleepSystem);
    connect(hibernateAction, &QAction::triggered, this, &PowerWidget::hibernateSystem);
    connect(batteryInfoAction, &QAction::triggered, this, &PowerWidget::showBatteryInfo);
    connect(logAction, &QAction::triggered, this, &PowerWidget::openLog);
    connect(
        autostartAction,
        &QAction::toggled,
        this,
        [this](bool enabled) {
            if (!m_manager.setAutostartEnabled(enabled)) {
                QMessageBox::warning(
                    this,
                    "Ошибка",
                    "Не удалось изменить настройку автозапуска.");
            }
        });

    menu.exec(event->globalPos());
}

void PowerWidget::refreshView()
{
    // PowerManager::update() emits informationChanged().
    // Calling update() here again would create an infinite signal recursion.
    update();
}

void PowerWidget::showBatteryInfo()
{
    m_manager.update();

    const PowerInfo &info = m_manager.info();

    const QString powerSource = info.charging
        ? "Заряжается"
        : (info.acConnected ? "Питание от сети" : "Питание от батареи");

    const QString charge = info.batteryPercent >= 0
        ? QString("%1%").arg(info.batteryPercent)
        : "нет данных";

    const QString designedCapacity = info.designedCapacityMWh >= 0
        ? QString("%1 mWh").arg(info.designedCapacityMWh)
        : "нет данных";

    const QString fullCapacity = info.fullChargeCapacityMWh >= 0
        ? QString("%1 mWh").arg(info.fullChargeCapacityMWh)
        : "нет данных";

    const QString wear = info.wearPercent >= 0
        ? QString("%1%").arg(info.wearPercent)
        : "нет данных";

    const QString text =
        "Источник питания: " + powerSource + "\n" +
        "Уровень заряда: " + charge + "\n" +
        "Оставшееся время: " + remainingTime(info.remainingSeconds).remove("Осталось: ") + "\n\n" +
        "Тип аккумулятора: " + info.batteryType + "\n" +
        "Проектная ёмкость: " + designedCapacity + "\n" +
        "Полная ёмкость: " + fullCapacity + "\n" +
        "Степень износа: " + wear + "\n\n" +
        "Спящий режим: " + QString(info.sleepSupported ? "доступен" : "недоступен") + "\n" +
        "Modern Standby: " + QString(info.modernStandbySupported ? "да" : "нет") + "\n" +
        "Гибернация: " + QString(info.hibernateSupported ? "доступна" : "недоступна");

    QMessageBox::information(
        this,
        "Информация о батарее",
        text);
}

void PowerWidget::openLog()
{
    if (!m_logWindow)
        m_logWindow = new LogWindow(&m_manager);

    m_logWindow->show();
    m_logWindow->raise();
    m_logWindow->activateWindow();
}

void PowerWidget::sleepSystem()
{
    if (!m_manager.sleep()) {
        QMessageBox::warning(
            this,
            "Ошибка",
            "Не удалось перевести систему в спящий режим.");
    }
}

void PowerWidget::hibernateSystem()
{
    if (!m_manager.hibernate()) {
        QMessageBox::warning(
            this,
            "Ошибка",
            "Не удалось перевести систему в гибернацию.");
    }
}
