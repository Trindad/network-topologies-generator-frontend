#-------------------------------------------------
#
# Project created by QtCreator 2015-04-17T15:52:47
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

include(xlsx/qtxlsx.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = interface
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Brandes.cpp \
    Dijkstra.cpp \
    FileWriter.cpp \
    Graph.cpp \
    Measure.cpp \
    Node.cpp \
    Plane.cpp \
    Suurballe.cpp \
    about.cpp

HEADERS  += mainwindow.h \
    Brandes.hpp \
    Dijkstra.hpp \
    FileWriter.hpp \
    Graph.hpp \
    Measure.hpp \
    Node.hpp \
    Plane.hpp \
    Suurballe.hpp \
    tree.hh \
    tree_util.hh \
    about.h

FORMS    += mainwindow.ui \
    about.ui
