#-------------------------------------------------
#
# Project created by QtCreator 2016-11-11T13:26:16
#
#-------------------------------------------------

QT       += core widgets

QT       -= gui

INCLUDEPATH += /usr/local/qwt-6.1.3/include/
LIBS += -L"/usr/local/qwt-6.1.3/lib/" -lqwt

TARGET = test
CONFIG   += console
CONFIG   -= app_bundle
INCLUDEPATH += /usr/local/include/
TEMPLATE = app
LIBS = /usr/local/lib/libfftw3.a

SOURCES += main.cpp \
    main.cpp \
    main.cpp \
    main.cpp
