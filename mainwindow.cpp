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

    connect(ui->actionConvert, SIGNAL(triggered()), this, SLOT(convert())); //Connect buttons to appropriate functions
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(addFiles()));
    connect(ui->pathBrowser, SIGNAL(clicked()), this, SLOT(setPath()));
    connect(ui->actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::convert()
{
    std::cout << "Preparing for conversion.\n";
    threads.setMaxThreadCount(this->ui->threadCount->value());
    std::cout << "Prepariation done.\n";
    for (int i = 0; i < files.count(); i++)
    {
        std::cout << "Executing conversion on thread " << i << "\n";
        ConverterRunnable *converter = new ConverterRunnable(this, getArgs(i), i);
        threads.start(converter);
    }
}

QString MainWindow::getArgs(int pos)
{
    QString args("ffmpeg ");
    QStringList output(QDir(ui->outputPath->text()).absoluteFilePath(files.at(pos)).split("."));
    output[output.count() - 1] = ui->container->text();
    std::cout << "Output path: " << output.join(".").toStdString();
    args += "-i \"" + files.at(pos) + "\"" +\
            " -s " + ui->width->text() + "x" + ui->height->text() +\
            " " + ui->additionalArgs->text() + " \"" + output.join(".") + "\"";
    return args;
}

void MainWindow::addFiles()
{
    //QStringList filenames;
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    if (dialog.exec()) {files = dialog.selectedFiles();}
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
