#-------------------------------------------------
#
# Project created by QtCreator 2017-12-19T13:36:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tiny
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    util.cpp \
    parse.cpp \
    scan.cpp

HEADERS  += mainwindow.h \
    util.h \
    scan.h \
    parse.h \
    globals.h \
    mymain.h

FORMS    += mainwindow.ui

RC_ICONS= icon.ico

DISTFILES += \
    images/document-open.png \
    images/document-save-as.png \
    images/document-save.png \
    images/edit-find.png \
    images/edit-undo.png \
    images/editcopy.png \
    images/editcut.png \
    images/editpaste.png \
    images/exit.png \
    images/gtk-close.png \
    images/help.png
