#include "Enemy.h"
using namespace std;
Enemy::Enemy()
{
    x_pos_=0;
    y_pos_=0;
    x_val_=0;
    y_val_=0;
    angle_val_=0;
    type=1.1;
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
    reverse_direction=0;
    changespawn=0;
}
Enemy::~Enemy()
{

}

bool Enemy::LoadTexture(string path, SDL_Renderer* screen)
{
    bool ret=Texture::LoadTexture(path,screen);

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

    SDL_RenderCopy(des,p_texture_,current_clip,&renderQuad);
}

void Enemy::MoveThreat()
{
    if(type==1.1 || type==2.1 || type==3.1 || type==5.1 || type==7.1)
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
    if(reverse_direction==1)
    {
        angle_val_=-angle_val_;
        reverse_direction=0;
    }
    if(angle>=360)
    {
        angle=0;
    }
    angle+=angle_val_;
}
bool Enemy::canspawnbullet()
{
    CurrentTime=SDL_GetTicks();
    bool check_can_spawn=0;
    if(type==1.1 || type==2.1 || type==3.1 || type==5.1 || type==6.1 || type==7.1)
    {
        if(CurrentTime>LastTime+delay_shoot_time && y_pos_>=y_limit_)
        {
            LastTime=CurrentTime;
            check_can_spawn=1;
        }
    }
    else if(type==4.1 || type==4.2)
    {
        if(CurrentTime>LastTime+400)
        {
            LastTime=CurrentTime;
            check_can_spawn=1;
        }
    }
    return check_can_spawn;
}
void Enemy::MakeBulletUponDeath(vector<Bullet*> &bullet,SDL_Renderer* screen)
{
    for(int i=0;i<12;i++)
    {
        Bullet*p_bullet=new Bullet();
        if(type==1.1 || type==3.1 || type==7.1)
        {
            p_bullet->LoadTexture("img//BulletThreat.png",screen);
        }
        else if(type==2.1)
        {
            p_bullet->LoadTexture("img//BulletThreat6.png",screen);
        }
        else if(type==4.1 || type==4.2)
        {
            p_bullet->LoadTexture("img//BulletThreat2.png",screen);
        }
        else if(type==5.1)
        {
            p_bullet->LoadTexture("img//BulletThreat5.png",screen);
        }
        p_bullet->set_is_move(true);
        p_bullet->set_angle(0+30*i);
        p_bullet->set_x_val(2);
        p_bullet->set_y_val(2);
        p_bullet->set_pos(x_pos_+width_frame_/2-(p_bullet->GetRect().w)/2,y_pos_+height_frame_/2);
        bullet.push_back(p_bullet);
    }
}
void Enemy::MakeBullet(vector<Bullet*> &bullet,SDL_Renderer* screen,Character &spaceship)
{
    if(type==1.1)
    {
        delay_shoot_time=400;
        Bullet*p_bullet=new Bullet();
        p_bullet->LoadTexture("img//BulletThreat.png",screen);
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
        delay_shoot_time=100;
        Bullet*p_bullet1=new Bullet();
        p_bullet1->LoadTexture("img//BulletThreat6.png",screen);
        p_bullet1->set_is_move(true);
        p_bullet1->set_angle(angle);
        rotate_angle();
        p_bullet1->set_x_val(2);
        p_bullet1->set_y_val(2);
        p_bullet1->set_pos(x_pos_+width_frame_/2-(p_bullet1->GetRect().w)/2,y_pos_+24);
        bullet.push_back(p_bullet1);

        Bullet*p_bullet2=new Bullet();
        p_bullet2->LoadTexture("img//BulletThreat6.png",screen);
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
            delay_shoot_time=500;
            Bullet*p_bullet=new Bullet();
            p_bullet->LoadTexture("img//BulletThreat.png",screen);
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
        Bullet*p_bullet=new Bullet();
        p_bullet->LoadTexture("img//BulletThreat2.png",screen);
        p_bullet->set_is_move(true);
        p_bullet->set_random_angle1();
        p_bullet->set_x_val(2);
        p_bullet->set_y_val(2);
        p_bullet->set_pos(x_pos_+width_frame_/2-(p_bullet->GetRect().w)/2,y_pos_+24);
        bullet.push_back(p_bullet);
    }
    else if(type==5.1)
    {
        delay_shoot_time=600;
        for(int i=0;i<3;i++)
        {
            Bullet*p_bullet=new Bullet();
            p_bullet->set_is_move(true);
            p_bullet->LoadTexture("img//BulletThreat5.png",screen);
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
                p_bullet->set_pos(x_pos_+width_frame_/2-(p_bullet->GetRect().w)/2+10*(i-1),y_pos_+height_frame_/2+sqrt(500));
            }
            bullet.push_back(p_bullet);
        }
    }
    else if(type==6.1)
    {
        if(die>=200 && die<300)
        {
            x_val_=1;
            if(!changespawn)
            {
                delay_shoot_time=400;
                for(int j=0;j<24;j++)
                {
                    for(int i=0;i<4;i++)
                    {
                        Bullet*p_bullet=new Bullet();
                        p_bullet->set_is_move(true);
                        p_bullet->LoadTexture("img//BulletThreat5.png",screen);
                        p_bullet->set_angle(15*j);
                        p_bullet->set_x_val(2);
                        p_bullet->set_y_val(2);
                        if(i%2==0)
                        {
                            p_bullet->set_pos(x_pos_+width_frame_/2-(p_bullet->GetRect().w)/2+10*(i-1),y_pos_+height_frame_/2);
                        }
                        else
                        {
                            p_bullet->set_pos(x_pos_+width_frame_/2-(p_bullet->GetRect().w)/2,y_pos_+height_frame_/2+10*(i-2));
                        }
                        bullet.push_back(p_bullet);
                    }
                }
                changespawn=1;
            }
            else
            {
                delay_shoot_time=500;
                for(int j=0;j<36;j++)
                {
                    Bullet*p_bullet=new Bullet();
                    p_bullet->set_is_move(true);
                    p_bullet->LoadTexture("img//BulletThreat4.png",screen);
                    p_bullet->set_angle(10*j);
                    p_bullet->set_x_val(2);
                    p_bullet->set_y_val(2);
                    p_bullet->set_pos(x_pos_+width_frame_/2-(p_bullet->GetRect().w)/2,y_pos_+height_frame_/2);
                    bullet.push_back(p_bullet);
                }
                changespawn=0;
            }
        }
        else if(die>=300 && die<400)
        {
            x_pos_=SCREEN_WIDTH/2-width_frame_/2;
            delay_shoot_time=150;
            x_val_=0;
            for(int i=0;i<12;i++)
            {
                Bullet*p_bullet1=new Bullet();
                p_bullet1->LoadTexture("img//BulletThreat5.png",screen);
                p_bullet1->set_is_move(true);
                p_bullet1->set_angle(angle+30*i);
                rotate_angle();
                if(angle>180 || angle<0)
                {
                    reverse_direction=1;
                    delay_shoot_time=1000;
                }
                p_bullet1->set_x_val(2);
                p_bullet1->set_y_val(2);
                p_bullet1->set_pos(x_pos_+width_frame_/2-(p_bullet1->GetRect().w)/2,y_pos_+height_frame_);
                bullet.push_back(p_bullet1);
            }
            for(int i=0;i<4;i++)
            {
                Bullet*p_bullet=new Bullet();
                if(i%2==0)
                {
                    p_bullet->LoadTexture("img//BulletThreat.png",screen);
                }
                else
                {
                    p_bullet->LoadTexture("img//BulletThreat2.png",screen);
                }
                p_bullet->set_is_move(true);
                p_bullet->set_random_angle2();
                p_bullet->set_x_val(2);
                p_bullet->set_y_val(2);
                p_bullet->set_pos(x_pos_+width_frame_/2-(p_bullet->GetRect().w)/2,y_pos_+height_frame_+20*i);
                bullet.push_back(p_bullet);
            }
        }
        else if(die>=100 && die <200)
        {
            x_val_=1;
            delay_shoot_time=150;
            for(int i=0;i<6;i++)
            {
                Bullet*p_bullet1=new Bullet();
                p_bullet1->LoadTexture("img//BulletThreat5.png",screen);
                p_bullet1->set_is_move(true);
                p_bullet1->set_type(2);
                p_bullet1->set_pos(100+100*i,0);
                p_bullet1->set_starting_point(120+120*i);
                bullet.push_back(p_bullet1);
            }
            for(int i=0;i<5;i++)
            {
                Bullet*p_bullet=new Bullet();
                p_bullet->LoadTexture("img//BulletThreat4.png",screen);
                p_bullet->set_is_move(true);
                p_bullet->set_type(1);
                p_bullet->set_angle(45);
                if(i==0)
                {
                    p_bullet->set_pos(200,0);
                }
                else
                {
                    p_bullet->set_pos(0,0+200*(i-1));
                }
                p_bullet->set_x_val(2);
                p_bullet->set_y_val(2);
                bullet.push_back(p_bullet);
            }
            for(int i=0;i<5;i++)
            {
                Bullet*p_bullet=new Bullet();
                p_bullet->LoadTexture("img//BulletThreat4.png",screen);
                p_bullet->set_is_move(true);
                p_bullet->set_type(1);
                p_bullet->set_angle(135);
                if(i==0)
                {
                    p_bullet->set_pos(SCREEN_WIDTH-200,0);
                }
                else
                {
                    p_bullet->set_pos(SCREEN_WIDTH,0+200*(i-1));
                }
                p_bullet->set_x_val(2);
                p_bullet->set_y_val(2);
                bullet.push_back(p_bullet);
            }
        }
        else if(die<100)
        {
            delay_shoot_time=500;
            x_val_=1;
            for(int i=0;i<24;i++)
            {
                Bullet*p_bullet=new Bullet();
                p_bullet->LoadTexture("img//BulletThreat6.png",screen);
                p_bullet->set_is_move(true);
                p_bullet->set_angle(0+15*i);
                p_bullet->set_x_val(1);
                p_bullet->set_y_val(2);
                p_bullet->set_pos(x_pos_+width_frame_/2-(p_bullet->GetRect().w)/2,y_pos_+height_frame_/2);
                bullet.push_back(p_bullet);
            }
            for(int i=0;i<24;i++)
            {
                Bullet*p_bullet=new Bullet();
                p_bullet->LoadTexture("img//BulletThreat2.png",screen);
                p_bullet->set_is_move(true);
                p_bullet->set_angle(0+15*i);
                p_bullet->set_x_val(2);
                p_bullet->set_y_val(1);
                p_bullet->set_pos(x_pos_+width_frame_/2-(p_bullet->GetRect().w)/2,y_pos_+height_frame_/2);
                bullet.push_back(p_bullet);
            }
        }
    }
    else if(type==7.1)
    {
        delay_shoot_time=800;
        for(int i=0;i<4;i++)
        {
            Bullet*p_bullet=new Bullet();
            p_bullet->set_is_move(true);
            p_bullet->LoadTexture("img//BulletThreat.png",screen);
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
            if(i%2==0)
            {
                p_bullet->set_pos(x_pos_+width_frame_/2-(p_bullet->GetRect().w)/2+10*(i-1),y_pos_+height_frame_/2);
            }
            else
            {
                p_bullet->set_pos(x_pos_+width_frame_/2-(p_bullet->GetRect().w)/2,y_pos_+height_frame_/2+10*(i-2));
            }
            bullet.push_back(p_bullet);
        }
    }
}
void Enemy::set_stats(SDL_Renderer* screen)
{
    if(type==1.1)
    {
        LoadTexture("img//SpaceThreat1.png",screen);
        set_clip();
        y_val_=2;
        score=100;
    }
    else if(type==2.1)
    {
        LoadTexture("img//SpaceThreat6.png",screen);
        set_clip();
        y_val_=2;
        score=500;
    }
    else if(type==3.1)
    {
        LoadTexture("img//SpaceThreat2.png",screen);
        set_clip();
        y_val_=2;
        score=300;
    }
    else if(type==4.1 || type==4.2)
    {
        LoadTexture("img//SpaceThreat5.png",screen);
        set_clip();
        x_val_=2;
        score=100;
    }
    else if(type==5.1)
    {
        LoadTexture("img//SpaceThreat4.png",screen);
        set_clip();
        y_val_=2;
        score=300;
    }
    else if(type==6.1)
    {
        LoadTexture("img//SpaceBoss.png",screen);
        set_clip();
        y_val_=2;
        x_val_=1;
        score=10000;
    }
    else if(type==7.1)
    {
        LoadTexture("img//SpaceThreat3.png",screen);
        set_clip();
        y_val_=2;
        score=500;
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
        if(die==5) return 1;
    }
    else if(type==6.1)
    {
        if(die==400) return 1;
    }
    else if(type==7.1)
    {
        if(die==5) return 1;
    }
    return 0;
}
void Enemy::Generate_Health(vector<Icon*> &health,SDL_Renderer* screen)
{
    if(rand()%10+1==1)
    {
        Icon *p_health=new Icon();
        p_health->LoadTexture("img//heart_icon.png",screen);
        p_health->SetRect(x_pos_+p_health->get_frame_width()/2,y_pos_+10);
        p_health->set_is_move(true);
        health.push_back(p_health);
    }
}


