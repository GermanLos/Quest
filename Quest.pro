#-------------------------------------------------
#
# Project created by QtCreator 2016-10-23T21:38:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Quest
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    parser.cpp \
    player.cpp

HEADERS  += widget.h \
    parser.h \
    player.h

FORMS    += widget.ui
