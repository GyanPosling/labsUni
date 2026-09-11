
#pragma once

#include <QWidget>

class QComboBox;
class QListWidget;
class QPushButton;
class PowerManager;

class LogWindow final : public QWidget
{
    Q_OBJECT

public:
    explicit LogWindow(
        PowerManager *manager,
        QWidget *parent = nullptr);

private slots:
    void reload();
    void saveReport();

private:
    PowerManager *m_manager;

    QComboBox *m_filter;
    QListWidget *m_list;
    QPushButton *m_saveButton;
};
