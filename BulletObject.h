#ifndef BULLETOBJECT_H_INCLUDED
#define BULLETOBJECT_H_INCLUDED

#include "BaseObject.h"
#include "CommonFunc.h"

class BulletObject : public BaseObject
{
public:
    BulletObject();
    ~BulletObject();

    enum Bullet_Direction
    {
        Dir_Left=0,
        Dir_Right=1,
        Dir_Down=2,
        Dir_Up=3,
    };

    void set_x_val(const int& xVal) {x_val_=xVal;}
    void set_y_val(const int& yVal) {y_val_=yVal;}
    int get_x_val() const {return x_val_;}
    int get_y_val() const {return y_val_;}

    void set_is_move(const bool &isMove) {is_move_=isMove;}
    bool get_is_move() const {return is_move_;}

    void set_bullet_direction(const int &bulletDir) {bullet_direction_=bulletDir;}
    int get_bullet_direction() const {return bullet_direction_;}
    void HandleMove(const int &x_border,const int &y_border);

private:
    int x_val_;
    int y_val_;
    bool is_move_;
    int bullet_direction_;
};

#endif // BULLETOBJECT_H_INCLUDED
