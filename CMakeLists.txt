cmake_minimum_required(VERSION 2.8)

project(oldscool_intro)

set(SOURCE src/main.cpp
    src/bitmapfont.cpp src/bitmapfont.h
    src/gameengine.cpp src/gameengine.h
    src/gfxmap.cpp src/gfxmap.h
    src/hcolorscroll.cpp src/hcolorscroll.h
    src/sinusscroller.cpp src/sinusscroller.h
    src/starfield.cpp src/starfield.h)

add_executable(oldscool_intro ${SOURCE})
target_link_libraries(oldscool_intro SDL SDL_gfx SDL_image SDL_mixer)

file(COPY daten DESTINATION .)