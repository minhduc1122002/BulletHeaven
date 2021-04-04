#include<iostream>
#include "ThreatObject.h"
#include "CommonFunc.h"
ThreatObject::ThreatObject()
{
    width_frame_=0;
    height_frame_=0;
    frame_=0;
    angle_move_=90;
    die=0;
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

    SDL_Rect renderQuad={rect_.x,rect_.y,width_frame_,height_frame_};

    SDL_RenderCopy(des,p_object_,current_clip,&renderQuad);
}

void ThreatObject::MoveThreat_Type1()
{
    if(type==1)
    {
        y_pos_+=y_val_;

    }
    else
    {
        x_pos_+=x_val_;
    }
}

void ThreatObject::InitBullet(SDL_Renderer* screen)
{
    if(type==1)
    {
        if((int)y_pos_%200==0)
        {

            BulletObject*p_bullet1=new BulletObject();
            p_bullet1->LoadImg("img//BulletThreat.png",screen);
            p_bullet1->set_is_move(true);
            p_bullet1->SetRect(x_pos_+30,y_pos_+20);
            p_bullet1->set_y_val(3);
            p_bullet_list1_.push_back(p_bullet1);
        }
    }
    else
    {
        if((int)x_pos_%200==0)
        {
            BulletObject*p_bullet1=new BulletObject();
            p_bullet1->LoadImg("img//BulletThreat.png",screen);
            p_bullet1->set_is_move(true);
            p_bullet1->SetRect(x_pos_+30,y_pos_+20);
            p_bullet1->set_y_val(3);
            p_bullet_list1_.push_back(p_bullet1);
        }
    }
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

int ThreatObject::set_random_x_pos_()
{
    int random=rand()%2+1;
    if(random==1)
    {
        return rand()%315;
    }
    else if(random==2)
    {
        return rand()%(715-315+1)+315;
    }
}

int ThreatObject::set_random_y_pos_()
{
    int random=rand()%2+1;
    if(random==1)
    {
        return rand()%250;
    }
    else if(random==2)
    {
        return rand()%(500-251+1)+251;
    }
}

void ThreatObject::RemoveBullet(const int &index)
{
    if(p_bullet_list1_.size()>0 && index<p_bullet_list1_.size())
    {
        BulletObject*p_bullet=p_bullet_list1_.at(index);
        p_bullet_list1_.erase(p_bullet_list1_.begin()+index);
        if(p_bullet!=NULL)
        {
            delete p_bullet;
            p_bullet=NULL;
        }
    }
}
void ThreatObject::random_type_threat()
{
    int random=rand()%2==1;
    if(random==1)
    {
        type=1;
    }
    else
    {
        type=2;
    }
}

void ThreatObject::set_stats(SDL_Renderer* screen)
{
    if(type==1)
    {
        LoadImg("img//SpaceThreat1.png",screen);
        set_clip();
        int rand_x=set_random_x_pos_();
        set_x_pos_(rand_x);
        set_y_pos_(-90);
        set_y_val_(2);
    }
    else
    {
        LoadImg("img//SpaceThreat2.png",screen);
        set_clip();
        int rand_y=set_random_y_pos_();
        int rand_x=rand()%2+1;
        if(rand_x==1)
        {
            set_x_pos_(-90);
            set_x_val_(1);
        }
        else
        {
            set_x_pos_(SCREEN_WIDTH);
            set_x_val_(-1);
        }
        set_y_pos_(rand_y);
    }
}


