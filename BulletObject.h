#ifndef BULLETOBJECT_H_INCLUDED
#define BULLETOBJECT_H_INCLUDED

#include "BaseObject.h"
#include "CommonFunc.h"
class BulletObject : public BaseObject
{
public:
    BulletObject();
    ~BulletObject();

    void set_x_val(const float& xVal) {x_val_=xVal;}
    void set_y_val(const float& yVal) {y_val_=yVal;}
    int get_x_val() const {return x_val_;}
    int get_y_val() const {return y_val_;}

    void set_is_move(const bool &isMove) {is_move_=isMove;}
    bool get_is_move() const {return is_move_;}

    void HandleMove(const int &x_border,const int &y_border, const double &angle);

private:
    float x_val_;
    float y_val_;
    bool is_move_;
};

#endif // BULLETOBJECT_H_INCLUDED
