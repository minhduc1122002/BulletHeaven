#include "BulletObject.h"
#include<iostream>

BulletObject::BulletObject()
{
    x_val_=0;
    y_val_=0;
    is_move_=false;
}

BulletObject::~BulletObject()
{

}

void BulletObject::HandleMove(const int &x_border,const int &y_border, const double &angle)
{
    rect_.y+=y_val_*sin(angle*PI/180);
    rect_.x+=x_val_*cos(angle*PI/180);
    if(rect_.y<0 || rect_.y>y_border)
    {
        is_move_=false;
    }
    if(rect_.x<0 || rect_.x>x_border)
    {
        is_move_=false;
    }
}
