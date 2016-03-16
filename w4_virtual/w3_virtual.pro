#-------------------------------------------------
#
# Project created by QtCreator 2016-03-15T08:56:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = w3_virtual
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    figura.cpp

HEADERS  += widget.h \
    figura.h

FORMS    += widget.ui

QMAKE_CXXFLAGS += -std=c++11
