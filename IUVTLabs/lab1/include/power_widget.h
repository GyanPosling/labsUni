
#pragma once

#include <QWidget>
#include <QPoint>
#include <QTimer>
#include <windows.h>

#include "power_manager.h"

class LogWindow;

class PowerWidget final : public QWidget
{
    Q_OBJECT

public:
    explicit PowerWidget(QWidget *parent = nullptr);
    ~PowerWidget() override;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;

private slots:
    void refreshView();
    void openLog();
    void sleepSystem();
    void hibernateSystem();

private:
    QColor colorForBattery(int percent) const;
    QString remainingTime(qint64 seconds) const;
    void drawBatteryIcon(QPainter &painter, const QRectF &area, const PowerInfo &info) const;

    PowerManager m_manager;
    QTimer m_timer;

    QPoint m_dragOffset;
    bool m_dragging = false;

    LogWindow *m_logWindow = nullptr;
};
