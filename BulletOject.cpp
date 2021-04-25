#include "BulletObject.h"
using namespace std;

BulletObject::BulletObject()
{
    x_val_=0;
    y_val_=0;
    is_move_=false;
    angle=90;
}

BulletObject::~BulletObject()
{

}
void BulletObject::set_random_angle1()
{
    angle=rand()%(165-15+1)+15;
}
void BulletObject::set_random_angle2()
{
    angle=rand()%(360-0+1)+0;
}
void BulletObject::HandleMove(const int &x_border,const int &y_border)
{
    x_pos_+=x_val_*cos(angle*PI/180);
    y_pos_+=y_val_*sin(angle*PI/180);
    if(y_pos_<0 || y_pos_>y_border)
    {
        is_move_=false;
    }
    if(x_pos_<0 || x_pos_>x_border)
    {
        is_move_=false;
    }
    rect_.x=x_pos_;
    rect_.y=y_pos_;
}
