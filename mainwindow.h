#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <thread>
#include <QThreadPool>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    Q_INVOKABLE void setStatus(QString, int);

private slots:
    void convert();
    void addFiles();
    void setPath();
    //void setStatus(QString, int);

private:
    Ui::MainWindow *ui;
    QString getArgs(int);
    void setDefaults(QString);
    void populateList();
    QStringList files;
    QThreadPool threads;
    //QList<QStringList> filelist;
};

#endif // MAINWINDOW_H
