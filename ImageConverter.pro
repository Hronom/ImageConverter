QT       += core gui svg network

TARGET = ImageConverter
VERSION = 1.2.0
TEMPLATE = app

CONFIG(debug, debug|release) {
    LIBS += -L$$PWD/../../VersionChecker/VersionChecker-build-desktop/debug -lVersionChecker
    PRE_TARGETDEPS += $$PWD/../../VersionChecker/VersionChecker-build-desktop/debug/libVersionChecker.a
}

CONFIG(release, debug|release) {
    LIBS += -L$$PWD/../../VersionChecker/VersionChecker-build-desktop/release -lVersionChecker
    PRE_TARGETDEPS += $$PWD/../../VersionChecker/VersionChecker-build-desktop/release/libVersionChecker.a
    DEFINES += QT_NO_DEBUG_OUTPUT
}

INCLUDEPATH += $$PWD/../../VersionChecker/VersionChecker/

SOURCES += main.cpp\
    MainWindow.cpp \
    AboutMyProgram.cpp

HEADERS  += MainWindow.h \
    AboutMyProgram.h \
    GlobalDefinitions.h

FORMS    += MainWindow.ui \
    AboutMyProgram.ui

RC_FILE = ImageConverter.rc

CODEC = Windows-1251
CODECFORSRC = Windows-1251
CODECFORTR = Windows-1251

TRANSLATIONS = ImageConverter_en_EN.ts

RESOURCES += ImageConverter.qrc






