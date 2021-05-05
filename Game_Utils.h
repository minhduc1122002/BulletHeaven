#ifndef COMMONFUNC_H_INCLUDED
#define COMMONFUNC_H_INCLUDED

#include<iostream>
#include<fstream>
#include<SDL.h>
#include <vector>
#include<iomanip>
#include <sstream>
#include<cmath>
#include<string>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
using namespace std;

static SDL_Window* g_window=NULL;
static SDL_Renderer* g_screen=NULL;
static SDL_Event g_event;

// Screen
const int SCREEN_WIDTH=800;
const int SCREEN_HEIGHT=1000;
const int SCREEN_BPP=32;
const double PI  =3.141592653589793238463;
const int COLOR_KEY_R=167;
const int COLOR_KEY_G=175;
const int COLOR_KEY_B=180;
const int RENDER_DRAW_COLOR=255;

bool CheckCollision(const SDL_Rect &object1,const SDL_Rect &object2);
string number_to_string(int number);
string GetHighScoreFromFile(string path);
void UpdateHighScore(string path,const int& score, string& old_high_score);
string RatingBaseOnScore(const long current_score);



#endif // COMMONFUNC_H_INCLUDED
