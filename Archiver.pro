#-------------------------------------------------
#
# Project created by QtCreator 2016-12-24T15:06:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Archiver
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    addfiledialog.cpp \
    settingsdialog.cpp \
    archivedialog.cpp \
    dearchivedialog.cpp \
    progressbardialog.cpp \
    writeread.cpp \
    Archiver.cpp \
    SParch.cpp \
    BHuffman.cpp

HEADERS  += mainwindow.h \
    addfiledialog.h \
    settingsdialog.h \
    archivedialog.h \
    dearchivedialog.h \
    progressbardialog.h \
    writeread.h \
    Archiver.h \
    SParch.h \
    BHuffman.h

FORMS    += mainwindow.ui \
    addfiledialog.ui \
    settingsdialog.ui \
    archivedialog.ui \
    dearchivedialog.ui \
    progressbardialog.ui

RESOURCES += \
    res.qrc
