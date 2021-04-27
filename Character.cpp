#include "Character.h"

using namespace std;

Character::Character()
{
    frame_=0;
    x_pos_=SCREEN_WIDTH/2-32;
    y_pos_=SCREEN_HEIGHT-100;
    width_frame_=0;
    height_frame_=0;
    status_=Normal;
    input_mouse_=0;
    life=3;
    canspawnbullet=0;
    CurrentTime=0;
    LastTime=0;
    PausedTime=0;
    angle=-90;
}

Character::~Character()
{

}

bool Character::LoadTexture(string path, SDL_Renderer* screen)
{
    bool ret=Texture::LoadTexture(path,screen);

    if(ret==true)
    {
        width_frame_=rect_.w/Num_of_Frame_Character;
        height_frame_=rect_.h;
    }
    return ret;
}

void Character::set_clip()
{
    if(width_frame_>0 && height_frame_>0)
    {
        for(int i=0;i<Num_of_Frame_Character;i++)
        {
            frame_clip_[i].x=0+i*(width_frame_);
            frame_clip_[i].y=0;
            frame_clip_[i].w=width_frame_;
            frame_clip_[i].h=height_frame_;
        }
    }
}
void Character::got_hit()
{
    if(status_==Normal)
    {
        status_=Pause;
        PausedTime=SDL_GetTicks();
        life--;
    }
}
void Character::Show(SDL_Renderer* des)
{
    if(SDL_GetTicks()-PausedTime>=2000 && status_==Pause)
    {
        status_=Normal;
    }
    if(status_==Normal)
    {
        LoadTexture("img//spaceship_up.png",des);
    }
    else if(status_==Pause)
    {
        LoadTexture("img//spaceship_diedelay.png",des);
    }
    if(input_mouse_==1)
    {
        frame_++;
    }
    else
    {
        frame_=0;
    }

    if(frame_>=8)
    {
        frame_=0;
    }
    rect_.x=x_pos_;
    rect_.y=y_pos_;

    SDL_Rect* current_clip=&frame_clip_[frame_];

    SDL_Rect renderQuad={rect_.x,rect_.y,width_frame_,height_frame_};

    SDL_RenderCopy(des,p_texture_,current_clip,&renderQuad);
}

SDL_Rect Character::GetRectFrame()
{
    SDL_Rect rect;
    rect.x=rect_.x+15*width_frame_/32;
    rect.y=rect_.y+15*height_frame_/32;
    rect.w=width_frame_/16;
    rect.h=height_frame_/16;
    return rect;
}

void Character::HandleInputAction(SDL_Event events, SDL_Renderer* screen)
{
    if(events.type==SDL_MOUSEBUTTONDOWN || events.type==SDL_MOUSEBUTTONUP || events.type==SDL_MOUSEMOTION)
    {
        input_mouse_=1;
        int x,y;
        SDL_GetMouseState(&x,&y);
        x_pos_=x-width_frame_/2;
        y_pos_=y-height_frame_/2;
    }
    if(events.type==SDL_MOUSEBUTTONDOWN)
    {
        if(events.button.button==SDL_BUTTON_LEFT)
        {
            canspawnbullet=1;
        }
    }
    else if(events.type==SDL_MOUSEBUTTONUP)
    {
        canspawnbullet=0;
    }
}
void Character::SpawnBullet(SDL_Renderer* screen)
{
    CurrentTime=SDL_GetTicks();
    if(canspawnbullet &&CurrentTime>LastTime+200)
    {
        Bullet* p_bullet1=new Bullet();
        p_bullet1->LoadTexture("img//bullet.png",screen);
        p_bullet1->set_pos(rect_.x+width_frame_/2-18,rect_.y+height_frame_*0.1);
        p_bullet1->set_angle(angle);
        p_bullet1->set_x_val(3);
        p_bullet1->set_y_val(3);
        p_bullet1->set_is_move(true);
        p_bullet_list1_.push_back(p_bullet1);
        LastTime=CurrentTime;
    }
}
void Character::HandleBullet1(SDL_Renderer* des)
{
    for(int i=0;i<p_bullet_list1_.size();i++)
    {
        Bullet* p_bullet1=p_bullet_list1_.at(i);
        if(p_bullet1!=NULL)
        {
            if(p_bullet1->get_is_move()==true)
            {
                p_bullet1->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);
                p_bullet1->Render(des);
            }
            else
            {
                p_bullet_list1_.erase(p_bullet_list1_.begin()+i);
                if(p_bullet1!=NULL)
                {
                    delete p_bullet1;
                    p_bullet1=NULL;
                }
            }
        }
    }
}

void Character::RemoveBullet(const int &index)
{
    int n=p_bullet_list1_.size();
    if(n>0 && index<n)
    {
        Bullet*p_bullet=p_bullet_list1_.at(index);
        p_bullet_list1_.erase(p_bullet_list1_.begin()+index);
        if(p_bullet)
        {
            delete p_bullet;
            p_bullet=NULL;
        }
    }
}

