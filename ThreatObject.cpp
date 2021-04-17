#include "ThreatObject.h"
using namespace std;
ThreatObject::ThreatObject()
{
    width_frame_=0;
    height_frame_=0;
    frame_=0;
    angle_move_=90;
    die=0;
    score=100;
    CurrentTime=0;
    LastTime=0;
}
ThreatObject::~ThreatObject()
{

}

bool ThreatObject::LoadImg(string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path,screen);

    if(ret==true)
    {
        width_frame_=rect_.w/Num_of_Frame_Enemy;
        height_frame_=rect_.h;
    }
    return ret;
}

void ThreatObject::resizebullet()
{
    if(type==1)
    {
        n=3;
    }
    else
    {
        n=1;
    }
    p_bullet_list1_.resize(n);
}
void ThreatObject::set_clip()
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

void ThreatObject::Show(SDL_Renderer* des)
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

void ThreatObject::MoveThreat_Type1()
{
    if(type==1)
    {
        y_pos_+=y_val_;
    }
    else if(type==2)
    {
        x_pos_+=x_val_;
    }
}

void ThreatObject::InitBullet(SDL_Renderer* screen)
{
    resizebullet();
    CurrentTime=SDL_GetTicks();
    if(type==1)
    {
        if(CurrentTime>LastTime+550)
        {
            for(int i=0;i<p_bullet_list1_.size();i++)
            {
                BulletObject*p_bullet1=new BulletObject();
                p_bullet1->LoadImg("img//BulletThreat.png",screen);
                p_bullet1->set_is_move(true);
                p_bullet1->SetRect(x_pos_+30,y_pos_+24);
                p_bullet1->set_x_val(3);
                p_bullet1->set_y_val(3);
                p_bullet_list1_.at(i).push_back(p_bullet1);
                LastTime=CurrentTime;
            }
        }
    }
    else
    {
        if(CurrentTime>LastTime+500)
        {
            for(int i=0;i<p_bullet_list1_.size();i++)
            {
                BulletObject*p_bullet1=new BulletObject();
                p_bullet1->LoadImg("img//BulletThreat.png",screen);
                p_bullet1->set_is_move(true);
                p_bullet1->SetRect(x_pos_+30,y_pos_);
                p_bullet1->set_x_val(3);
                p_bullet1->set_y_val(3);
                p_bullet_list1_.at(i).push_back(p_bullet1);
                LastTime=CurrentTime;
            }
        }
    }
}

void ThreatObject::MakeBullet(SDL_Renderer* screen,const int &x_limit,const int &y_limit)
{
    for(int i=0;i<p_bullet_list1_.size();i++)
    {
        for(int j=0;j<p_bullet_list1_.at(i).size();j++)
        {
            BulletObject* p_bullet1=p_bullet_list1_.at(i).at(j);
            double angle;
            if(i==0)
            {
                angle=90;
            }
            else if(i==1)
            {
                angle=45;
            }
            else if(i==2)
            {
                angle=135;
            }
            if(p_bullet1!=NULL)
            {
                if(p_bullet1->get_is_move()==true)
                {
                    p_bullet1->HandleMove(x_limit,y_limit,angle);
                    p_bullet1->Render(screen);
                }
                else
                {
                    p_bullet_list1_.at(i).erase(p_bullet_list1_.at(i).begin()+j);
                    if(p_bullet1!=NULL)
                    {
                        delete p_bullet1;
                        p_bullet1=NULL;
                    }
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

void ThreatObject::RemoveBullet(const int &index1,const int &index2)
{
    int n1=p_bullet_list1_.size();
    int n2=p_bullet_list1_.at(index1).size();
    if((n1>0 && index1<n1)&&(n2>0 && index2<n2))
    {
        BulletObject*p_bullet=p_bullet_list1_.at(index1).at(index2);
        p_bullet_list1_.at(index1).erase(p_bullet_list1_.at(index1).begin()+index2);
        if(p_bullet)
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


