#ifndef MAINOBJECT_H_INCLUDED
#define MAINOBJECT_H_INCLUDED

#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include <vector>

#define SPEED 0.8
class MainObject:public BaseObject
{
public:
    MainObject();
    ~MainObject();

    enum TurnType
    {
        Turn_Right=0,
        Turn_Left=1,
        Go_Down=2,
        Go_Up=3,
    };
    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
    void set_clip();

    void MovePlayer();
    void set_bullet_list1(std::vector<BulletObject*> bullet_list1)
    {
        p_bullet_list1_=bullet_list1;
    }
    std::vector<BulletObject*> get_bullet_list1() const {return p_bullet_list1_;}
    void HandleBullet1(SDL_Renderer* des);
    void HandleBullet2(SDL_Renderer* des);


private:
    std::vector<BulletObject*> p_bullet_list1_;
    std::vector<BulletObject*> p_bullet_list2_;

    float x_pos_;
    float y_pos_;

    int width_frame_;
    int height_frame_;

    SDL_Rect frame_clip_[8];
    Input input_type_;
    int frame_;
    int status_;
};

#endif // MAINOBJECT_H_INCLUDED
