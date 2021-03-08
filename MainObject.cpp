#include<iostream>
#include "MainObject.h"

MainObject::MainObject()
{
    frame_=0;
    x_pos_=0;
    y_pos_=0;
    x_val_=0;
    y_val_=0;
    width_frame_=0;
    height_frame_=0;
    status_=-1;
    input_type_.left_=0;
    input_type_.right_=0;
    input_type_.down_=0;
    input_type_.up_=0;
}

MainObject::~MainObject()
{

}

bool MainObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path,screen);

    if(ret==true)
    {
        width_frame_=rect_.w/6;
        height_frame_=rect_.h;
    }
    return ret;
}

void MainObject::set_clip()
{
    if(width_frame_>0 && height_frame_>0)
    {
        for(int i=0;i<6;i++)
        {
            frame_clip_[i].x=0+i*(width_frame_);
            frame_clip_[i].y=0;
            frame_clip_[i].w=width_frame_;
            frame_clip_[i].h=height_frame_;
        }
    }
}

void MainObject::Show(SDL_Renderer* des)
{
    if(status_==Turn_Right)
    {
        LoadImg("img//spaceship_right.png",des);
    }
    else if(status_==Turn_Left)
    {
        LoadImg("img//spaceship_left.png",des);
    }
    else if(status_==Go_Up)
    {
        LoadImg("img//spaceship_up.png",des);
    }
    else if(status_==Go_Down)
    {
        LoadImg("img//spaceship_down.png",des);
    }

    if(input_type_.left_==1 || input_type_.right_==1 || input_type_.down_==1 || input_type_.up_==1)
    {
        frame_++;
    }
    else
    {
        frame_=0;
    }
    if(frame_>=6)
    {
        frame_=0;
    }
    rect_.x=x_pos_;
    rect_.y=y_pos_;

    SDL_Rect* current_clip=&frame_clip_[frame_];

    SDL_Rect renderQuad= {rect_.x,rect_.y,width_frame_,height_frame_};

    SDL_RenderCopy(des,p_object_,current_clip,&renderQuad);
}

void MainObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen)
{
    if(events.type==SDL_KEYDOWN)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_d:
            {
                status_=Turn_Right;
                input_type_.right_=1;
                input_type_.left_=0;
            }
            break;
        case SDLK_a:
            {
                status_=Turn_Left;
                input_type_.left_=1;
                input_type_.right_=0;
            }
            break;
        case SDLK_w:
            {
                status_=Go_Up;
                input_type_.down_=0;
                input_type_.up_=1;
            }
            break;
        case SDLK_s:
            {
                status_=Go_Down;
                input_type_.down_=1;
                input_type_.up_=0;
            }
            break;
        }
    }
    else if(events.type==SDL_KEYUP)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_d:
            {
                input_type_.right_=0;
            }
            break;
        case SDLK_a:
            {
                input_type_.left_=0;
            }
            break;
        case SDLK_w:
            {
                input_type_.up_=0;
            }
            break;
        case SDLK_s:
            {
                input_type_.down_=0;
            }
            break;
        }
    }
    if(events.type== SDL_MOUSEBUTTONDOWN)
    {
        if(events.button.button==SDL_BUTTON_LEFT)
        {
            BulletObject* p_bullet=new BulletObject();

            if(status_==Turn_Left)
            {
                p_bullet->LoadImg("img//bullet1.png",screen);
                p_bullet->set_bullet_direction(BulletObject::Dir_Left);
                p_bullet->SetRect(this->rect_.x+width_frame_-25,rect_.y+height_frame_*0.32);
            }
            else if(status_==Turn_Right)
            {
                p_bullet->LoadImg("img//bullet1.png",screen);
                p_bullet->set_bullet_direction(BulletObject::Dir_Right);
                p_bullet->SetRect(this->rect_.x+width_frame_-25,rect_.y+height_frame_*0.32);
            }
            else if(status_==Go_Down)
            {
                p_bullet->LoadImg("img//bullet2.png",screen);
                p_bullet->set_bullet_direction(BulletObject::Dir_Down);
                p_bullet->SetRect(this->rect_.x+width_frame_-22,rect_.y+height_frame_*0.32);
            }
            else if(status_==Go_Up)
            {
                p_bullet->LoadImg("img//bullet2.png",screen);
                p_bullet->set_bullet_direction(BulletObject::Dir_Up);
                p_bullet->SetRect(this->rect_.x+width_frame_-22,rect_.y+height_frame_*0.32);
            }

            p_bullet->set_x_val(1);
            p_bullet->set_y_val(1);
            p_bullet->set_is_move(true);

            p_bullet_list_.push_back(p_bullet);
        }
    }
}

void MainObject::HandleBullet(SDL_Renderer* des)
{
    for(int i=0;i<p_bullet_list_.size();i++)
    {
        BulletObject* p_bullet=p_bullet_list_.at(i);
        if(p_bullet!=NULL)
        {
            if(p_bullet->get_is_move()==true)
            {
                p_bullet->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);
                p_bullet->Render(des);
            }
            else
            {
                p_bullet_list_.erase(p_bullet_list_.begin()+i);
                if(p_bullet!=NULL)
                {
                    delete p_bullet;
                    p_bullet=NULL;
                }
            }
        }
    }
}

void MainObject::MovePlayer()
{
    if(input_type_.left_==1)
    {
        x_pos_-=SPEED;
        if(x_pos_<0)
        {
            x_pos_=SCREEN_WIDTH;
        }
    }
    if(input_type_.right_==1)
    {
        x_pos_+=SPEED;
        if(x_pos_>SCREEN_WIDTH)
        {
            x_pos_=0;
        }
    }
    if(input_type_.down_==1)
    {
        y_pos_+=SPEED;
        if(y_pos_>SCREEN_HEIGHT)
        {
            y_pos_=0;
        }
    }
    if(input_type_.up_==1)
    {
        y_pos_-=SPEED;
        if(y_pos_<0)
        {
            y_pos_=SCREEN_HEIGHT;
        }
    }
}
