#-------------------------------------------------
#
# Project created by QtCreator 2017-05-22T09:15:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 06-analisador-sintatico
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    analisadorSintatico.cpp

HEADERS  += mainwindow.h \
    simbolo.h \
    analisadorSintatico.h

FORMS    += mainwindow.ui
