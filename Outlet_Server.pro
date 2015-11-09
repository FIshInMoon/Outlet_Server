#-------------------------------------------------
#
# Project created by QtCreator 2015-11-08T18:59:13
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Outlet_Server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    socketprotocol.cpp \
    tcpsocket.cpp \
    tcpserver.cpp

HEADERS  += mainwindow.h \
    socketprotocol.h \
    tcpsocket.h \
    tcpserver.h

FORMS    += mainwindow.ui
