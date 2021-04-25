#include "Icon.h"
using namespace std;
Effect::Effect()
{
    width_frame_=0;
    height_frame_=0;
    is_move_=false;
}
Effect::~Effect()
{

}
bool Effect::LoadImg(string path, SDL_Renderer* screen)
{
    bool ret=BaseObject::LoadImg(path,screen);
    if(ret==true)
    {
        width_frame_=rect_.w;
        height_frame_=rect_.h;
    }
    return ret;
}

void Effect::MoveEffect(const int &x_border,const int &y_border)
{
    rect_.y+=2;
    if(rect_.y<0 || rect_.y>y_border)
    {
        is_move_=false;
    }
    if(rect_.x<0 || rect_.x>x_border)
    {
        is_move_=false;
    }
}
