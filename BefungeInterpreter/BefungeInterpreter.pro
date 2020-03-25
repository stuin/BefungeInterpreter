#-------------------------------------------------
#
# Project created by QtCreator 2016-12-19T17:16:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KagofBefunge93Interpreter
VERSION = 1.0.1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    file.cpp \
    codetorus.cpp \
    interpreter.cpp \
    clickfilter.cpp

HEADERS  += mainwindow.h \
    file.h \
    codetorus.h \
    interpreter.h \
    clickfilter.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc
	
RC_FILE = bficon.rc

