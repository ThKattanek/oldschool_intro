#include "starfield.h"
#include <stdlib.h>

Starfield::Starfield(SDL_Renderer *renderer)
{
    this->renderer = renderer;

    StarAnzahl = 0;
    StarBuffer = NULL;

    /*
    star_anz = _stars;
    stars = new Star*[star_anz];

    for(int i=0; i<star_anz;i++)
    {
        stars[i] = new Star(rand() % Screen->w,rand() % Screen->h);
    }

    speed_add_wert = _speed;
    akt_pos_x = 0.0f;
    */
} 

Starfield::~Starfield()
{
    delete StarBuffer;
}

void Starfield::SetStars(int star_anzahl, int xw, int yw, Uint32 color, float xspeed, float yspeed)
{
    if(StarBuffer != 0) delete StarBuffer;

    StarAnzahl = star_anzahl;
    XW = xw;
    YW = yw;
    StarColor = color;
    XSpeed = xspeed;
    YSpeed = yspeed;

    StarBuffer = new Star*[StarAnzahl];
    for(int i=0;i<StarAnzahl;i++) StarBuffer[i] = new Star(rand() % XW,rand() % YW);
}

void Starfield::DrawStars(float frame_time,int x, int y)
{
    if(StarBuffer == NULL) return;

    for(int i=0;i<StarAnzahl;i++)
    {        
        SDL_SetRenderDrawColor(renderer,StarColor >> 24,StarColor >> 16, StarColor >> 8, StarColor);
        SDL_RenderDrawPoint(renderer,StarBuffer[i]->pos_x+x,StarBuffer[i]->pos_y+y);

        StarBuffer[i]->pos_x += frame_time*XSpeed;
        if(StarBuffer[i]->pos_x >= XW) StarBuffer[i]->pos_x -= XW;
        if(StarBuffer[i]->pos_x <= 0) StarBuffer[i]->pos_x += XW;

        StarBuffer[i]->pos_y += frame_time*YSpeed;
        if(StarBuffer[i]->pos_y >= YW) StarBuffer[i]->pos_y -= YW;
        if(StarBuffer[i]->pos_y <= 0) StarBuffer[i]->pos_y += YW;
    }
}
