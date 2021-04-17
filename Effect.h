#ifndef EFFECT_H_INCLUDED
#define EFFECT_H_INCLUDED

#include "CommonFunc.h"
#include "BaseObject.h"
#define Num_of_Frame_Effect 1
using namespace std;
class Effect : public BaseObject
{
public:
    Effect();
    ~Effect();
    virtual bool LoadImg(string path,SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    int get_frame_width() const {return width_frame_;}
    int get_frame_height() const {return height_frame_;}
private:
    int width_frame_;
    int height_frame_;
};

#endif // EFFECT_H_INCLUDED
