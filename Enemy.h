#ifndef THREATOBJECT_H_INCLUDED
#define THREATOBJECT_H_INCLUDED

#include "Game_Utils.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include "MainObject.h"
#include "Icon.h"
#define Num_of_Frame_Enemy 1
using namespace std;
class Enemy:public BaseObject
{
public:
    Enemy();
    ~Enemy();

    //frame
    int get_width_frame() const {return width_frame_;}
    int get_height_frame() const {return height_frame_;}

    //position
    void set_x_pos_(const double &xPos) {x_pos_=xPos;}
    void set_y_pos_(const double &yPos) {y_pos_=yPos;}
    double get_x_pos_() const {return x_pos_;}
    double get_y_pos_() const {return y_pos_;}

    //type
    void set_type_threat(const double type_) {type=type_;}
    double get_type_threat() const {return type;}
    void set_y_limit(const double &yLimit) {y_limit_=yLimit;}
    void set_stats(SDL_Renderer* screen);

    //bullet
    bool canspawnbullet();
    void MakeBullet(vector<BulletObject*> &bullet,SDL_Renderer* screen,MainObject &spaceship);

    //movement
    void set_x_val_(const float &xVal) {x_val_=xVal;}
    void set_y_val_(const float &yVal) {y_val_=yVal;}
    void MoveThreat();

    //texture
    bool LoadImg(string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void set_clip();

    //action when die
    void increase_die() {die++;}
    bool check_die();
    int get_score() const {return score;}
    void Generate_Health(vector<Effect*>&health,SDL_Renderer* screen);

    //angle
    void rotate_angle();
    void set_angle_val(const double& angle_val) {angle_val_=angle_val;}
    void set_angle_(const double& angle_) {angle=angle_;}

private:
    double x_pos_;
    double y_pos_;
    double x_val_;
    double y_val_;

    double x_limit_;
    double y_limit_;

    double type;

    double angle;
    double angle_val_;
    double angle_move;

    int die;
    int score;
    int delay_shoot_time;

    int width_frame_;
    int height_frame_;

    SDL_Rect frame_clip_[Num_of_Frame_Enemy];
    int frame_;

    unsigned long long CurrentTime;
    unsigned long long LastTime;

};

#endif // THREATOBJECT_H_INCLUDED
