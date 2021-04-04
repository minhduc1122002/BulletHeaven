#include<iostream>
#include "GUI.h"

Text::Text()
{
    texture_=NULL;
    width_=0;
    height_=0;

}
Text::~Text()
{

}
bool Text::LoadFromRenderText(TTF_Font*font,SDL_Renderer* screen)
{
    SDL_Surface* text_surface=TTF_RenderText_Solid(font,str_val_.c_str(),text_color_);
    if(text_surface)
    {
        texture_=SDL_CreateTextureFromSurface(screen,text_surface);
        width_=text_surface->w;
        height_=text_surface->h;
        SDL_FreeSurface(text_surface);
    }
    return texture_!=NULL;
}
void Text::Free()
{
    if(texture_!=NULL)
    {
        SDL_DestroyTexture(texture_);
        texture_=NULL;
    }
}
void Text::SetColor(int type)
{
    if(type==1)
    {
        SDL_Color color={255,255,255};
        text_color_=color;
    }
}
void Text::RenderText(SDL_Renderer*screen,int x_pos_,int y_pos_,SDL_Rect* clip, double angle,SDL_Point* center,SDL_RendererFlip flip)
{
    SDL_Rect renderQuad={x_pos_,y_pos_,width_,height_};
    if(clip!=NULL)
    {
        renderQuad.w=clip->w;
        renderQuad.h=clip->h;
    }
    SDL_RenderCopyEx(screen,texture_,clip,&renderQuad,angle,center,flip);
}
