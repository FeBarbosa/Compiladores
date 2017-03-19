#-------------------------------------------------
#
# Project created by QtCreator 2017-03-17T19:42:21
#
#-------------------------------------------------
CONFIG += c++ 11
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 02-AFN-MV
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    expreregular.cpp \
    nfa.cpp

HEADERS  += mainwindow.h \
    expreregular.h \
    estado.h \
    nfa.h

FORMS    += mainwindow.ui
