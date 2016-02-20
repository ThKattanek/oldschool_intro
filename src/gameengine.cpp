#include "gameengine.h"

GameEngine::GameEngine(int sf,int breite,int hoehe,int bits,char *titel,int *err)
{
    cout << endl << "> GameEngine wird initialisiert...";

    int ret;

    ret = SDL_Init(SDL_INIT_VIDEO);
    if(ret < 0)
    {
        cout << "ERROR" << endl << "> Beim installieren von SDL_VIDEO: " << SDL_GetError() << endl;
        if(ret != 0) *err = -1;
        ende = true;
        return;
    }

    if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
     {
        cout << "ERROR" << endl << "> Beim installieren von SDL_AUDIO: " << SDL_GetError() << endl;
        cout << "SDL_FEHLERMELDUNG: " << SDL_GetError() << endl;
        if(ret != 0) *err = -1;
        ende = true;

       return;
     }

    xw = breite;
    yw = hoehe;
    colbits = bits;

    svm_flags = 0;

    if((sf & resize) == resize)
    {
        isResizeEnable = true;
        svm_flags |= SDL_WINDOW_RESIZABLE;
    }
    else isResizeEnable = false;

    if((sf & fullscreen) == fullscreen) svm_flags |= SDL_WINDOW_FULLSCREEN;
    if((sf & esc_ende) == esc_ende) EnabledESC_Ende = true; else EnabledESC_Ende = false;

    svm_flags |= SDL_WINDOW_OPENGL;
    main_window = SDL_CreateWindow(titel,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,xw, yw,svm_flags);
    renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_SOFTWARE);
    screen0 = SDL_GetWindowSurface(main_window);

    SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, xw, yw);

    if(screen0 == 0)
    {
        cout << "Es konnte kein Fenster geoeffnet werden: " << SDL_GetError() << endl;
        if(ret != 0) *err = -2;
        ende = true;
        return;
    }
    screen0_rec.x= 0;
    screen0_rec.y= 0;
    screen0_rec.w = xw;
    screen0_rec.h = yw;

    if(isResizeEnable)
    {
        screen1 = SDL_CreateRGBSurface(0,xw,yw,colbits,0,0,0,0);
        if(screen1 == 0)
        {
            cout << "Es konnte kein Surface1 erstellt werden: " << SDL_GetError() << endl;
            if(ret != 0) *err = -3;
            ende = true;
            return;
        }
        screen1_rec.x= 0;
        screen1_rec.y= 0;
        screen1_rec.w = xw;
        screen1_rec.h = yw;
    }

    ticks_new = SDL_GetTicks();
    ticks_old = ticks_new;

    EnabledViewFPS = false;
    ticksADD = 0;
    fps_frame_counter = 0;
    fps = 0;

    ende = false;

    /// Audio setzen ///
    for(int i=0;i<AUDIO_MUSIK_SLOTS;i++)musik[i]=0;

    if(Mix_OpenAudio(AUDIO_SAMPLERATE,MIX_DEFAULT_FORMAT,AUDIO_CHANNELS,AUDIO_BUFFERSIZE) == -1)
    {
        printf("Mix_Init: Failed to init required mod support!\n");
        printf("Mix_Init: %s\n", Mix_GetError());
        exit(2);
    }
    Mix_Init(MIX_INIT_MOD);

/*
#ifdef HAVE_MIX_INIT
 int initted;

 printf("About to call Mix_Init():\n");

 initted = Mix_Init(MIX_INIT_MOD);

 // We must have MOD support to have sound:
 if((initted & MIX_INIT_MOD) != MIX_INIT_MOD)
 {
   printf("Mix_Init: Failed to init required mod support!\n");
   printf("Mix_Init: %s\n", Mix_GetError());
   exit(2);
 }

 printf("Mix_Init() succeeded.\n");

#else
printf("Mix_Init() not detected by configure script.\n");


#endif

    cout << "Alles OK...";


    if(Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 4096))
    //if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096))
    //if(Mix_OpenAudio(44100, AUDIO_S16, 2, 4096))
    {
        cout << "Unable to open audio!" << endl;
        return;
      }
*/
    /// CallBack auf 0 setzen !!! ///
    RenderCallback = 0;

    *err = 0;

    cout << "OK" << endl;
}

GameEngine::~GameEngine()
{
    cout << "> GameEngine wird beendet...";

    for(int i=0;i<AUDIO_MUSIK_SLOTS;i++)
    {
        if(musik[i] != 0) Mix_FreeMusic(musik[i]);
    }
    Mix_CloseAudio();
    SDL_Quit();

    cout << "OK" << endl;
}

void GameEngine::ExitLoop()
{
    ende = true;
}

bool GameEngine::Loop()
{
    /// Framezeit und Fps berechnen ///
    ticks_new = SDL_GetTicks();
    frame_time = (ticks_new-ticks_old) / 1000.0f;
    ticksADD += (ticks_new-ticks_old);
    ticks_old = ticks_new;

    fps_frame_counter++;
    if(fps_frame_counter == fps_mittel_count)
    {
        ticksADD /= fps_mittel_count;
        fps_frame_counter = 0;
        fps = (1.0f/(ticksADD / 1000.0f));
        ticksADD = 0;
    }

    while (SDL_PollEvent (&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            ende = true;
            break;
        case SDL_WINDOWEVENT_RESIZED:
            xw = screen0_rec.w = event.window.data1;
            yw = screen0_rec.h = event.window.data2;
            //screen0 = SDL_SetVideoMode(xw,yw,colbits,svm_flags | SDL_HWSURFACE | SDL_DOUBLEBUF);
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                if(EnabledESC_Ende)ende = true;
                break;
            default:
                break;
            }
        }
    }

    if(isResizeEnable)
    {
        RenderVideo(screen1);
        SDL_SoftStretch(screen1,&screen1_rec,screen0,&screen0_rec);
    }
    else
    {
        RenderVideo(screen0);
    }

    if(EnabledViewFPS)
    {
        char fps_out[20];
        sprintf(fps_out,"FPS: %d",fps);
        stringRGBA(renderer,2,2,fps_out,255,255,255,100);
    }

    SDL_RenderPresent(renderer);
    //SDL_Delay(1);

    return ende;
}

void GameEngine::ViewFPS(bool status)
{
    EnabledViewFPS = status;
}

SDL_Surface* GameEngine::GetScreen()
{
    if(isResizeEnable) return screen1;
    else return screen0;
}

void GameEngine::NewObject(HColorScroll **obj)
{
    *obj = 0;
    if(isResizeEnable) *obj = new HColorScroll(screen1);
    else *obj = new HColorScroll(screen0);
}

void GameEngine::NewObject(GFXMap **obj)
{
    *obj = 0;
    if(isResizeEnable) *obj = new GFXMap(screen1);
    else *obj = new GFXMap(screen0);
}

void GameEngine::NewObject(BitmapFont **obj)
{
    *obj = 0;
    if(isResizeEnable) *obj = new BitmapFont(screen1);
    else *obj = new BitmapFont(screen0);
}

void GameEngine::NewObject(Starfield **obj)
{
    *obj = 0;
    if(isResizeEnable) *obj = new Starfield(renderer);
    else *obj = new Starfield(renderer);
}

void GameEngine::NewObject(SinusScroller **obj)
{
    *obj = 0;
    if(isResizeEnable) *obj = new SinusScroller(screen1);
    else *obj = new SinusScroller(screen0);
}

void GameEngine::DrawRect(int x, int y, int xw, int yw, Uint32 color)
{
    SDL_Surface *AktScreen;

    if(isResizeEnable) AktScreen = screen1;
    else AktScreen = screen0;

    SDL_Rect rec = {x,y,xw,yw+1};
    SDL_SetRenderDrawColor(renderer,color >> 24,color >> 16, color >> 8, color);
    SDL_RenderFillRect(renderer, &rec);
}

void GameEngine::RenderVideo(SDL_Surface *screen)
{
    if(ende) return;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    if(RenderCallback != 0) RenderCallback(this,frame_time);
}

void GameEngine::LoadMusik(int slotnr,const char *filename)
{
    if(slotnr >= AUDIO_MUSIK_SLOTS) return;
    if(musik[slotnr] != 0) Mix_FreeMusic(musik[slotnr]);

    musik[slotnr] = Mix_LoadMUS(filename);
}

void GameEngine::PlayMusik(int slotnr)
{
    if(musik[slotnr] == 0) return;
    Mix_PlayMusic(musik[slotnr],-1);
}

void GameEngine::StopMusik()
{
    Mix_PauseMusic();
}
