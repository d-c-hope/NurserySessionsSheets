#-------------------------------------------------
#
# Project created by QtCreator 2015-05-13T10:05:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SessionsBooking
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    childlistform.cpp \
    childlistreader.cpp \
    child.cpp \
    tablemodel.cpp \
    pagenavigator.cpp \
    newchildform.cpp \
    stackWidget.cpp \
    timeutils.cpp \
    editchildform.cpp \
    sessionsform.cpp \
    sessionsreader.cpp \
    sessionshelpers.cpp \
    attendancesheets.cpp \
    childWeeklySessions.cpp

HEADERS  += mainwindow.h \
    childlistform.h \
    childlistreader.h \
    child.h \
    tablemodel.h \
    pagenavigator.h \
    newchildform.h \
    stackWidget.h \
    timeutils.h \
    editchildform.h \
    sessionsform.h \
    sessionsreader.h \
    childWeeklySessions.h \
    sessionshelpers.h \
    attendancesheets.h

FORMS    += mainwindow.ui \
    childlistform.ui \
    newchildform.ui \
    editchildform.ui \
    sessionsform.ui

INCLUDEPATH += /Users/david_hope2/Desktop/boost_1_58_0

QMAKE_CXXFLAGS += -std=c++11

#INCLUDEPATH += C:/boost/boost_1_53_0/
#LIBS += "-LC:/boost/boost_1_53_0/stage/lib/"
