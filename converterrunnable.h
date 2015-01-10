#ifndef CONVERTERTHREAD_H
#define CONVERTERTHREAD_H

#include <QObject>
#include <QRunnable>
#include <iostream>
#include "mainwindow.h"


class ConverterRunnable : public QRunnable
{
public:
    explicit ConverterRunnable(MainWindow*, QString, int);
    void run();

signals:
    void setMessage(QString, int);

private:
    MainWindow* parent;
    QString cmd;
    int pos;

};

#endif // CONVERTERTHREAD_H
