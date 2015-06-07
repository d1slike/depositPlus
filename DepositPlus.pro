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
    calc_logic/model/ratesmatrix.cpp \
    calc_logic/model/date.cpp \
    calc_logic/model/deposit.cpp \
    calc_logic/templates/depositholder.cpp \
    ui_logic/mainwindow.cpp \
    ui_logic/depositform.cpp \
    controller.cpp \
    calc_logic/model/profitresult.cpp

HEADERS  += \
    utils/array.h \
    calc_logic/model/date.h \
    calc_logic/model/deposit.h \
    calc_logic/model/money.h \
    calc_logic/model/ratesmatrix.h \
    calc_logic/model/valute.h \
    calc_logic/templates/depositholder.h \
    calc_logic/templates/deposittemplate.h \
    ui_logic/mainwindow.h \
    ui_logic/depositform.h \
    controller.h \
    calc_logic/model/profitresult.h

FORMS    += \
    ui_logic/mainwindow.ui \
    ui_logic/depositform.ui

RESOURCES += \
    resource.qrc
