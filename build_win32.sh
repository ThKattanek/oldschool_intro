#!/bin/bash

# QtBin Pfad bitte hier eintragen
qt_path=/usr/i686-w64-mingw32/bin/

"$qt_path"/qmake -r -spec win32-g++-cross -o Makefile
make --makefile=Makefile -j2