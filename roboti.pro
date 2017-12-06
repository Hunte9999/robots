#-------------------------------------------------
#
# Project created by QtCreator 2017-11-08T19:18:58
#
#-------------------------------------------------

QT       -= gui

TARGET = roboti
TEMPLATE = lib
CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    module.cpp \
    manager.cpp \
    component.cpp \
    generator.cpp \
    sensor.cpp \
    movcomp.cpp \
    managecomp.cpp \
    movmanagecomp.cpp \
    place.cpp \
    ai.cpp \
    env.cpp \
    ti.cpp \
    obstacle.cpp \
    myvector.cpp

HEADERS += \
    module.h \
    manager.h \
    component.h \
    generator.h \
    sensor.h \
    movcomp.h \
    managecomp.h \
    movmanagecomp.h \
    place.h \
    ai.h \
    env.h \
    ti.h \
    obstacle.h \
    myvector.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
