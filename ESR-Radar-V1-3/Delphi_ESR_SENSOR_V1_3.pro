#-------------------------------------------------
#
# Project created by QtCreator 2016-03-21T19:18:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Delphi_ESR_SENSOR_V1_3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    canconnect.cpp \
    data.cpp \
    matrix.cpp \
    reversing.cpp \
    rule.cpp \
    view.cpp \
    video.cpp \
    toolradar.cpp \
    table.cpp \
    toolcamera.cpp \
    toolrecode.cpp \
    recode.cpp \
    objecttrajectory.cpp

HEADERS  += mainwindow.h \
    canconnect.h \
    data.h \
    defines.h \
    matrix.h \
    reversing.h \
    rule.h \
    view.h \
    video.h \
    toolradar.h \
    table.h \
    toolcamera.h \
    toolrecode.h \
    recode.h \
    objecttrajectory.h

FORMS    += mainwindow.ui \
    video.ui \
    toolradar.ui \
    table.ui \
    toolcamera.ui \
    toolrecode.ui \
    objecttrajectory.ui

RESOURCES += \
    image.qrc

#canlib
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../CANLIB_SIMPLE/ -lcanlib32
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../CANLIB_SIMPLE/ -lcanlib32
else:unix: LIBS += -L$$PWD/../CANLIB_SIMPLE/ -lcanlib32

INCLUDEPATH += $$PWD/../CANLIB_SIMPLE
DEPENDPATH += $$PWD/../CANLIB_SIMPLE

#opencv
INCLUDEPATH += $$PWD/../OPENCV/include

LIBS += $$PWD/../OPENCV/bin/libopencv_calib3d2411d.dll \
        $$PWD/../OPENCV/bin/libopencv_contrib2411d.dll \
        $$PWD/../OPENCV/bin/libopencv_core2411d.dll \
        $$PWD/../OPENCV/bin/libopencv_features2d2411d.dll \
        $$PWD/../OPENCV/bin/libopencv_highgui2411d.dll \
        $$PWD/../OPENCV/bin/libopencv_imgproc2411d.dll \
