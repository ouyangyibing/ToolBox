#-------------------------------------------------
#
# Project created by QtCreator 2019-03-26T14:20:14
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = RegExp
TEMPLATE = lib
CONFIG += plugin

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    regexp.cpp

HEADERS += \
    regexp.h

FORMS += \
    regexp.ui


DISTFILES += RegExp.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DESTDIR = ../bin/plugins

DEPENDPATH += ../bin

INCLUDEPATH += $$PWD/../PluginWidget
LIBS += -L../bin/ -lPluginWidget

INCLUDEPATH += $$PWD/../MyShareLibrary
LIBS += -L../bin/ -lMyShareLibrary
