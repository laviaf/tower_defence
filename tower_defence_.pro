#-------------------------------------------------
#
# Project created by QtCreator 2020-05-28T23:48:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tower_defence_
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
    start_click.cpp \
    world_map.cpp \
    level1.cpp \
    tower_position.cpp \
    enemy.cpp \
    utility.cpp \
    way_point.cpp \
    tower.cpp

HEADERS += \
        mainwindow.h \
    start_click.h \
    world_map.h \
    level1.h \
    tower_position.h \
    enemy.h \
    utility.h \
    way_point.h \
    tower.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    tower_defence.qrc

QT += multimedia
