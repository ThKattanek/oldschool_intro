#include "gameengine.h"

#include <iostream>
using namespace std;

void InitDemo(GameEngine *ge);
void Render(GameEngine *ge, float frame_time);
void DrawScrollzeile(GameEngine* ge, float frame_time);

HColorScroll* hcolscroll[2];
BitmapFont* bmpfont0;
BitmapFont* bmpfont1;
BitmapFont* bmpfont2;
Starfield* starfield[3];
GFXMap* giana;
SinusScroller* scroller0;
SinusScroller* scroller1;

const char *scroll_text = "     COOLER SINUSSCROLLER ODER!? DAS NENNE ICH MAL OLDSCOOOOL :-) SOWAS KOMMT RAUS WENN MAN SICH EIGENTLICH NUR MIT SDL BESCHAEFTIGEN MOECHTE. DIESES INTRO IST EIN REINES SPASS PROJEKT OHNE TIEFEREN SINN......... ICH GRUESSE ALLE AUF FACEBOOK UND SPEZIELL MUGG, ANDREAS, PFLOCKI, HOEPPI, PLUE, HESSI, JENS, TOBI200, NETTI, C64 CAMPER UND UND UND .... (C)20.05.2012 BERLIN             ";

int main(int , char** )
{
    GameEngine *ge;
    int err;

    cout << "Oldscool Intro by Thorsten Kattanek" << endl;

    /// Initialisieren der GameEngine incl. Loop ///
    ge = new GameEngine(esc_ende,640,480,32,(char*)"INTRO BY THORSTEN KATTANEK ALIAS MR.EMU64 --- (C)2016   [SDL2 Version]",&err);
    if(err < 0) return 0;

    /// Demo Installieren ///
    InitDemo(ge);

    /// FPS anschalten ///
    ge->ViewFPS(true);

    /// CallBacks setzen ///
    ge->RenderCallback = bind(Render,_1,_2);

    SDL_ShowCursor(true);

    /// ************************void DrawScrollzeile(void)*************** ///

    while(!ge->Loop()){}
    delete ge;

    /// *************************************** ///

    return 0;
}

void InitDemo(GameEngine *ge)
{
    /// Paralax Sternenfeld erzeugen ///
    ge->NewObject((&starfield[0]));
    ge->NewObject((&starfield[1]));
    ge->NewObject((&starfield[2]));

    starfield[0]->SetStars(200,640,480,0xffffff50,150,0);
    starfield[1]->SetStars(150,640,480,0xffffff90,180,0);
    starfield[2]->SetStars(50,640,480,0xffffffd0,220,0);

    /// Giana Animation erstellen ///

    ge->NewObject(&giana);
    giana->LoadTileSet(DATA_PATH"giana.png",44,92);
    giana->SetAnimation(0,0,0,8);
    giana->SetAnimationSpeed(0,11);
    giana->SetAnimation(1,8,0,8);
    giana->SetAnimationSpeed(1,11);

    /// Oberer und untere animierter Farbbalken ///
    ge->NewObject(&hcolscroll[0]);
    ge->NewObject(&hcolscroll[1]);
    ge->NewObject(&hcolscroll[2]);

    hcolscroll[0]->SetPos(0,50);
    hcolscroll[0]->SetSize(640,1);
    hcolscroll[0]->SetTeilung(32);
    hcolscroll[0]->SetSpeed(-60);

    hcolscroll[1]->SetPos(0,430);
    hcolscroll[1]->SetSize(640,1);
    hcolscroll[1]->SetTeilung(32);
    hcolscroll[1]->SetSpeed(60);

    Uint32 colors0[5] = {0x00ff0000,0x00ffff00,0x0000ff00,0x000000ff,0x00ff0000};
    Uint32 colors1[5] = {0x00ff0000,0x000000ff,0x0000ff00,0x00ffff00,0x00ff0000};
    hcolscroll[0]->CreateColorTab(colors0,5,64);
    hcolscroll[1]->CreateColorTab(colors1,5,64);

    ge->NewObject(&bmpfont0);
    bmpfont0->LoadFont(DATA_PATH"font6.png",32,30,10,5,"ABCDEFGHIJKLMNOPQRSTUVWXYZ.,\"-+!?()?:;0123456789np");

    ge->NewObject(&bmpfont1);
    ge->NewObject(&bmpfont2);
    bmpfont1->LoadFont(DATA_PATH"font1.png",32,33,10,6," !\"    '()  ,-. 0123456789:; = ? ABCDEFGHIJKLMNOPQRSTUVWXYZ ");
    bmpfont2->LoadFont(DATA_PATH"font1m.png",32,33,10,6,"RSTUVWXYZ HIJKLMNOPQ ? YBCDEFG456789:; =  ,-. 0123 !\"   '()");
    //bmpfont1->LoadFont("daten/font1.png","daten/font1.inf");
    //bmpfont2->LoadFont("daten/font1m.png","daten/font1m.inf");

    /// Sinusscroller ///
    ge->NewObject(&scroller0);
    scroller0->InitScroller(bmpfont1,20,240,0);
    scroller0->SetScrollText(scroll_text);

    ge->NewObject(&scroller1);
    scroller1->InitScroller(bmpfont2,20,120,0.5);
    scroller1->SetScrollText(scroll_text);

    scroller0->SetSpeed(100,600);
    scroller1->SetSpeed(100,600);

    ge->LoadMusik(0,DATA_PATH"3.xm");
    ge->PlayMusik(0);
}

void Render(GameEngine* ge, float frame_time)
{
    starfield[0]->DrawStars(frame_time,0,0);
    starfield[1]->DrawStars(frame_time,0,0);
    starfield[2]->DrawStars(frame_time,0,0);

    scroller0->Draw(frame_time,0,152);
    scroller1->Draw(frame_time,0,390);

    hcolscroll[0]->SetPos(0,50);
    hcolscroll[0]->Draw(0);
    hcolscroll[0]->SetPos(0,91);
    hcolscroll[0]->Draw(frame_time);

    hcolscroll[1]->SetPos(0,389);
    hcolscroll[1]->Draw(0);
    hcolscroll[1]->SetPos(0,430);
    hcolscroll[1]->Draw(frame_time);

    ge->DrawRect(0,51,640,39,0x0000AA70);
    ge->DrawRect(0,390,640,39,0x0000AA70);
    ge->DrawRect(0,431,640,48,0x000000ff);

    static float giana_xpos = -44;
    if(giana_xpos > 320)
        giana->DrawAnimation(1,frame_time,giana_xpos,4);
    else
        giana->DrawAnimation(0,frame_time,giana_xpos,4);
    giana_xpos += frame_time * 50;
    if(giana_xpos >= 670) giana_xpos -= 670+44;

    static float frame_counter = 0.0f;
    char str00[20];
    sprintf(str00,"TIME: %4.2f",frame_counter);
    bmpfont0->DrawText(10,440,str00);
    frame_counter += frame_time;
}
