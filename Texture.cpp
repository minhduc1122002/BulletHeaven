#include "Texture.h"
using namespace std;

Texture::Texture()
{
    p_texture_=NULL;
    rect_.x=0;
    rect_.y=0;
    rect_.w=0;
    rect_.h=0;
}
Texture::~Texture()
{
    Free();
}

bool Texture::LoadTexture(string path,SDL_Renderer* screen)
{
    Free();
    SDL_Texture* new_texture=NULL;
    SDL_Surface* load_surface=IMG_Load(path.c_str());
    if(load_surface !=NULL)
    {
        SDL_SetColorKey(load_surface,SDL_TRUE,SDL_MapRGB(load_surface->format,COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        new_texture=SDL_CreateTextureFromSurface(screen, load_surface);
        if(new_texture!=NULL)
        {
            rect_.w=load_surface->w;
            rect_.h=load_surface->h;
        }
        SDL_FreeSurface(load_surface);
    }
    p_texture_=new_texture;
    return p_texture_!=NULL;
}

void Texture::MoveBackGround(SDL_Renderer* des,const SDL_Rect* clip /*- NULL*/)
{
    SDL_Rect renderquad1={rect_.x,rect_.y,rect_.w,rect_.h};
    SDL_RenderCopy(des,p_texture_,clip,&renderquad1);
    SDL_Rect renderquad2={rect_.x,rect_.y-SCREEN_HEIGHT,rect_.w,rect_.h};
    SDL_RenderCopy(des,p_texture_,clip,&renderquad2);
    rect_.y+=1;
    if(rect_.y>=SCREEN_HEIGHT)
    {
        rect_.y=0;
    }
}
void Texture::Render(SDL_Renderer* des,const SDL_Rect* clip /*- NULL*/)
{
    SDL_Rect renderquad1={rect_.x,rect_.y,rect_.w,rect_.h};
    SDL_RenderCopy(des,p_texture_,clip,&renderquad1);
}
void Texture::Free()
{
    if(p_texture_!=NULL)
    {
        SDL_DestroyTexture(p_texture_);
        p_texture_=NULL;
        rect_.w=0;
        rect_.h=0;
    }
}



