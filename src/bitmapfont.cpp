#include "bitmapfont.h"

BitmapFont::BitmapFont(SDL_Surface *screen)
{
    Screen = screen;
    FontImage = 0;
}

BitmapFont::~BitmapFont()
{
    if(FontImage != 0) SDL_FreeSurface(FontImage);
}

int BitmapFont::LoadFont(const char *filename_font, const char *filename_inf)
{
    /// Aufbereiten für LoadFont II ///
    //LoadFont(filename_font,32,32,10,10,"dsssss");
}

int BitmapFont::LoadFont(const char *filename, int char_xw, int char_yw, int chars_nx, int chars_ny, const char *ascii_tbl)
{
    if(FontImage != 0) SDL_FreeSurface(FontImage);

    FontImage = IMG_Load(filename);
    if(FontImage == NULL)
    {
        cout << "ERROR" << endl << "> Beim laden der Datei: " << filename << endl;
        return -1;
    }

    CharXW = char_xw;
    CharYW = char_yw;

    for(int i=0;i<256;i++)
    {
        ASCII_TAB[i].x = 0;
        ASCII_TAB[i].y = 0;
        ASCII_TAB[i].w = 0;
        ASCII_TAB[i].h = 0;
    }

    int char_anzahl = strlen(ascii_tbl);
    for(int i=0;i<char_anzahl;i++)
    {
        int posy = (i/chars_nx)*char_yw;
        int posx = (i-((i/chars_nx)*chars_nx))*char_xw;
        ASCII_TAB[ascii_tbl[i]].x = posx;
        ASCII_TAB[ascii_tbl[i]].y = posy;
        ASCII_TAB[ascii_tbl[i]].w = char_xw;
        ASCII_TAB[ascii_tbl[i]].h = char_yw;
    }
    return 0;
}

int BitmapFont::GetCharXW(void)
{
    return CharXW;
}

int BitmapFont::GetCharYW(void)
{
    return CharYW;
}

void BitmapFont::DrawChar(int x, int y, char _char)
{
    if(FontImage == 0) return;

    SDL_Rect dst_rec = {x,y,CharXW,CharYW};
    SDL_BlitSurface(FontImage,&ASCII_TAB[_char],Screen,&dst_rec);
}

void BitmapFont::DrawChar(SDL_Surface *screen, int x, int y, char _char)
{
    if(FontImage == 0) return;

    SDL_Rect dst_rec = {x,y,CharXW,CharYW};
    SDL_BlitSurface(FontImage,&ASCII_TAB[_char],screen,&dst_rec);
}

void BitmapFont::DrawText(int x, int y, const char *text)
{
    if(FontImage == 0) return;

    int char_anzahl = strlen(text);
    SDL_Rect dst_rec = {x,y,CharXW,CharYW};

    for(int i=0;i<char_anzahl;i++)
    {
        SDL_BlitSurface(FontImage,&ASCII_TAB[text[i]],Screen,&dst_rec);
        dst_rec.x += CharXW;
    }
}
