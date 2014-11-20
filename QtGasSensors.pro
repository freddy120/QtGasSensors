#-------------------------------------------------
#
# Project created by QtCreator 2014-11-19T08:36:16
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

QT += serialport
QMAKE_CXXFLAGS += -std=c++11


TARGET = QtGasSensors
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    settingsdialog.cpp \
    tendencias.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    settingsdialog.h \
    util.h \
    tendencias.h \
    qcustomplot.h

FORMS    += mainwindow.ui \
    settingsdialog.ui \
    tendencias.ui
