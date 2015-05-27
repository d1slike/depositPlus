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
    calc_logic/model/ratesmatrix.cpp \
    calc_logic/model/date.cpp \
    calc_logic/model/deposit.cpp

HEADERS  += \
    utils/array.h \
    ui_logic/mainform.h \
    utils/section.h \
    calc_logic/model/date.h \
    calc_logic/model/deposit.h \
    calc_logic/model/money.h \
    calc_logic/model/ratesmatrix.h \
    calc_logic/model/valute.h \
    calc_logic/templates/depositholder.h \
    calc_logic/templates/deposittemplate.h

FORMS    += \
    ui_logic/mainform.ui
