#ifndef GFXMAP_H
#define GFXMAP_H

#define MAX_ANIMATIONEN 256

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include <iostream>
using namespace std;

class ANIMATION
{
public:
    ANIMATION(int x=0,int y=0, int len=0)
    {
        tile_xpos = start_x = x;
        tile_ypos = start_y=y;
        laenge = len;

        ani_pos = 0;
        speed = 0;
    }

    void NetxFrame(float frame_time)
    {
        ani_pos += frame_time*speed;
        if(ani_pos >= laenge) ani_pos -= laenge;
        if(ani_pos <= 0) ani_pos += laenge;

        //tile_xpos = ani_pos+start_x;
        int xcalc = start_x + (int)ani_pos;
        tile_ypos = start_y + xcalc/XW;
        tile_xpos = (xcalc-(XW*(xcalc/XW)));
    }

    int start_x;
    int start_y;
    int laenge;

    int XW;

    float speed;
    float ani_pos;

    int tile_xpos,tile_ypos;
};

class GFXMap
{
public:
    GFXMap(SDL_Surface *screen);
    ~GFXMap();
    int LoadTileSet(const char* filename, int raster_x, int raster_y);
    void DrawTile(int x, int y, int tile_xpos, int tile_ypos);
    void SetAnimation(int animation_nr, int x_pos, int y_pos, int laenge);
    void SetAnimationSpeed(int animation_nr,float speed);
    void DrawAnimation(int animation_nr, float frame_time, int x, int y);

private:
    SDL_Surface* Picture;
    SDL_Surface* Screen;
    int RasterX;
    int RasterY;

    ANIMATION *Animationen[MAX_ANIMATIONEN];
};

#endif // GFXMAP_H
