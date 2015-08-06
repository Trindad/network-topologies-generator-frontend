#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.addLibraryPath(a.applicationDirPath());

    MainWindow w;
    w.appPath = a.applicationDirPath().toStdString();
    w.show();
    
    return a.exec();
}
