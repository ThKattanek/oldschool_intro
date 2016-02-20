#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
using namespace std;

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "tr1/functional"
using namespace std::tr1;
using namespace std::tr1::placeholders;

/// Alle einzelnen Objekte ///
#include "hcolorscroll.h"
#include "gfxmap.h"
#include "bitmapfont.h"
#include "starfield.h"
#include "sinusscroller.h"

#define fps_mittel_count 10
#define AUDIO_SAMPLERATE 44100
#define AUDIO_FOTMAT AUDIO_S16   // 16Bit Stereo
#define AUDIO_CHANNELS 2
#define AUDIO_BUFFERSIZE 4096
#define AUDIO_MUSIK_SLOTS 16

enum ge_start_flags
{
    fullscreen = 1,
    resize = 2,
    esc_ende = 4
};

class GameEngine
{
public:
    GameEngine(int sf=esc_ende,int breite=640,int hoehe=480,int bits=32,char* titel="GameEngine",int *err=0);
    ~GameEngine();

    void ExitLoop(void);
    bool Loop();
    void ViewFPS(bool status);
    SDL_Surface *GetScreen(void);
    void NewObject(HColorScroll **obj);
    void NewObject(GFXMap **obj);
    void NewObject(BitmapFont **obj);
    void NewObject(Starfield **obj);
    void NewObject(SinusScroller **obj);

    void DrawRect(int x, int y, int xw, int yw, Uint32 color);

    void LoadMusik(int slotnr, const char *filename);
    void PlayMusik(int slotnr);
    void StopMusik();

    /// CallBacks ///
    function<void(GameEngine*,float)> RenderCallback;

private:
    void RenderVideo(SDL_Surface* screen);
    int svm_flags;
    bool ende, EnabledESC_Ende;
    SDL_Event event;
    int xw,yw,colbits;
    bool isResizeEnable;
    SDL_Window *main_window;
    SDL_Surface *screen0;
    SDL_Surface *screen1;
    SDL_Renderer *renderer;

    int ticks_old,ticks_new;
    float frame_time;

    long int ticksADD;
    int fps_frame_counter;
    int fps;
    bool EnabledViewFPS;
    SDL_Rect screen0_rec,screen1_rec;

    Mix_Music *musik[AUDIO_MUSIK_SLOTS];
};

#endif // GAMEENGINE_H
