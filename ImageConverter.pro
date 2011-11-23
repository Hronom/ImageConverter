QT       += core gui svg

TARGET = ImageConverter
VERSION = 1.0.0
TEMPLATE = app

SOURCES += main.cpp\
        MainWindow.cpp

HEADERS  += MainWindow.h

FORMS    += MainWindow.ui

RC_FILE = ImageConverter.rc

CODEC = Windows-1251
CODECFORSRC = Windows-1251
CODECFORTR = Windows-1251

TRANSLATIONS = ImageConverter_en_EN.ts
