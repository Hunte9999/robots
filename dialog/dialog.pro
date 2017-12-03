TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-roboti-Desktop_Qt_5_9_1_GCC_64bit-Debug/release/ -lroboti
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-roboti-Desktop_Qt_5_9_1_GCC_64bit-Debug/debug/ -lroboti
else:unix: LIBS += -L$$PWD/../build-roboti-Desktop_Qt_5_9_1_GCC_64bit-Debug/ -lroboti

INCLUDEPATH += ../roboti
DEPENDPATH += ../roboti

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-roboti-Desktop_Qt_5_9_1_GCC_64bit-Debug/release/libroboti.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-roboti-Desktop_Qt_5_9_1_GCC_64bit-Debug/debug/libroboti.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-roboti-Desktop_Qt_5_9_1_GCC_64bit-Debug/release/roboti.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-roboti-Desktop_Qt_5_9_1_GCC_64bit-Debug/debug/roboti.lib
else:unix: PRE_TARGETDEPS += $$PWD/../build-roboti-Desktop_Qt_5_9_1_GCC_64bit-Debug/libroboti.a
