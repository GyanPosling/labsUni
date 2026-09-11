
#include <QApplication>
#include "power_widget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("PowerMonitorA4");
    QApplication::setOrganizationName("PowerMonitorA4");

    PowerWidget widget;
    widget.show();
    widget.raise();
    widget.activateWindow();

    return app.exec();
}
