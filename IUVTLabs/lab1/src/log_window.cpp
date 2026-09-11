
#include "log_window.h"
#include "power_manager.h"

#include <QComboBox>
#include <QFileDialog>
#include <QFile>
#include <QHBoxLayout>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QTextStream>
#include <QVBoxLayout>

LogWindow::LogWindow(
    PowerManager *manager,
    QWidget *parent)
    : QWidget(parent),
      m_manager(manager)
{
    setWindowTitle("Журнал энергопитания");
    resize(760, 480);

    setStyleSheet(R"QSS(
        QWidget {
            background: #0b0f17;
            color: #e5e7eb;
            font-family: "Segoe UI", "Segoe UI Emoji";
            font-size: 10pt;
        }
        QLabel {
            color: #cbd5e1;
            font-size: 12pt;
            font-weight: 600;
        }
        QComboBox, QPushButton {
            background: #111827;
            border: 1px solid #334155;
            border-radius: 8px;
            padding: 9px 14px;
            color: #e5e7eb;
            font-size: 11pt;
        }
        QComboBox:hover, QPushButton:hover {
            background: #1f2937;
        }
        QComboBox::drop-down {
            border: 0;
            width: 25px;
        }
        QListWidget {
            background: #090d14;
            border: 1px solid #263244;
            border-radius: 8px;
            padding: 8px;
            outline: none;
        }
        QListWidget::item {
            padding: 8px 10px;
            margin: 3px 0;
            border-radius: 6px;
            color: #cbd5e1;
        }
        QListWidget::item:selected {
            background: #1f2937;
            color: #22c55e;
        }
        QScrollBar:vertical {
            background: #111827;
            width: 10px;
            margin: 4px;
            border-radius: 5px;
        }
        QScrollBar::handle:vertical {
            background: #475569;
            min-height: 25px;
            border-radius: 5px;
        }
    )QSS");

    m_filter = new QComboBox(this);

    m_filter->addItems({
        "Все",
        "Подключение ЗУ",
        "Изменение заряда",
        "Переход в сон",
        "Гибернация"
    });

    m_list = new QListWidget(this);

    m_saveButton =
        new QPushButton("Сохранить отчёт", this);

    auto *topLayout = new QHBoxLayout;
    topLayout->addWidget(m_filter);
    topLayout->addStretch();
    topLayout->addWidget(m_saveButton);

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(m_list);

    connect(
        m_filter,
        &QComboBox::currentTextChanged,
        this,
        &LogWindow::reload);

    connect(
        m_saveButton,
        &QPushButton::clicked,
        this,
        &LogWindow::saveReport);

    connect(
        m_manager,
        &PowerManager::newLogEntry,
        this,
        &LogWindow::reload);

    reload();
}

void LogWindow::reload()
{
    m_list->clear();

    const QString filter =
        m_filter->currentText();

    for (const LogEntry &entry :
         m_manager->log()) {

        if (filter != "Все" &&
            filter != entry.type) {
            continue;
        }

        m_list->addItem(
            entry.time.toString(
                "yyyy-MM-dd HH:mm:ss")
            + " | "
            + entry.type
            + " | "
            + entry.message);
    }
}

void LogWindow::saveReport()
{
    const QString fileName =
        QFileDialog::getSaveFileName(
            this,
            "Сохранить журнал",
            "power_report.txt",
            "Текстовый файл (*.txt)");

    if (fileName.isEmpty())
        return;

    QFile file(fileName);

    if (!file.open(
            QIODevice::WriteOnly |
            QIODevice::Text)) {

        QMessageBox::warning(
            this,
            "Ошибка",
            "Не удалось сохранить отчёт.");

        return;
    }

    QTextStream stream(&file);

    stream << "Журнал событий энергопитания\n";
    stream << "====================================\n";

    for (const LogEntry &entry :
         m_manager->log()) {

        stream
            << entry.time.toString(
                   "yyyy-MM-dd HH:mm:ss")
            << " | "
            << entry.type
            << " | "
            << entry.message
            << '\n';
    }

    file.close();

    QMessageBox::information(
        this,
        "Готово",
        "Журнал успешно сохранён.");
}
