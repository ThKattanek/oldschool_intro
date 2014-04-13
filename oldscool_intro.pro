TEMPLATE = app
CONFIG -= app_bundle
CONFIG -= qt

linux-g++-32{
DESTDIR = "bin/linux_32bit"
TARGET = start
LIBS += -lSDL -lSDL_gfx -lSDL_image -lSDL_mixer
}

linux-g++-64{
TARGET = start
DESTDIR = "bin/linux_64bit"
LIBS += -lSDL -lSDL_gfx -lSDL_image -lSDL_mixer
}

win32-g++-cross{
TARGET = start
DESTDIR = "bin/win_x32"
LIBS += -lmingw32 -lSDLmain -lSDL -lSDL_gfx -lSDL_image -lSDL_mixer
}

win64-g++-cross{
TARGET = start
DESTDIR = "bin/win_x64"
LIBS += -lmingw32 -lSDLmain -lSDL -lSDL_gfx -lSDL_image -lSDL_mixer
}

SOURCES += \
    main.cpp \
    gameengine.cpp \
    hcolorscroll.cpp \
    gfxmap.cpp \
    starfield.cpp \
    sinusscroller.cpp \
    bitmapfont.cpp

HEADERS += \
    gameengine.h \
    hcolorscroll.h \
    gfxmap.h \
    starfield.h \
    sinusscroller.h \
    bitmapfont.h

OTHER_FILES += \
    doc/doc \
    readme.md \
    daten/luigi.png \
    daten/giana.png \
    daten/font7.png \
    daten/font7 \
    daten/font6.png \
    daten/font6 \
    daten/font5.png \
    daten/font5 \
    daten/font4.png \
    daten/font3.png \
    daten/font2.png \
    daten/font1m.png \
    daten/font1m.inf \
    daten/font1.png \
    daten/font1.inf \
    daten/3.xm \
    build_win32.sh \
    build_win64.sh

















