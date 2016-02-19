#Linux Build#
```Bash  
git clone https://tkattanek@bitbucket.org/tkattanek/oldscool_intro.git
cd oldscool_intro
mkdir linux_build
cd linux_build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j4
```

#Compile for Windows on Limux with MXE (mxe.cc)#
MXE evoriment must installed on your system
```Bash  
git clone https://tkattanek@bitbucket.org/tkattanek/oldscool_intro.git
cd oldscool_intro

nano cross_build_mxe.sh
--> Edit MXE_PATH = Set mxe path of your system

./cross_build_mxe.sh
```
#Libs#
- SDL
- SLD_image
- SDL_gfx
- SDL_mixer
#Was gehört mit zur Ausführbaren Datei in den Ordner
1. Ein Verzeichnis "daten"
2. Dort muss hinnein 3.xm / font1.png / font1m.png / font6.png / giana.png


#screenshot

![screenshot](http://picload.org/image/adolalp/oldscool_intro_s.png)