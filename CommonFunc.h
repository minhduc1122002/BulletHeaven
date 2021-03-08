#ifndef COMMONFUNC_H_INCLUDED
#define COMMONFUNC_H_INCLUDED

#include<iostream>
#include<SDL.h>
#include<string>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>

static SDL_Window* g_window=NULL;
static SDL_Renderer* g_screen=NULL;
static SDL_Event g_event;

// Screen
const int SCREEN_WIDTH=960;
const int SCREEN_HEIGHT=540;
const int SCREEN_BPP=32;

const int COLOR_KEY_R=167;
const int COLOR_KEY_G=175;
const int COLOR_KEY_B=180;

const int RENDER_DRAW_COLOR=255;

typedef struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;
};
#endif // COMMONFUNC_H_INCLUDED
