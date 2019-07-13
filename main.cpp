#include "mainwindow.h"
#include "controlbar.h"
#include "playlist.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    ControlBar c;
//    c.show();
//      PlayList p;
//      p.show();
    return a.exec();
}
