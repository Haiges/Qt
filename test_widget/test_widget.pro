#-------------------------------------------------
#
# Project created by QtCreator 2017-09-29T15:23:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#qwt
INCLUDEPATH += /usr/local/qwt-6.1.3/include/
LIBS += -L"/usr/local/qwt-6.1.3/lib/" -lqwt

TARGET = test_widget
TEMPLATE = app


SOURCES += main.cc\
        mainwindow.cc

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
