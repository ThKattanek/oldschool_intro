#ifndef SINUSSCROLLER_H
#define SINUSSCROLLER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "bitmapfont.h"
#include <math.h>

#include <iostream>
using namespace std;

class SinusScroller
{
public:
    SinusScroller(SDL_Surface *screen);
    ~SinusScroller();
    void InitScroller(BitmapFont *bmpfont, int xchar_anzahl, int yw, float start_sin);
    void SetScrollText(const char *scrolltext);
    void SetSpeed(float scrollspeed, float sinspeed);
    void Draw(float frame_time, int x, int y);

private:
    SDL_Surface *Screen;
    SDL_Surface *ScreenTmp;

    BitmapFont *Font;

    int XCharAnzahl;
    int CharXW;
    int XW,YW;

    char *ScrollZeile;
    const char *ScrollText;
    int *SinTab;

    float SinScroll;
    int ScrollTextPointer;

    float XVersatz;

    float ScrollSpeed,SinSpeed;

};

#endif // SINUSSCROLLER_H
