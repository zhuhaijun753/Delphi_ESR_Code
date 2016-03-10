#-------------------------------------------------
#
# Project created by QtCreator 2016-03-02T19:22:06
#
#-------------------------------------------------

QT += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Delphi_ESR_SENSOR
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    canconnect.cpp \
    reversing.cpp \
    planview.cpp \
    datathread.cpp \
    sensorview.cpp \
    tableview.cpp \
    fileio.cpp \
    rule.cpp \
    messagebox.cpp \
    video.cpp

HEADERS  += widget.h \
    canconnect.h \
    reversing.h \
    planview.h \
    datathread.h \
    sensorview.h \
    tableview.h \
    fileio.h \
    rule.h \
    mode.h \
    messagebox.h \
    video.h

FORMS    += widget.ui \
    messagebox.ui \
    video.ui

LIBS += -L$$PWD/../CANLIB_SIMPLE/ -lcanlib32

INCLUDEPATH += $$PWD/../CANLIB_SIMPLE
DEPENDPATH += $$PWD/../CANLIB_SIMPLE

RESOURCES += \
    images.qrc

