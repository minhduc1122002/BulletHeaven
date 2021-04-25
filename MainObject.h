#ifndef MAINOBJECT_H_INCLUDED
#define MAINOBJECT_H_INCLUDED

#include "Game_Utils.h"
#include "BaseObject.h"
#include "BulletObject.h"

#define Num_of_Frame_MainObject 8
using namespace std;
class MainObject:public BaseObject
{
public:
    MainObject();
    ~MainObject();

    enum TurnType
    {
        Normal=1,
        Pause=2
    };
    //texture
    bool LoadImg(string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void set_clip();
    SDL_Rect GetRectFrame();
    //positions
    void set_positions(const int x,const int y)
    {
        x_pos_=x;
        y_pos_=y;
    }
    //bullet
    void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
    vector<BulletObject*> get_bullet_list1() const {return p_bullet_list1_;}
    void HandleBullet1(SDL_Renderer* des);
    void SpawnBullet(SDL_Renderer* screen);
    void RemoveBullet(const int &index);
    //life
    void life_decrease()
    {
        if(life>0)
        {
            life--;
        }
    }
    void life_increase()
    {
        if(life<3)
        {
            life++;
        }
    }
    int get_life() {return life;}
    void got_hit(Mix_Chunk* dead);
    //frame
    int get_width_frame() const {return width_frame_;}
    int get_height_frame() const {return height_frame_;}
private:
    vector<BulletObject*> p_bullet_list1_;
    bool canspawnbullet;

    int x_pos_;
    int y_pos_;
    int width_frame_;
    int height_frame_;

    int frame_;
    SDL_Rect frame_clip_[Num_of_Frame_MainObject];

    int life;
    int status_;

    Input input_type_;

    double angle;

    unsigned long long CurrentTime;
    unsigned long long LastTime;
    unsigned long long PausedTime;

};

#endif // MAINOBJECT_H_INCLUDED
