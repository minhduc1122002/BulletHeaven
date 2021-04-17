#include "Effect.h"
using namespace std;
Effect::Effect()
{
    width_frame_=0;
    height_frame_=0;

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

void Effect::Show(SDL_Renderer* screen)
{
    SDL_Rect render_Quad={rect_.x,rect_.y,width_frame_,height_frame_};
    SDL_RenderCopy(screen,p_object_,NULL,&render_Quad);

}
