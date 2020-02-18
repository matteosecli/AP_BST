QT += testlib
QT -= gui

CONFIG += console warn_on depend_includepath testcase
CONFIG -= app_bundle qt
CONFIG += c++14

TEMPLATE = app

PROJECT_DIR = $$PWD/../src/
INCLUDEPATH += $$PROJECT_DIR

SOURCES +=  \
    000-CatchMain.cpp \
    010-NodeTest.cpp \
    020-IteratorTest.cpp \
    030-TreeTest.cpp

HEADERS += \
    catch.hpp
