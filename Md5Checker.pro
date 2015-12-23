#-------------------------------------------------
#
# Project created by QtCreator 2015-12-04T21:32:07
#
#-------------------------------------------------

QT       += core gui winextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Md5Checker
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    dialogstyle.cpp \
    comparechecksums.cpp \
    settingpage.cpp

HEADERS  += mainwindow.h \
    dialogstyle.h \
    comparechecksums.h \
    settingpage.h

FORMS    += mainwindow.ui \
    settingpage.ui

RESOURCES += \
    icons.qrc \
    translation.qrc

TRANSLATIONS += \
    languages/lang_it.ts
    languages/lang_en.ts
