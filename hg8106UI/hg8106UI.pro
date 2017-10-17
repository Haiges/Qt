#-------------------------------------------------
#
# Project created by QtCreator 2017-09-13T08:48:57
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

//debug
#DEFINES += QT_NO_DEBUG_OUTPUT

TARGET = hg8106UI
TEMPLATE = app

#qwt
INCLUDEPATH += /usr/local/qwt-6.1.3/include/
LIBS += -L"/usr/local/qwt-6.1.3/lib/" -lqwt

SOURCES += main.cpp\
    test.cpp \
    cmdwidget.cpp \
    serialcmdwidget.cpp \
    wavewidget.cc \
    dbwidget.cc

HEADERS  += \
    test.h \
    cmdwidget.h \
    serialcmdwidget.h \
    wavewidget.h \
    dbwidget.h \
    qtdefine.h

FORMS    += mainwindow.ui


