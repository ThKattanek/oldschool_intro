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

Bsp.: with integrated script for MXE environment (cross_build.sh)

./cross_build.sh /opt/mxe i686 static
```
#Libs#
- SDL2
- SLD2_image
- SDL2_gfx
- SDL2_mixer

#This all must in the daten directory
- 3.xm
- font1.png
- font1m.png
- font6.png
- giana.png


#Screenshot

![screenshot](http://picload.org/image/adolalp/oldscool_intro_s.png)