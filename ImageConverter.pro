QT       += core gui svg network

TARGET = ImageConverter
VERSION = 1.0.0
TEMPLATE = app

CONFIG(debug, debug|release) {
    LIBS += -L$$PWD/../../NewVersionChecker/NewVersionChecker-build-desktop/debug -lNewVersionChecker
    PRE_TARGETDEPS += $$PWD/../../NewVersionChecker/NewVersionChecker-build-desktop/debug/libNewVersionChecker.a
}

CONFIG(release, debug|release) {
    LIBS += -L$$PWD/../../NewVersionChecker/NewVersionChecker-build-desktop/release -lNewVersionChecker
    PRE_TARGETDEPS += $$PWD/../../NewVersionChecker/NewVersionChecker-build-desktop/release/libNewVersionChecker.a
    DEFINES += QT_NO_DEBUG_OUTPUT
}

INCLUDEPATH += $$PWD/../../NewVersionChecker/NewVersionChecker/

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






