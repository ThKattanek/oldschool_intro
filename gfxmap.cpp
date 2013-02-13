#include "gfxmap.h"

GFXMap::GFXMap(SDL_Surface *screen)
{
    Screen = screen;
    Picture = NULL;
}

GFXMap::~GFXMap()
{
    if(Picture != NULL) SDL_FreeSurface(Picture);

    for(int i=0;i<MAX_ANIMATIONEN;i++) Animationen[i] = NULL;
}

int GFXMap::LoadTileSet(const char *filename, int raster_x, int raster_y)
{
    RasterX = raster_x;
    RasterY = raster_y;
    Picture = IMG_Load(filename);
    if(Picture == NULL)
    {
        cout << "ERROR" << endl << "> Beim laden der Datei: " << filename << endl;
        return -1;
    }
    else
    {
        return 0;
    }
}

void GFXMap::DrawTile(int x, int y, int tile_xpos, int tile_ypos)
{
    if(Picture == NULL) return;
    SDL_Rect scr_rec = {RasterX*tile_xpos,RasterY*tile_ypos,RasterX,RasterY};
    SDL_Rect dst_rec = {x,y,RasterX,RasterY};
    if(scr_rec.x > Picture->w) return;
    if(scr_rec.y > Picture->h) return;

    SDL_BlitSurface(Picture,&scr_rec,Screen,&dst_rec);
}

void GFXMap::SetAnimation(int animation_nr, int x_pos, int y_pos, int laenge)
{
    if(Animationen[animation_nr] != NULL) delete Animationen[animation_nr];
    Animationen[animation_nr] = new ANIMATION(x_pos,y_pos,laenge);
    Animationen[animation_nr]->XW = Picture->w/RasterX;
}

void GFXMap::SetAnimationSpeed(int animation_nr, float speed)
{
    if(Animationen[animation_nr] == NULL) return;
    Animationen[animation_nr]->speed = speed;
}

void GFXMap::DrawAnimation(int animation_nr, float frame_time, int x, int y)
{
    if(Animationen[animation_nr] == NULL) return;
    DrawTile(x,y,Animationen[animation_nr]->tile_xpos,Animationen[animation_nr]->tile_ypos);
    Animationen[animation_nr]->NetxFrame(frame_time);
}
