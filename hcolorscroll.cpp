#include "hcolorscroll.h"

HColorScroll::HColorScroll(SDL_Surface *_screen)
{
    screen = _screen;
    teilung = 1;

    x = 0;
    y = 50;
    xw = 640;
    yw = 50;

    color_tab = 0;
    x_tab = 0;
    color_pointer = 0;

    color_tab_size = 1;
    color_tab = new Uint32(2);
    color_tab[0] = 0xffffffff;

    speed = 0;

    CalcWithNewSize();
}

void HColorScroll::Draw(float frame_time)
{
    color_pointer += (frame_time*speed);
    if(color_pointer > color_tab_size) color_pointer -= (float)color_tab_size;
    if(color_pointer < 0) color_pointer += (float)color_tab_size;

    int akt_col_pointer = (int)color_pointer;

    for(int i=0;i<teilung;i++)
    {
        SDL_Rect rec = {x_tab[i]+x,y,x_tab[i+1]-x_tab[i]+x,yw};
        SDL_FillRect(screen,&rec,color_tab[akt_col_pointer]);

        akt_col_pointer++;
        if(akt_col_pointer == color_tab_size) akt_col_pointer = 0;
    }
}

void HColorScroll::SetPos(int _x, int _y)
{
    x = _x;
    y = _y;
}

void HColorScroll::SetSize(int _xw, int _yw)
{
    xw = _xw;
    yw = _yw;

    CalcWithNewSize();
}

void HColorScroll::SetTeilung(int _teilung)
{
    teilung = _teilung;
    CalcWithNewSize();
}

void HColorScroll::SetSpeed(float _speed)
{
    speed = _speed * -1.0f;
}

void HColorScroll::CreateColorTab(Uint32 *colors,int color_count, int tab_size)
{
    color_tab_size = tab_size;
    if(color_tab != 0) delete color_tab;
    color_tab = new Uint32[color_tab_size];

    unsigned char r0,g0,b0,r1,g1,b1,r,g,b;
    float r_step,g_step,b_step;
    Uint32 rgb;

    float j=1.0f / (float)tab_size*(color_count-1);

    int pointer = 0;

    r1 = (colors[0] & 0x00ff0000) >> 16; g1 = (colors[0] & 0x0000ff00) >> 8; b1 = (colors[0] & 0x000000ff);

    for(int x=0;x<color_count-1;x++)
    {
        r0 = r1; g0 = g1; b0 = b1;
        r1 = (colors[x+1] & 0x00ff0000) >> 16; g1 = (colors[x+1] & 0x0000ff00) >> 8; b1 = (colors[x+1] & 0x000000ff);
        r_step = 1.0f / (r1-r0);g_step = 1.0f / (g1-g0);b_step = 1.0f / (b1-b0);

        for(float i=0.0f;i<1.0f;i+=j)
        {
            r = r0+(unsigned char)(i/r_step);
            g = g0+(unsigned char)(i/g_step);
            b = b0+(unsigned char)(i/b_step);
            rgb = (r<<16)  | (g<<8) | b;
            color_tab[pointer++] = rgb;
        }
    }
}

void HColorScroll::CalcWithNewSize(void)
{
    if(x_tab != 0) delete x_tab;

    x_tab_size = teilung+1;
    x_tab = new int[x_tab_size];

    float seg_size = (float)xw/(float)teilung;
    for(int i=0;i<teilung+1;i++)
    {
        x_tab[i] = (int)(float)i*seg_size;
    }
}
