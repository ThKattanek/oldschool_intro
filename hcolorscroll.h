#ifndef HCOLORSCROLL_H
#define HCOLORSCROLL_H

#include <SDL/SDL.h>

#include <iostream>
using namespace std;

class HColorScroll
{
public:    
    HColorScroll(SDL_Surface *screen);
    void Draw(float frame_time=0);
    void SetPos(int _x, int _y);
    void SetSize(int _xw, int _yw);
    void SetTeilung(int _teilung);
    void SetSpeed(float _speed);
    void CreateColorTab(Uint32 *colors,int color_count, int tab_size);

private:
    void CalcWithNewSize(void);

private:
    SDL_Surface *screen;

    int x;
    int y;
    int xw;
    int yw;
    int teilung;

    int color_tab_size;
    Uint32 *color_tab;
    float color_pointer;

    int x_tab_size;
    int *x_tab;

    float speed;
};

#endif // HCOLORSCROLL_H
