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
    video.cpp \
    videothread.cpp

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
    video.h \
    videothread.h

FORMS    += widget.ui \
    messagebox.ui \
    video.ui

#CANLIB
INCLUDEPATH += $$PWD/../CANLIB_SIMPLE
DEPENDPATH += $$PWD/../CANLIB_SIMPLE
LIBS += -L$$PWD/../CANLIB_SIMPLE/ -lcanlib32

#OPENCV
INCLUDEPATH += $$PWD/../OPENCV/include
DEPENDPATH += $$PWD/../OPENCV/include

LIBS += -L$$PWD/../OPENCV/bin/libopencv_calib3d2411d.dll \
        $$PWD/../OPENCV/bin/libopencv_contrib2411d.dll \
        $$PWD/../OPENCV/bin/libopencv_core2411d.dll \
        $$PWD/../OPENCV/bin/libopencv_features2d2411d.dll \
        $$PWD/../OPENCV/bin/libopencv_highgui2411d.dll \
        $$PWD/../OPENCV/bin/libopencv_imgproc2411d.dll \

RESOURCES += \
    images.qrc

