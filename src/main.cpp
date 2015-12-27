#include <QApplication>
#include <QDir>
#include <QDebug>

#include "databaseconfig.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("Laycan");
    QApplication::setApplicationVersion("1.0");

    DatabaseConfig w;
    w.show();

    return a.exec();
}