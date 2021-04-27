#include "Icon.h"
using namespace std;
Icon::Icon()
{
    width_frame_=0;
    height_frame_=0;
    is_move_=false;
}
Icon::~Icon()
{

}
bool Icon::LoadTexture(string path, SDL_Renderer* screen)
{
    bool ret=Texture::LoadTexture(path,screen);
    if(ret==true)
    {
        width_frame_=rect_.w;
        height_frame_=rect_.h;
    }
    return ret;
}

void Icon::MoveEffect(const int &x_border,const int &y_border)
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
