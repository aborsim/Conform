#include <QFileDialog> //The include of includes
#include <string>
#include <vector>
#include <iostream>
#include <json/json.h>
#include <QThreadPool>
#include "cmder.cpp"
#include "mainwindow.h"
#include "ui_mainwindow.h" //Import auto-generated code
#include "converterrunnable.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->threadCount->setMaximum(std::thread::hardware_concurrency());

    mediaMenu->addAction(ui->actionDelete);

    connect(ui->actionConvert, SIGNAL(triggered()), this, SLOT(convert())); //Connect buttons to appropriate functions
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(addFiles()));
    connect(ui->pathBrowser, SIGNAL(clicked()), this, SLOT(setPath()));
    connect(ui->actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));

    connect(ui->mediaList, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(listContextMenu(const QPoint&))); //Connect media list functions
    connect(ui->actionDelete, SIGNAL(triggered()), this, SLOT(deleteItem()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::convert()
{
    threads.setMaxThreadCount(this->ui->threadCount->value());
    for (int i = 0; i < files.count(); i++)
    {
        ConverterRunnable *converter = new ConverterRunnable(this, getArgs(i), i);
        threads.start(converter);
    }
}

QString MainWindow::getArgs(int pos)
{
    QString args("ffmpeg ");
    QStringList outputList = files.at(pos).split(QDir::separator()).last().split("."); //Get file path
    outputList[outputList.count() - 1] = ui->container->text();
    QString output = QDir(ui->outputPath->text()).absoluteFilePath(outputList.join("."));
    args += "-i \"" + files.at(pos) + "\"" +\
            " -s " + ui->width->text() + "x" + ui->height->text() +\
            " " + ui->additionalArgs->text() + " \"" + output + "\"";
    return args;
}

void MainWindow::addFiles()
{
    //QStringList filenames;
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    if (dialog.exec()) {files = dialog.selectedFiles();}
    if (files.count() == 0) return;
    for (int i = 0; i < files.size(); i++)
    {
        QStringList file(files.at(i)); file.append("Ready");
        ui->mediaList->addTopLevelItem(new QTreeWidgetItem(file));
    }
    setDefaults(this->files.last());
}

void MainWindow::setDefaults(QString filename)
{
    QString rawData = cmder(QString("ffprobe -v quiet -print_format json -show_streams ") + QString(filename));
    Json::Value allData, data;
    Json::Reader reader; reader.parse(rawData.toStdString(), allData);
    data = allData["streams"][0];
    ui->width->setText(QString::number(data["width"].asInt()));
    ui->height->setText(QString::number(data["height"].asInt()));
    ui->container->setText(filename.split(".").last());
}

void MainWindow::setPath()
{
    QString path;
    QFileDialog pathGetter(this);
    pathGetter.setFileMode(QFileDialog::Directory);
    pathGetter.setOption(QFileDialog::ShowDirsOnly, true);
    if (pathGetter.exec()) {path = pathGetter.selectedFiles()[0];}
    ui->outputPath->setText(path);
}

void MainWindow::setStatus(QString status, int pos)
{
    //QStringList item(files.at(pos)); item.append(status);
    ui->mediaList->topLevelItem(pos)->setText(1, status);
    QCoreApplication::processEvents();
    std::cout << "Status set\n";
}

void MainWindow::listContextMenu(const QPoint& point)
{
    QPoint globalPoint = ui->mediaList->mapToGlobal(point);
    mediaMenu->exec(globalPoint);
}

void MainWindow::deleteItem()
{
    if (ui->mediaList->currentItem())
        delete ui->mediaList->currentItem();
}
