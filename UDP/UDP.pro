#-------------------------------------------------
#
# Project created by QtCreator 2019-04-08T10:28:20
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UDP
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
        udp.cpp

HEADERS += \
        udp.h

FORMS += \
        udp.ui


DISTFILES += RegExp.json \
    UDP.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DESTDIR = ../bin/plugins

DEPENDPATH += $$PWD/../../build/ToolBox/bin

INCLUDEPATH += $$PWD/../PluginWidget
LIBS += -L$$PWD/../../build/ToolBox/bin/ -lPluginWidget

INCLUDEPATH += $$PWD/../MyShareLibrary
LIBS += -L$$PWD/../../build/ToolBox/bin/ -lMyShareLibrary
