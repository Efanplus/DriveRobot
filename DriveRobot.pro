#-------------------------------------------------
#
# Project created by QtCreator 2018-04-24T16:04:23
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DriveRobot
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    arm.cpp \
    delta_chest.cpp \
    eye.cpp \
    head.cpp \
    legs.cpp \
    qport.cpp \
    qsingleton.cpp

HEADERS += \
        mainwindow.h \
    arm.h \
    delta_chest.h \
    eye.h \
    head.h \
    legs.h \
    qport.h \
    qsingleton.h

FORMS += \
        mainwindow.ui \
    arm.ui \
    delta_chest.ui \
    eye.ui \
    head.ui \
    legs.ui \
    qport.ui

INCLUDEPATH += 'C:\Program Files (x86)\opencv\install\include'
INCLUDEPATH += 'C:\Program Files (x86)\opencv\install\include\opencv'
INCLUDEPATH += 'C:\Program Files (x86)\opencv\install\include\opencv2'
LIBS += 'C:\Program Files (x86)\opencv\install\x64\vc15\lib\*.lib'
