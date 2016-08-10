#-------------------------------------------------
#
# Project created by QtCreator 2016-07-22T13:53:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sudoku
TEMPLATE = app


SOURCES += main.cpp\
        kontroler.cpp \
    model.cpp \
    widok.cpp \
    plansza.cpp \
    cyfra.cpp

HEADERS  += kontroler.h \
    model.h \
    widok.h \
    plansza.h \
    cyfra.h

FORMS    += kontroler.ui

RESOURCES += \
    zasoby.qrc
