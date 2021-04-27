#ifndef BASEOBJECT_H_INCLUDED
#define BASEOBJECT_H_INCLUDED

#include "Game_Utils.h"
using namespace std;
class Texture
{
public:
    Texture();
    ~Texture();
    void SetRect(const int& x, const int& y)
    {
        rect_.x=x;
        rect_.y=y;
    }
    SDL_Rect GetRect()
    {
        return rect_;
    }
    SDL_Texture* GetTexture()
    {
        return p_texture_;
    }
    virtual bool LoadTexture(string path, SDL_Renderer* screen);
    void MoveBackGround(SDL_Renderer* des,const SDL_Rect* clip=NULL);
    void Render(SDL_Renderer* des,const SDL_Rect* clip=NULL);
    void Free();
protected:
    SDL_Texture* p_texture_;
    SDL_Rect rect_;
};

#endif // BASEOBJECT_H_INCLUDED
