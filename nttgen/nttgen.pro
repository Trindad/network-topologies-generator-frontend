#-------------------------------------------------
#
# Project created by QtCreator 2015-02-24T15:47:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nttgen
TEMPLATE = app

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    Suurballe.cpp \
    Plane.cpp \
    Node.cpp \
    Measure.cpp \
    Graph.cpp \
    Dijkstra.cpp \
    Brandes.cpp

HEADERS  += mainwindow.h \
    tree_util.hh \
    tree.hh \
    Suurballe.hpp \
    Plane.hpp \
    Node.hpp \
    Measure.hpp \
    Graph.hpp \
    Dijkstra.hpp \
    Brandes.hpp \
    FileWriter.hpp

FORMS    += mainwindow.ui
