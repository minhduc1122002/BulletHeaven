#ifndef MAINOBJECT_H_INCLUDED
#define MAINOBJECT_H_INCLUDED

#include "Game_Utils.h"
#include "Texture.h"
#include "Bullet.h"

#define Num_of_Frame_Character 8
using namespace std;
class Character:public Texture
{
public:
    Character();
    ~Character();

    enum StateType
    {
        Normal=1,
        Pause=2
    };
    //texture
    bool LoadTexture(string path, SDL_Renderer* screen);
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
    vector<Bullet*> get_bullet_list1() const {return p_bullet_list1_;}
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
        if(life<3 && life>0)
        {
            life++;
        }
    }
    int get_life() {return life;}
    void got_hit();
    //frame
    int get_width_frame() const {return width_frame_;}
    int get_height_frame() const {return height_frame_;}
private:
    vector<Bullet*> p_bullet_list1_;
    bool canspawnbullet;

    int x_pos_;
    int y_pos_;
    int width_frame_;
    int height_frame_;

    int frame_;
    SDL_Rect frame_clip_[Num_of_Frame_Character];

    int life;
    int status_;

    bool input_mouse_;

    double angle;

    unsigned long long CurrentTime;
    unsigned long long LastTime;
    unsigned long long PausedTime;

};

#endif // MAINOBJECT_H_INCLUDED
