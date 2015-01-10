//Licensed under the GPLv2
//Property of aborsim
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(QString(":/resources/conform.png")));
    MainWindow w;
    //QObject::connect(ConverterThread*, SIGNAL(setMessage(QString, int)), MainWindow*s, SLOT(setStatus(QString,int)));
    w.setWindowTitle("Conform");
    w.show();

    return a.exec();
}
