#ifndef THREATOBJECT_H_INCLUDED
#define THREATOBJECT_H_INCLUDED

#include "Game_Utils.h"
#include "Texture.h"
#include "Bullet.h"
#include "Character.h"
#include "Icon.h"
#define Num_of_Frame_Enemy 1
using namespace std;
class Enemy:public Texture
{
public:
    Enemy();
    ~Enemy();

    //frame
    int get_width_frame() const {return width_frame;}
    int get_height_frame() const {return height_frame;}

    //position
    void set_x_pos(const double &xPos) {x_pos=xPos;}
    void set_y_pos(const double &yPos) {y_pos=yPos;}
    double get_x_pos() const {return x_pos;}
    double get_y_pos() const {return y_pos;}

    //type
    void set_type_threat(const double type_) {type=type_;}
    double get_type_threat() const {return type;}
    void set_y_limit(const double &yLimit) {y_limit=yLimit;}
    void set_stats(SDL_Renderer* screen);

    //bullet
    bool canspawnbullet();
    void MakeBullet(vector<Bullet*> &bullet,SDL_Renderer* screen,Character &spaceship);
    void MakeBulletUponDeath(vector<Bullet*> &bullet,SDL_Renderer* screen);

    //movement
    void set_x_speed(const float &xSpeed) {x_speed=xSpeed;}
    void set_y_speed(const float &ySpeed) {y_speed=ySpeed;}
    void MoveThreat();

    //texture
    bool LoadTexture(string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void set_clip();

    //action when die
    void increase_die() {die++;}
    bool check_die();
    int get_score() const {return score;}
    void Generate_Health(vector<Icon*>&health,SDL_Renderer* screen);

    //angle
    void rotate_angle();
    void set_angle_rotate_speed(const double& angleSpeed) {angle_rotate_speed=angleSpeed;}
    void set_angle(const double& angle_) {angle=angle_;}

private:
    double x_pos;
    double y_pos;
    double x_speed;
    double y_speed;

    double y_limit;

    double type;

    double angle;
    double angle_rotate_speed;
    double angle_move;
    bool changespawn;
    bool reverse_direction;

    int die;
    int score;
    int delay_shoot_time;

    int width_frame;
    int height_frame;

    SDL_Rect frame_clip[Num_of_Frame_Enemy];
    int frame;

    unsigned long long CurrentTime;
    unsigned long long LastTime;

};

#endif // THREATOBJECT_H_INCLUDED
