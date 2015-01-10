#-------------------------------------------------
#
# Project created by QtCreator 2015-01-04T21:46:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Conform
TEMPLATE = app
CONFIG += c++11
#ICON = resources/conform.png

SOURCES += main.cpp\
        mainwindow.cpp \
    cmder.cpp \
    converterrunnable.cpp

LIBS += -ljsoncpp

HEADERS  += mainwindow.h \
    converterrunnable.h

FORMS    += mainwindow.ui

RESOURCES += \
    Resources.qrc
