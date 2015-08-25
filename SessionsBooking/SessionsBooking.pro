#-------------------------------------------------
#
# Project created by QtCreator 2015-05-13T10:05:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4.8): QT += widgets



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
    childWeeklySessions.cpp \
    monthrange.cpp \
    appConstants.cpp \
    apputils.cpp \
    childlistexporter.cpp

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
    attendancesheets.h \
    monthrange.h \
    appConstants.h \
    apputils.h \
    childlistexporter.h

FORMS    += mainwindow.ui \
    childlistform.ui \
    newchildform.ui \
    editchildform.ui \
    sessionsform.ui

INCLUDEPATH += /usr/local/boost_1_58_0

#QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS_CXX11 = -std=c++14 -stdlib=libc++
CONFIG += c++11

#INCLUDEPATH += C:/boost/boost_1_53_0/
#LIBS += "-LC:/boost/boost_1_53_0/stage/lib/"

DISTFILES += \
    sessionsbooking.icns

RESOURCES += \
    images.qrc

macx: LIBS += /usr/local/boostBuild/lib/libboost_system.a
macx: LIBS += /usr/local/boostBuild/lib/libboost_filesystem.a

#INCLUDEPATH += $$PWD/../../../../../../usr/local/boostBuild/include
#DEPENDPATH += $$PWD/../../../../../../usr/local/boostBuild/include

#macx: PRE_TARGETDEPS += $$PWD/../../../../../../usr/local/boostBuild/lib/libboost_system.a
#macx: PRE_TARGETDEPS += $$PWD/../../../../../../usr/local/boostBuild/lib/libboost_filesystem.a


ICON = sessionsbooking.icns






