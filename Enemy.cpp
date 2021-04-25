#include "Enemy.h"
using namespace std;
Enemy::Enemy()
{
    width_frame_=0;
    height_frame_=0;
    frame_=0;
    die=0;
    score=0;
    CurrentTime=0;
    LastTime=0;
    angle=0;
    angle_move=0;
    y_limit_=0;
    x_limit_=0;
    delay_shoot_time=300;
}
Enemy::~Enemy()
{

}

bool Enemy::LoadImg(string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path,screen);

    if(ret==true)
    {
        width_frame_=rect_.w/Num_of_Frame_Enemy;
        height_frame_=rect_.h;
    }
    return ret;
}

void Enemy::set_clip()
{
    if(width_frame_>0 && height_frame_>0)
    {
        for(int i=0;i<Num_of_Frame_Enemy;i++)
        {
            frame_clip_[i].x=0+i*(width_frame_);
            frame_clip_[i].y=0;
            frame_clip_[i].w=width_frame_;
            frame_clip_[i].h=height_frame_;
        }
    }
}

void Enemy::Show(SDL_Renderer* des)
{
    rect_.x=x_pos_;
    rect_.y=y_pos_;
    frame_++;
    if(frame_>=Num_of_Frame_Enemy)
    {
        frame_=0;
    }
    SDL_Rect* current_clip=&frame_clip_[frame_];

    SDL_Rect renderQuad={rect_.x,rect_.y,width_frame_,height_frame_};

    SDL_RenderCopy(des,p_object_,current_clip,&renderQuad);
}

void Enemy::MoveThreat()
{
    if(type==1.1 || type==2.1 || type==3.1 || type==5.1)
    {
        if(y_pos_>=y_limit_)
        {
            y_pos_=y_limit_;
        }
        y_pos_+=y_val_;
    }
    else if(type==4.1)
    {
        if(x_pos_>=100)
        {
            x_pos_=100;
        }
        x_pos_+=x_val_;
    }
    else if(type==4.2)
    {
        if(x_pos_<=700-width_frame_)
        {
            x_pos_=700-width_frame_;
        }
        x_pos_-=x_val_;
    }
    else if(type==6.1)
    {
        if(y_pos_>=y_limit_)
        {
            y_pos_=y_limit_;
            if(x_pos_>=650-width_frame_)
            {
                angle_move=180;
            }
            else if(x_pos_<=150)
            {
                angle_move=0;
            }
            x_pos_+=x_val_*cos(angle_move*PI/180);
        }
        y_pos_+=y_val_;
    }
}
void Enemy::rotate_angle()
{
    angle+=angle_val_;
    if(angle>=360)
    {
        angle=0;
    }
}
bool Enemy::canspawnbullet()
{
    CurrentTime=SDL_GetTicks();
    bool check_can_spawn=0;
    if(type==1.1)
    {
        if(CurrentTime>LastTime+400 && y_pos_>=y_limit_)
        {
            LastTime=CurrentTime;
            check_can_spawn=1;
        }
    }
    else if(type==2.1)
    {
        if(CurrentTime>LastTime+100 && y_pos_>=y_limit_)
        {
            LastTime=CurrentTime;
            check_can_spawn=1;
        }
    }
    else if(type==3.1 || type==5.1)
    {
        if(CurrentTime>LastTime+600 && y_pos_>=y_limit_)
        {
            LastTime=CurrentTime;
            check_can_spawn=1;
        }
    }
    else if(type==6.1)
    {
        if(CurrentTime>LastTime+delay_shoot_time && y_pos_>=y_limit_)
        {
            LastTime=CurrentTime;
            check_can_spawn=1;
        }
    }
    else
    {
        if(CurrentTime>LastTime+400)
        {
            LastTime=CurrentTime;
            check_can_spawn=1;
        }
    }
    return check_can_spawn;
}
void Enemy::MakeBullet(vector<BulletObject*> &bullet,SDL_Renderer* screen,MainObject &spaceship)
{
    if(type==1.1)
    {
        BulletObject*p_bullet=new BulletObject();
        p_bullet->LoadImg("img//BulletThreat.png",screen);
        p_bullet->set_is_move(true);
        if(spaceship.GetRect().x-x_pos_>=0)
        {
            p_bullet->set_angle(atan((spaceship.GetRect().y-y_pos_)/(spaceship.GetRect().x-x_pos_))*180/PI);
        }
        else if(spaceship.GetRect().x-x_pos_<0)
        {
            p_bullet->set_angle(180+atan((spaceship.GetRect().y-y_pos_)/(spaceship.GetRect().x-x_pos_))*180/PI);
        }
        p_bullet->set_x_val(2);
        p_bullet->set_y_val(2);
        p_bullet->set_pos(x_pos_+width_frame_/2-(p_bullet->GetRect().w)/2,y_pos_+24);
        bullet.push_back(p_bullet);
    }
    else if(type==2.1)
    {
        BulletObject*p_bullet1=new BulletObject();
        p_bullet1->LoadImg("img//BulletThreat6.png",screen);
        p_bullet1->set_is_move(true);
        p_bullet1->set_angle(angle);
        rotate_angle();
        p_bullet1->set_x_val(2);
        p_bullet1->set_y_val(2);
        p_bullet1->set_pos(x_pos_+width_frame_/2-(p_bullet1->GetRect().w)/2,y_pos_+24);
        bullet.push_back(p_bullet1);

        BulletObject*p_bullet2=new BulletObject();
        p_bullet2->LoadImg("img//BulletThreat6.png",screen);
        p_bullet2->set_is_move(true);
        p_bullet2->set_angle(10+angle);
        rotate_angle();
        p_bullet2->set_x_val(2);
        p_bullet2->set_y_val(2);
        p_bullet2->set_pos(x_pos_+width_frame_/2-(p_bullet2->GetRect().w)/2,y_pos_+24);
        bullet.push_back(p_bullet2);
    }
    else if(type==3.1)
    {
        for(int i=0;i<36;i++)
        {
            BulletObject*p_bullet=new BulletObject();
            p_bullet->LoadImg("img//BulletThreat.png",screen);
            p_bullet->set_is_move(true);
            p_bullet->set_angle(0+10*i);
            p_bullet->set_x_val(2);
            p_bullet->set_y_val(2);
            p_bullet->set_pos(x_pos_+width_frame_/2-(p_bullet->GetRect().w)/2,y_pos_+24);
            bullet.push_back(p_bullet);
        }
    }
    else if(type==4.1 || type==4.2)
    {
        BulletObject*p_bullet=new BulletObject();
        p_bullet->LoadImg("img//BulletThreat2.png",screen);
        p_bullet->set_is_move(true);
        p_bullet->set_random_angle1();
        p_bullet->set_x_val(2);
        p_bullet->set_y_val(2);
        p_bullet->set_pos(x_pos_+width_frame_/2-(p_bullet->GetRect().w)/2,y_pos_+24);
        bullet.push_back(p_bullet);
    }
    else if(type==5.1)
    {
        for(int i=0;i<3;i++)
        {
            BulletObject*p_bullet=new BulletObject();
            p_bullet->set_is_move(true);
            p_bullet->LoadImg("img//BulletThreat5.png",screen);
            if(spaceship.GetRect().x-x_pos_>=0)
            {
                p_bullet->set_angle(atan((spaceship.GetRect().y-y_pos_)/(spaceship.GetRect().x-x_pos_))*180/PI);
            }
            else if(spaceship.GetRect().x-x_pos_<0)
            {
                p_bullet->set_angle(180+atan((spaceship.GetRect().y-y_pos_)/(spaceship.GetRect().x-x_pos_))*180/PI);
            }
            p_bullet->set_x_val(2);
            p_bullet->set_y_val(2);
            if(i==0 || i==2)
            {
                p_bullet->set_pos(x_pos_+width_frame_/2-(p_bullet->GetRect().w)/2+10*(i-1),y_pos_+height_frame_/2);
            }
            else if(i==1)
            {
                p_bullet->set_pos(x_pos_+width_frame_/2-(p_bullet->GetRect().w)/2+10*(i-1),y_pos_+height_frame_/2+20);
            }
            bullet.push_back(p_bullet);
        }
    }
    else if(type==6.1)
    {
        if(die<50)
        {
            delay_shoot_time=300;
            for(int i=0;i<6;i++)
            {
                BulletObject*p_bullet1=new BulletObject();
                p_bullet1->LoadImg("img//BulletThreat4.png",screen);
                p_bullet1->set_is_move(true);
                p_bullet1->set_random_angle1();
                p_bullet1->set_x_val(2);
                p_bullet1->set_y_val(2);
                p_bullet1->set_pos(x_pos_+width_frame_/2-(p_bullet1->GetRect().w)/2-20*(i-2.5),y_pos_+height_frame_/2-50);
                bullet.push_back(p_bullet1);
            }
            for(int j=0;j<2;j++)
            {
                for(int i=0;i<24;i++)
                {
                    BulletObject*p_bullet2=new BulletObject();
                    p_bullet2->LoadImg("img//BulletThreat5.png",screen);
                    p_bullet2->set_is_move(true);
                    p_bullet2->set_angle(0+15*i);
                    p_bullet2->set_x_val(2);
                    p_bullet2->set_y_val(2);
                    p_bullet2->set_pos(x_pos_+width_frame_/2-(p_bullet2->GetRect().w)/2-200*(j-0.5),y_pos_+50);
                    bullet.push_back(p_bullet2);
                }
            }
        }
        if(die>=50 && die<100)
        {
            delay_shoot_time=100;
            x_val_=0;
            for(int i=0;i<6;i++)
            {
                BulletObject*p_bullet1=new BulletObject();
                if(i%2==0)
                {
                    p_bullet1->LoadImg("img//BulletThreat5.png",screen);
                }
                else
                {
                    p_bullet1->LoadImg("img//BulletThreat4.png",screen);
                }
                p_bullet1->set_is_move(true);
                p_bullet1->set_angle(angle+30*i);
                rotate_angle();
                p_bullet1->set_x_val(2);
                p_bullet1->set_y_val(2);
                p_bullet1->set_pos(x_pos_+width_frame_/2-(p_bullet1->GetRect().w)/2,y_pos_+24);
                bullet.push_back(p_bullet1);
            }
            for(int i=0;i<6;i++)
            {
                BulletObject*p_bullet1=new BulletObject();
                if(i%2==0)
                {
                    p_bullet1->LoadImg("img//BulletThreat5.png",screen);
                }
                else
                {
                    p_bullet1->LoadImg("img//BulletThreat4.png",screen);
                }
                p_bullet1->set_is_move(true);
                p_bullet1->set_angle(180+angle+30*i);
                rotate_angle();
                p_bullet1->set_x_val(2);
                p_bullet1->set_y_val(2);
                p_bullet1->set_pos(x_pos_+width_frame_/2-(p_bullet1->GetRect().w)/2,y_pos_+24);
                bullet.push_back(p_bullet1);
            }
            BulletObject*p_bullet=new BulletObject();
            p_bullet->LoadImg("img//BulletThreat.png",screen);
            p_bullet->set_is_move(true);
            p_bullet->set_random_angle1();
            p_bullet->set_x_val(2);
            p_bullet->set_y_val(2);
            p_bullet->set_pos(x_pos_+width_frame_/2-(p_bullet->GetRect().w)/2,y_pos_+24);
            bullet.push_back(p_bullet);
        }
    }
}
void Enemy::set_stats(SDL_Renderer* screen)
{
    if(type==1.1)
    {
        LoadImg("img//SpaceThreat1.png",screen);
        set_clip();
        y_val_=2;
        score=100;
    }
    else if(type==2.1)
    {
        LoadImg("img//SpaceThreat6.png",screen);
        set_clip();
        y_val_=2;
        score=300;
    }
    else if(type==3.1)
    {
        LoadImg("img//SpaceThreat2.png",screen);
        set_clip();
        y_val_=2;
        score=300;
    }
    else if(type==4.1 || type==4.2)
    {
        LoadImg("img//SpaceThreat5.png",screen);
        set_clip();
        x_val_=2;
        score=100;
    }
    else if(type==5.1)
    {
        LoadImg("img//SpaceThreat4.png",screen);
        set_clip();
        y_val_=2;
        score=200;
    }
    else if(type==6.1)
    {
        LoadImg("img//SpaceBoss.png",screen);
        set_clip();
        y_val_=2;
        x_val_=1;
        score=1000;
    }
}
bool Enemy::check_die()
{
    if(type==1.1)
    {
        if(die==3) return 1;
    }
    else if(type==2.1)
    {
        if(die==5) return 1;
    }
    else if(type==3.1)
    {
        if(die==5) return 1;
    }
    else if(type==4.1 || type==4.2)
    {
        if(die==3) return 1;
    }
    else if(type==5.1)
    {
        if(die==3) return 1;
    }
    else if(type==6.1)
    {
        if(die==200) return 1;
    }
    return 0;
}
void Enemy::Generate_Health(vector<Effect*> &health,SDL_Renderer* screen)
{
    if(rand()%100+1==5)
    {
        Effect *p_health=new Effect();
        p_health->LoadImg("img//heart_icon.png",screen);
        p_health->SetRect(x_pos_+p_health->get_frame_width()/2,y_pos_+10);
        p_health->set_is_move(true);
        health.push_back(p_health);
    }
}


