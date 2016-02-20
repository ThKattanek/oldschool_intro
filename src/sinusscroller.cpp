#include "sinusscroller.h"

SinusScroller::SinusScroller(SDL_Surface *screen)
{
    Screen = screen;
    ScreenTmp = NULL;
    ScrollZeile = NULL;
    ScrollText = NULL;
    SinTab = NULL;
}

SinusScroller::~SinusScroller()
{
    if(ScreenTmp != NULL) delete ScreenTmp;
    if(ScrollZeile != NULL) delete ScrollZeile;
    if(SinTab != NULL) delete SinTab;
}

void SinusScroller::InitScroller(BitmapFont *bmpfont, int xchar_anzahl, int yw, float start_sin)
{
    Font = bmpfont;
    XCharAnzahl = xchar_anzahl;

    XW = (XCharAnzahl+1) * Font->GetCharXW();
    if(yw < Font->GetCharYW()) yw = Font->GetCharYW();
    YW = yw;
    CharXW = Font->GetCharXW();

    ScreenTmp = SDL_CreateRGBSurface(0,XW-CharXW,YW,32,0,0,0,0);
    SDL_SetColorKey(ScreenTmp,SDL_TRUE,0);
    ScrollZeile = new char[XCharAnzahl];
    for(int i=0;i<XCharAnzahl;i++) ScrollZeile[i] = 0x20;

    SinTab = new int[XW];

    float mul = 1.0f/(float)XW;
    float freq = 1;

    int Amplitude = yw-Font->GetCharYW();

    for(int i=0;i<XW;i++) SinTab[i] = (Amplitude/2)*sin(2*3.1415926*freq*i*mul)+(Amplitude/2);

    if((start_sin >=0) && (start_sin <= 1)) SinScroll = (float)XW * start_sin;
    else SinScroll = 0;

    ScrollTextPointer = 0;
    XVersatz = 0;

    ScrollSpeed = 150;
    SinSpeed = 800;
}

void SinusScroller::SetScrollText(const char *scrolltext)
{
    ScrollText = scrolltext;
}

void SinusScroller::SetSpeed(float scrollspeed, float sinspeed)
{
    ScrollSpeed = scrollspeed;
    SinSpeed = sinspeed;
}

void SinusScroller::Draw(float frame_time, int x, int y)
{
    SDL_FillRect(ScreenTmp,0,0);


    int sin_pointer = (CharXW-(int)XVersatz) + SinScroll;
    int i=0;
    if(sin_pointer >= XW) sin_pointer -= XW;
    while(i<(XCharAnzahl+1))
    {
        Font->DrawChar(ScreenTmp, i*CharXW-(int)XVersatz,SinTab[sin_pointer],ScrollZeile[i]);
        sin_pointer += CharXW;
        if(sin_pointer >= XW) sin_pointer -= XW;
        i++;
    }

    SinScroll += frame_time*SinSpeed;
    if(SinScroll >= (float)XW)
    {
        SinScroll -= (float)XW;
    }

    XVersatz += frame_time*ScrollSpeed;


    if(XVersatz >= (float)CharXW)
    {
        XVersatz-=(float)CharXW;

        for(int i=0;i<(XCharAnzahl);i++) ScrollZeile[i]=ScrollZeile[i+1];
        char zeichen = ScrollText[ScrollTextPointer++];
        if(zeichen == 0)
        {
            ScrollTextPointer = 0;
            zeichen = ScrollText[ScrollTextPointer++];
        }
        ScrollZeile[XCharAnzahl]=zeichen;
    }

    SDL_Rect rec = {x,y,0,0};
    SDL_BlitSurface(ScreenTmp,0,Screen,&rec);
}
