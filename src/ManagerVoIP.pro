#-------------------------------------------------
#
# Project created by QtCreator 2014-02-19T13:12:02
#
#-------------------------------------------------

include(wizard.pri)

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ManagerVoIP
TEMPLATE = app

LIBS += -lamc

SOURCES += main.cpp\
        managervoip.cpp \
    SQLite.cpp \
    settings.cpp \
    IPFrame.cpp \
    movedbox.cpp

HEADERS  += managervoip.h \
    SQLite.h \
    settings.h \
    IPFrame.h \
    movedbox.h

FORMS    += managervoip.ui \
    settings.ui

RESOURCES += \
    resource.qrc
