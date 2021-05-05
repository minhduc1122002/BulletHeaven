#include "Character.h"
using namespace std;

Character::Character()
{
    frame=0;
    x_pos=SCREEN_WIDTH/2-32;
    y_pos=SCREEN_HEIGHT-100;
    width_frame=0;
    height_frame=0;
    status=Normal;
    input_mouse=0;
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
        width_frame=Rect.w/Num_of_Frame_Character;
        height_frame=Rect.h;
    }
    return ret;
}

void Character::set_clip()
{
    if(width_frame>0 && height_frame>0)
    {
        for(int i=0;i<Num_of_Frame_Character;i++)
        {
            frame_clip[i].x=0+i*(width_frame);
            frame_clip[i].y=0;
            frame_clip[i].w=width_frame;
            frame_clip[i].h=height_frame;
        }
    }
}
void Character::got_hit(Mix_Chunk* dead)
{
    if(status==Normal)
    {
        status=Pause;
        PausedTime=SDL_GetTicks();
         Mix_PlayChannel(4,dead,0);
        life--;
    }
}
void Character::Show(SDL_Renderer* des)
{
    if(SDL_GetTicks()-PausedTime>=2000 && status==Pause)
    {
        status=Normal;
    }
    if(status==Normal)
    {
        LoadTexture("img//spaceship_up.png",des);
    }
    else if(status==Pause)
    {
        LoadTexture("img//spaceship_diedelay.png",des);
    }
    if(input_mouse==1)
    {
        frame++;
    }
    else
    {
        frame=0;
    }

    if(frame>=8)
    {
        frame=0;
    }
    Rect.x=x_pos;
    Rect.y=y_pos;

    SDL_Rect* current_clip=&frame_clip[frame];

    SDL_Rect RenderQuad={Rect.x,Rect.y,width_frame,height_frame};

    SDL_RenderCopy(des,p_texture,current_clip,&RenderQuad);
}

SDL_Rect Character::GetHitBox()
{
    SDL_Rect hit_box;
    hit_box.x=Rect.x+15*width_frame/32;
    hit_box.y=Rect.y+15*height_frame/32;
    hit_box.w=width_frame/16;
    hit_box.h=height_frame/16;
    return hit_box;
}

void Character::HandleInputAction(SDL_Event events, SDL_Renderer* screen)
{
    if(events.type==SDL_MOUSEBUTTONDOWN || events.type==SDL_MOUSEBUTTONUP || events.type==SDL_MOUSEMOTION)
    {
        input_mouse=1;
        int x,y;
        SDL_GetMouseState(&x,&y);
        x_pos=x-width_frame/2;
        y_pos=y-height_frame/2;
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
        Bullet* p_bullet=new Bullet();
        p_bullet->LoadTexture("img//bullet.png",screen);
        p_bullet->set_pos(Rect.x+width_frame/2-18,Rect.y+height_frame*0.1);
        p_bullet->set_angle(angle);
        p_bullet->set_x_speed(3);
        p_bullet->set_y_speed(3);
        p_bullet->set_is_move(true);
        p_bullet_list.push_back(p_bullet);
        LastTime=CurrentTime;
    }
}
void Character::HandleBullet1(SDL_Renderer* des)
{
    for(int i=0;i<p_bullet_list.size();i++)
    {
        Bullet* p_bullet=p_bullet_list.at(i);
        if(p_bullet!=NULL)
        {
            if(p_bullet->get_is_move()==true)
            {
                p_bullet->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);
                p_bullet->Render(des);
            }
            else
            {
                p_bullet_list.erase(p_bullet_list.begin()+i);
                if(p_bullet!=NULL)
                {
                    delete p_bullet;
                    p_bullet=NULL;
                }
            }
        }
    }
}

void Character::RemoveBullet(const int &index)
{
    int n=p_bullet_list.size();
    if(n>0 && index<n)
    {
        Bullet*p_bullet=p_bullet_list.at(index);
        p_bullet_list.erase(p_bullet_list.begin()+index);
        if(p_bullet)
        {
            delete p_bullet;
            p_bullet=NULL;
        }
    }
}
void Character::Reset()
{
    x_pos=SCREEN_WIDTH/2-32;
    y_pos=SCREEN_HEIGHT-100;
    life=3;
    p_bullet_list.erase(p_bullet_list.begin(),p_bullet_list.begin()+p_bullet_list.size());
}

