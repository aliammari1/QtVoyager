QT += testlib sql core
QT -= gui

CONFIG += c++17 console testcase
CONFIG -= app_bundle

TARGET = tests
TEMPLATE = app

# Headless: tests set QT_QPA_PLATFORM=offscreen, but no GUI is linked anyway.

INCLUDEPATH += $$PWD/..

# Optional coverage instrumentation: build with `qmake CONFIG+=coverage`.
coverage {
    QMAKE_CXXFLAGS += --coverage -O0 -g
    QMAKE_LFLAGS += --coverage
}

SOURCES += \
    tst_voyage.cpp \
    ../gestionVoyages/voyage.cpp

HEADERS += \
    ../gestionVoyages/voyage.h
