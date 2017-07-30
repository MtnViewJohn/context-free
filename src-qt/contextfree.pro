#-------------------------------------------------
#
# Project created by QtCreator 2017-07-09T22:19:31
#
#-------------------------------------------------

QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = contextfree
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cfdg_highlighter.cpp \
    qtcanvas.cpp \
    qtsystem.cpp

HEADERS  += mainwindow.h \
    cfdg_highlighter.h \
    qtcanvas.h \
    cf-util.h \
    qtsystem.h


FORMS    += mainwindow.ui
INCLUDEPATH += ../src-common ../src-agg ../objs ../src-unix ../src-win/derived ../src-common/agg-extras
CONFIG += c++11
LIBS += ./cfdg.a -lpng -pthread
PRE_TARGETDEPS += /home/kiernan/code/contextfree/src-qt/cfdg.a
