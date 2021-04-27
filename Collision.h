#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED

#include "Enemy.h"
#include "Character.h"
#include "Bullet.h"
#include "Icon.h"
#include "Game_Utils.h"
using namespace std;

void Collision(vector<Enemy*>&Enemy_List,Character &spaceship,
               vector<Bullet*> &Bullet_List,vector<Icon*>&Health_List,
               SDL_Renderer* screen,Mix_Chunk* dead,Mix_Chunk* hit,Mix_Chunk* Power,long &current_score,
               bool &GameOver);

#endif // COLLISION_H_INCLUDED
