cmake_minimum_required(VERSION 2.8)

project(oldscool_intro)

# set( CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s -Os")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s -Os")

set(SOURCE src/main.cpp
    src/bitmapfont.cpp src/bitmapfont.h
    src/gameengine.cpp src/gameengine.h
    src/gfxmap.cpp src/gfxmap.h
    src/hcolorscroll.cpp src/hcolorscroll.h
    src/sinusscroller.cpp src/sinusscroller.h
    src/starfield.cpp src/starfield.h)

add_executable(oldscool_intro ${SOURCE})

if(UNIX)
target_link_libraries(oldscool_intro SDL2 SDL2_gfx SDL2_image SDL2_mixer)
endif(UNIX)

if(WIN32)
target_link_libraries(oldscool_intro ${CMAKE_SDL2_LIBS})
endif(WIN32)


file(COPY daten DESTINATION .)
