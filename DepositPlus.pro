#-------------------------------------------------
#
# Project created by QtCreator 2015-04-25T23:12:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DepositPlus
TEMPLATE = app


SOURCES += main.cpp \
    ui_logic/mainform.cpp \
    calc_logic/ratesmatrix.cpp

HEADERS  += \
    utils/array.h \
    ui_logic/mainform.h \
    calc_logic/date.h \
    calc_logic/valute.h \
    calc_logic/deposittemplate.h \
    calc_logic/ratesmatrix.h \
    calc_logic/deposit.h \
    calc_logic/depositholder.h

FORMS    += \
    ui_logic/mainform.ui
