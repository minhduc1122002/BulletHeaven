#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include"CommonFunc.h"
class Text
{
public:
    Text();
    ~Text();

    bool LoadFromRenderText(TTF_Font* font,SDL_Renderer* screen);
    void Free();
    void SetColor(int type);

    void RenderText(SDL_Renderer*screen,int x_pos_,int y_pos_,SDL_Rect* clip=NULL, double angle=0.0,SDL_Point* center=NULL,SDL_RendererFlip flip=SDL_FLIP_NONE);
    int get_width_() const {return width_;}
    int get_height_() const {return height_;}
    void Set_Text(const std::string& text) {str_val_=text;}
    std::string GetText() const {return str_val_;}
private:
    std::string str_val_;
    SDL_Color text_color_;
    SDL_Texture* texture_;
    int width_;
    int height_;
};


#endif // GUI_H_INCLUDED
