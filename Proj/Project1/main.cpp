
#include <QApplication>

#include <QPixmap>


#include "playspace.h"
//#include "newgamedialog.h"
//#include "mainwindow.h"
#include "logindialog.h"
//#include "guessentry.h"

int main(int argc, char *argv[])
{
    QApplication a(argc,argv);

    QString image1(":/images/Bull-icon.png");
    QString image2(":/images/cow-icon.png");
    QPixmap bull(image1);
    QPixmap cow(image2);
    unsigned int size=8;


    PlaySpace w(bull,cow,size);
    w.show();

    LoginDialog *l = new LoginDialog;
    l->show();

    return a.exec();
}
