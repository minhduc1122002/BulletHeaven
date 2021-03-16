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

void BulletObject::HandleMove(const int &x_border,const int &y_border, const float &angle)
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
        if(angle==90)
        {
            rect_.y+=y_val_;
        }
        else if(angle==45)
        {
            rect_.y+=y_val_;
            rect_.x+=x_val_;
        }
        if(rect_.y>y_border || rect_.x>x_border)
        {
            is_move_=false;
        }
    }
    else if(bullet_direction_==Dir_Up)
    {
        if(angle==90)
        {
            rect_.y-=y_val_;
        }
        else if(angle==45)
        {
            rect_.y-=y_val_;
            rect_.x-=x_val_;
        }
        if(rect_.y<0 || rect_.x<0)
        {
            is_move_=false;
        }
    }
}
