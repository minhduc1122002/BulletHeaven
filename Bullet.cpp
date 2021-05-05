#include "Bullet.h"
using namespace std;

Bullet::Bullet()
{
    x_speed=0;
    y_speed=0;
    is_move=false;
    angle=90;
    type=1;
    starting_point=0;
}

Bullet::~Bullet()
{

}
void Bullet::set_random_angle1()
{
    angle=rand()%(165-15+1)+15;
}
void Bullet::set_random_angle2()
{
    angle=rand()%(360+0+1);
}
void Bullet::set_random_angle3()
{
    angle=rand()%(120+120+1)-120;
}
void Bullet::HandleMove(const int &x_border,const int &y_border)
{
    if(type==1)
    {
        x_pos+=x_speed*cos(angle*PI/180);
        y_pos+=y_speed*sin(angle*PI/180);
    }
    else if(type==2)
    {
        y_pos+=1;
        x_pos=50*sin(PI*y_pos/100)+starting_point;
    }
    else if(type==3)
    {
        x_pos+=1;
        y_pos=50*sin(PI*x_pos/100)+starting_point;
    }
    else if(type==4)
    {
        x_pos+=1;
        y_pos=50*sin(PI*x_pos/100+PI)+starting_point;
    }
    if(y_pos<0 || y_pos>y_border)
    {
        is_move=false;
    }
    if(x_pos<0 || x_pos>x_border)
    {
        is_move=false;
    }
    Rect.x=x_pos;
    Rect.y=y_pos;
}
