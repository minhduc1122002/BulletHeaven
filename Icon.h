#ifndef EFFECT_H_INCLUDED
#define EFFECT_H_INCLUDED

#include "Game_Utils.h"
#include "Texture.h"
using namespace std;
class Icon : public Texture
{
public:
    Icon();
    ~Icon();
    virtual bool LoadTexture(string path,SDL_Renderer* screen);
    int get_frame_width() const {return width_frame_;}
    int get_frame_height() const {return height_frame_;}
    void MoveEffect(const int &x_border,const int &y_border);
    void set_is_move(const bool &isMove) {is_move_=isMove;}
    bool get_is_move() const {return is_move_;}
private:
    int width_frame_;
    int height_frame_;
    bool is_move_;
};

#endif // EFFECT_H_INCLUDED
