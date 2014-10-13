#-------------------------------------------------
#
# Project created by QtCreator 2014-10-08T21:10:17
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = roku
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    httphandler.cpp \
    roku.cpp

HEADERS  += mainwindow.h \
    httphandler.h \
    roku.h

FORMS    += mainwindow.ui
