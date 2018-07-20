TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
		demo.cpp

QMAKE_CFLAGS   += $$system(pkg-config --cflags sdl2)
QMAKE_CXXFLAGS += $$system(pkg-config --cflags sdl2)
QMAKE_LFLAGS   += $$system(pkg-config --libs sdl2)

include($$quote($$PWD/gl3w/gl3w.pri))

HEADERS += \
    common.h

DISTFILES += \
    first.frag \
    first.vert
