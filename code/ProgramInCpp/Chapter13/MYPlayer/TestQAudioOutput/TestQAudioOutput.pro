QT += core multimedia
QT -= gui

CONFIG += c++11

TARGET = TestQAudioOutput
CONFIG += console c++11
CONFIG -= app_bundle

TEMPLATE = app

# Directory where all intermediate objects and moc files should be placed
CONFIG(debug, debug|release) {
    OBJECTS_DIR = ./tmp/debug
    MOC_DIR = ./tmp/debug
} else {
    OBJECTS_DIR = ./tmp/release
    MOC_DIR = ./tmp/release
}

# Directory where all intermediate files from uic should be placed
CONFIG(debug, debug|release) {
    UI_DIR = ./tmp/debug
} else {
    UI_DIR = ./tmp/release
}

# Directory for Qt Resource Compiler output files
CONFIG(debug, debug|release) {
    RCC_DIR = ./tmp/debug
} else {
    RCC_DIR = ./tmp/release
}

# Specifies where to put the target file
CONFIG(debug, debug|release) {
    contains(QMAKE_TARGET.arch, x86_64) {
        DESTDIR = $$_PRO_FILE_/../../../bin/debug/x64
    } else {
        DESTDIR = $$_PRO_FILE_/../../../bin/debug/x86
    }
} else {
    contains(QMAKE_TARGET.arch, x86_64) {
        DESTDIR = $$_PRO_FILE_/../../../bin/release/x64
    } else {
        DESTDIR = $$_PRO_FILE_/../../../bin/release/x86
    }
}

# Codec configuration
CODECFORTR = UTF-8
CODECFORSRC = UTF-8

SOURCES += main.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
