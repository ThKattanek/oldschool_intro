#!/bin/bash

# QtBin Pfad bitte hier eintragen
qt_path=/usr/x86_64-w64-mingw32/bin/

"$qt_path"/qmake -r -spec win64-g++-cross -o Makefile
make --makefile=Makefile -j2