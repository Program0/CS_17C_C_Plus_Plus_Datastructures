
#include <QApplication>

#include <QDebug>

//#include "playspace.h"
#include "mainwindow.h"
//#include "logindialog.h"
//#include "newuserdialog.h"
//#include "computer.h"
#include "newgamedialog.h"

int main(int argc, char *argv[])
{


    QApplication a(argc,argv);

    MainWindow mainWin;
    mainWin.show();

    return a.exec();
}
