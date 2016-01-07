#-------------------------------------------------
#
# Project created by QtCreator 2015-12-29T11:06:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = XML_Test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tinyxml/tinystr.cpp \
    tinyxml/tinyxml.cpp \
    tinyxml/tinyxmlerror.cpp \
    tinyxml/tinyxmlparser.cpp

HEADERS  += mainwindow.h \
    tinyxml/tinystr.h \
    tinyxml/tinyxml.h

FORMS    += mainwindow.ui
