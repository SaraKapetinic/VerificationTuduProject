#-------------------------------------------------
#
# Project created by QtCreator 2020-11-17T12:33:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tudu
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    src/tudutask.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/addtaskform.cpp \
    src/tudulist.cpp \
    src/task.cpp \
    src/init.cpp 

HEADERS += \
    headers/tudutask.h \
    headers/mainwindow.h \
    headers/addtaskform.h \
    headers/tudulist.h \
    headers/task.h \
    headers/init.h

FORMS += \
    forms/mainwindow.ui \
    forms/addtaskform.ui \
    forms/tudutask.ui
