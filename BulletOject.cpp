#include "BulletObject.h"
using namespace std;

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
    if(angle==90)
    {
      rect_.y+=y_val_;
    }
    else if(angle==-90)
    {
        rect_.y-=y_val_;
    }
    else if(angle==45)
    {
       rect_.x+=x_val_-1;
       rect_.y+=y_val_;
    }
    else if(angle==135)
    {
        rect_.x-=x_val_-1;
        rect_.y+=y_val_;
    }
    if(rect_.y<0 || rect_.y>y_border)
    {
        is_move_=false;
    }
    if(rect_.x<0 || rect_.x>x_border)
    {
        is_move_=false;
    }
}
