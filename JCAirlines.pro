#-------------------------------------------------
#
# Project created by QtCreator 2014-02-25T23:24:15
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JCAirlines
TEMPLATE = app


SOURCES += main.cpp\
        mwindow.cpp \
    admindialog.cpp \
    graphicarea.cpp \
    newairportdialog.cpp \
    clientdialog.cpp

HEADERS  += mwindow.h \
    admindialog.h \
    graphicarea.h \
    figure.h \
    pointfigure.h \
    airport.h \
    newairportdialog.h \
    ../GrafoTest/Grafo.h \
    linefigure.h \
    clientdialog.h

FORMS    += mwindow.ui \
    admindialog.ui \
    newairportdialog.ui \
    clientdialog.ui

RESOURCES += \
    resources.qrc
