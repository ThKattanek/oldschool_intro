cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

project(oldscool_intro)

set(SOURCE src/main.cpp
    src/bitmapfont.cpp src/bitmapfont.h
    src/gameengine.cpp src/gameengine.h
    src/gfxmap.cpp src/gfxmap.h
    src/hcolorscroll.cpp src/hcolorscroll.h
    src/sinusscroller.cpp src/sinusscroller.h
    src/starfield.cpp src/starfield.h)

add_executable(oldscool_intro ${SOURCE})

if(UNIX)
target_link_libraries(oldscool_intro SDL SDL_gfx SDL_image SDL_mixer)
endif(UNIX)

if(WIN32)

message(Dies ist ein TEst ... ${CMAKE_SDL_LIBRARIES})

target_link_libraries(oldscool_intro ${CMAKE_SDL_LIBRARIES})
endif(WIN32)


file(COPY daten DESTINATION .)