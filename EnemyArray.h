#ifndef ENEMYARRAY_H_INCLUDED
#define ENEMYARRAY_H_INCLUDED

#include "Enemy.h"
#include "Game_Utils.h"

const int Num_of_ThreatArray1=5;
const int Num_of_ThreatArray2=4;
const int Num_of_ThreatArray3=2;
const int Num_of_ThreatArray4=1;
const int Num_of_ThreatArray5=3;

void EnemyArray_Type1(vector<Enemy*> &EnemyArray,SDL_Renderer* screen);
void EnemyArray_Type2(vector<Enemy*> &EnemyArray,SDL_Renderer* screen);
void EnemyArray_Type3(vector<Enemy*> &EnemyArray,SDL_Renderer* screen);
void EnemyArray_Type4(vector<Enemy*> &EnemyArray,SDL_Renderer* screen);
void EnemyArray_Type5(vector<Enemy*> &EnemyArray,SDL_Renderer* screen);
void EnemyArray_Type6(vector<Enemy*> &EnemyArray,SDL_Renderer* screen);
void EnemyArray_Type7(vector<Enemy*> &EnemyArray,SDL_Renderer* screen);
void EnemyBoss(vector<Enemy*> &EnemyArray,SDL_Renderer* screen);

void GenerateEnemy(vector<Enemy*> &Enemy_List,SDL_Renderer* screen,int &wave);

#endif // ENEMYARRAY_H_INCLUDED
