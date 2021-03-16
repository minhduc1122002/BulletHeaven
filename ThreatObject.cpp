#include<iostream>
#include "ThreatObject.h"
#include "CommonFunc.h"
ThreatObject::ThreatObject()
{
    width_frame_=0;
    height_frame_=0;
    frame_=0;
}
ThreatObject::~ThreatObject()
{

}

bool ThreatObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path,screen);

    if(ret==true)
    {
        width_frame_=rect_.w;
        height_frame_=rect_.h;
    }
    return ret;
}


void ThreatObject::set_clip()
{
    if(width_frame_>0 && height_frame_>0)
    {
        for(int i=0;i<1;i++)
        {
            frame_clip_[i].x=0+i*(width_frame_);
            frame_clip_[i].y=0;
            frame_clip_[i].w=width_frame_;
            frame_clip_[i].h=height_frame_;
        }
    }
}

void ThreatObject::Show(SDL_Renderer* des)
{
    rect_.x=x_pos_;
    rect_.y=y_pos_;
    frame_++;
    if(frame_>=1)
    {
        frame_=0;
    }

    SDL_Rect* current_clip=&frame_clip_[frame_];

    SDL_Rect renderQuad= {rect_.x,rect_.y,width_frame_,height_frame_};

    SDL_RenderCopy(des,p_object_,current_clip,&renderQuad);
}

void ThreatObject::MoveThreat()
{
    y_pos_+=y_val_;
    /*if(x_pos_<0-width_frame_)
    {
        x_pos_=SCREEN_WIDTH+width_frame_;

    }
    else if(x_pos_>SCREEN_WIDTH+width_frame_)
    {
        x_pos_=0-width_frame_;
    }*/
    if(y_pos_<0-height_frame_)
    {
        y_pos_=SCREEN_HEIGHT+height_frame_;

    }
    else if(y_pos_>SCREEN_HEIGHT+height_frame_)
    {
        y_pos_=0-height_frame_;
        x_pos_=rand()%(SCREEN_WIDTH-width_frame_);
    }
}

void ThreatObject::InitBullet(BulletObject*p_bullet1, SDL_Renderer* screen)
{
    p_bullet1->LoadImg("img//BulletThreat.png",screen);
    p_bullet1->set_is_move(true);
    p_bullet1->set_bullet_direction(BulletObject::Dir_Down);
    p_bullet1->SetRect(x_pos_+30,y_pos_+20);
    p_bullet1->set_y_val(1);
    p_bullet1->set_x_val(1);
    p_bullet_list1_.push_back(p_bullet1);
}

void ThreatObject::MakeBullet(SDL_Renderer* screen,const int &x_limit,const int &y_limit)
{
    for(int i=0;i<p_bullet_list1_.size();i++)
    {
        BulletObject* p_bullet1=p_bullet_list1_.at(i);
        if(p_bullet1!=NULL)
        {
            if(p_bullet1->get_is_move()==true)
            {
                p_bullet1->HandleMove(x_limit,y_limit,90);
                p_bullet1->Render(screen);
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
