#ifndef BULLETOBJECT_H_INCLUDED
#define BULLETOBJECT_H_INCLUDED

#include "BaseObject.h"
#include "Game_Utils.h"
using namespace std;
class BulletObject : public BaseObject
{
public:
    BulletObject();
    ~BulletObject();

    void set_x_val(const double& xVal) {x_val_=xVal;}
    void set_y_val(const double& yVal) {y_val_=yVal;}
    void set_angle(const double& angle_) {angle=angle_;}

    void set_pos(const double& xPos, const double& yPos)
    {
        x_pos_=xPos;
        y_pos_=yPos;
    }

    int get_x_val() const {return x_val_;}
    int get_y_val() const {return y_val_;}

    void set_is_move(const bool &isMove) {is_move_=isMove;}
    void set_random_angle1();
    void set_random_angle2();
    bool get_is_move() const {return is_move_;}

    void HandleMove(const int &x_border,const int &y_border);

private:
    double x_val_;
    double y_val_;
    double x_pos_;
    double y_pos_;
    double angle;
    bool is_move_;
};

#endif // BULLETOBJECT_H_INCLUDED
