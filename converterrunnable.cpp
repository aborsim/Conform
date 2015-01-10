#include "converterrunnable.h"

ConverterRunnable::ConverterRunnable(MainWindow* parent = 0, QString command = "", int position = 0)
{
    std::cout << "Thread running.";
    this->parent = parent;
    this->pos = position;
    this->cmd = command;
}

void ConverterRunnable::run()
{
    //emit setMessage(QString("Processing"), pos);
    std::cout << "Setting status\n";
    QString outputLocation("Converting to "); outputLocation += this->cmd.split(" ").last();
    QMetaObject::invokeMethod(parent, "setStatus", Qt::QueuedConnection, Q_ARG(QString, outputLocation), Q_ARG(int, this->pos));
    QByteArray ba(this->cmd.toLocal8Bit());
    system(ba.data());
    //emit setMessage(QString("Done"), pos);
    QMetaObject::invokeMethod(parent, "setStatus", Qt::QueuedConnection, Q_ARG(QString, QString("Done")), Q_ARG(int, this->pos));
}
