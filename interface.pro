#-------------------------------------------------
#
# Project created by QtCreator 2015-04-17T15:52:47
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

include(src/xlsx/qtxlsx.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = interface
TEMPLATE = app

copydata.commands = $(COPY_DIR) $$PWD/src/help $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

SOURCES += src/about.cpp \
    src/Brandes.cpp \
    src/Dijkstra.cpp \
    src/FileWriter.cpp \
    src/Graph.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/Measure.cpp \
    src/Node.cpp \
    src/Plane.cpp \
    src/Suurballe.cpp

HEADERS  += src/about.h \
    src/Brandes.hpp \
    src/Dijkstra.hpp \
    src/FileWriter.hpp \
    src/Graph.hpp \
    src/mainwindow.h \
    src/Measure.hpp \
    src/Node.hpp \
    src/Plane.hpp \
    src/Suurballe.hpp \
    src/tree.hh \
    src/tree_util.hh

FORMS    += src/mainwindow.ui \
    src/about.ui
