#-------------------------------------------------
#
# Project created by QtCreator 2013-07-12T15:41:40
#
#-------------------------------------------------

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET       = unit-converter
TEMPLATE     = app
SOURCES     += main.cc mainwindow.cc
HEADERS     += mainwindow.h
FORMS       += mainwindow.ui
RESOURCES   += icon.qrc
TRANSLATIONS = l10n/fr_FR.ts

win32 {
    TARGET  += .exe
    RC_FILE += favicon.rc
}

