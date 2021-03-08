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

void BulletObject::HandleMove(const int &x_border,const int &y_border)
{
    if(bullet_direction_==Dir_Right)
    {
        rect_.x+=x_val_;
        if(rect_.x>x_border)
        {
            is_move_=false;
        }
    }
    else if(bullet_direction_==Dir_Left)
    {
        rect_.x-=x_val_;
        if(rect_.x<0)
        {
            is_move_=false;
        }
    }
    else if(bullet_direction_==Dir_Down)
    {
        rect_.y+=y_val_;
        if(rect_.y>y_border)
        {
            is_move_=false;
        }
    }
    else if(bullet_direction_==Dir_Up)
    {
        rect_.y-=y_val_;
        if(rect_.y<0)
        {
            is_move_=false;
        }
    }
}
