#-------------------------------------------------
#
# Project created by QtCreator 2017-09-25T16:26:07
#
#-------------------------------------------------

INCLUDEPATH += /usr/local/include/
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

INCLUDEPATH += /usr/local/qwt-6.1.3/include/
LIBS += -L"/usr/local/qwt-6.1.3/lib/" -lqwt

TARGET = RealTime
TEMPLATE = app


SOURCES += main.cc\
        mainwindow.cc \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h
LIBS = /usr/local/lib/libfftw3.a
FORMS    += mainwindow.ui
