#!/bin/bash
# windows binary cross compiled with MXE (http://mxe.cc/)
# by thorsten kattanek 2016

# You must set MXE Path !!
MXE_ROOT_PATH=/media/daten/mxe


###############################################################################

BUILD_PATH="./windows_build"
MXE_USR_PATH="$MXE_ROOT_PATH/usr"
MXE_BIN_PATH="$MXE_USR_PATH/bin"

export PATH="$MXE_BIN_PATH":$PATH

# check of exist build dir
if [ -d "$BUILD_PATH" ] ; then
# build dir ist exist
# remove
rm -rf "$BUILD_PATH"
# create build dir
mkdir "$BUILD_PATH"
else
# build dir is not exist
# create build dir
mkdir "$BUILD_PATH"
fi

# change to build dir
cd "$BUILD_PATH"

# cmake run
cmake -DCMAKE_BUILD_TYPE=Release\
      -DCMAKE_TOOLCHAIN_FILE="$MXE_USR_PATH/i686-w64-mingw32.static/share/cmake/mxe-conf.cmake"\
      -DCMAKE_SDL_LIBRARIES="`i686-w64-mingw32.static-sdl-config --libs` `i686-w64-mingw32.static-pkg-config SDL_image SDL_mixer SDL_gfx --libs`"\
      ..
# build run
make -j8