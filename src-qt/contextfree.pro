#-------------------------------------------------
#
# Project created by QtCreator 2017-07-09T22:19:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = contextfree
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cfdg_highlighter.cpp \
    qtcanvas.cpp

HEADERS  += mainwindow.h \
    cfdg_highlighter.h \
    qtcanvas.h


FORMS    += mainwindow.ui
INCLUDEPATH += ../src-common ../src-agg ../objs ../src-unix
CONFIG += c++11
LIBS += ./cfdg.a -lpng
PRE_TARGETDEPS += /home/kiernan/code/contextfree/src-qt/cfdg.a
