#ifndef BITMAPFONT_H
#define BITMAPFONT_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include <iostream>
using namespace std;

class BitmapFont
{
public:
    BitmapFont(SDL_Surface *screen);
    ~BitmapFont();
    int LoadFont(const char *filename, int char_xw, int char_yw, int chars_nx, int chars_ny, const char *ascii_tbl);
    int LoadFont(const char *filename_font, const char *filename_inf);
    void DrawChar(int x, int y, char _char);
    void DrawChar(SDL_Surface *screen, int x, int y, char _char);
    void DrawText(int x, int y, const char *text);
    int GetCharXW(void);
    int GetCharYW(void);

private:
    SDL_Surface *Screen;
    SDL_Surface *FontImage;
    SDL_Rect ASCII_TAB[256];

    int CharXW;
    int CharYW;
};

#endif // BITMAPFONT_H
