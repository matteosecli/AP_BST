QT += testlib
QT -= gui

CONFIG += console warn_on depend_includepath testcase
CONFIG -= app_bundle qt
CONFIG += c++14

TEMPLATE = app

SOURCES +=  \
    000-CatchMain.cpp \
    010-NodeTest.cpp

HEADERS += \
    catch.hpp
