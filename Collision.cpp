#include "Collision.h"
using namespace std;

void Collision(vector<Enemy*>&Enemy_List,Character &spaceship,
               vector<Bullet*> &Bullet_List,vector<Icon*>&Health_List,
               SDL_Renderer* screen,Mix_Chunk* dead,Mix_Chunk* hit,Mix_Chunk* Power,long &current_score,
               bool &GameOver)
{
    for(int i=0;i<Enemy_List.size();i++)
    {
        Enemy *p_enemy=Enemy_List.at(i);
        if(p_enemy!=NULL)
        {
            p_enemy->MoveThreat();
            p_enemy->Show(screen);
            if(p_enemy->canspawnbullet()==1)
            {
                p_enemy->MakeBullet(Bullet_List,screen,spaceship);
            }
            SDL_Rect spaceshipRect=spaceship.GetHitBox();
            if(p_enemy!=NULL)
            {
                SDL_Rect ThreatRect=p_enemy->GetRect();
                bool Threat_to_Spaceship=CheckCollision(spaceshipRect,ThreatRect);
                if(Threat_to_Spaceship)
                {
                    spaceship.got_hit(dead);
                    spaceship.SetRect(-100,SCREEN_HEIGHT-100);
                    if(spaceship.get_life()==0)
                    {
                        GameOver=true;
                    }
                }
            }
        }
    }
    for(int i=0;i<Bullet_List.size();i++)
    {
        Bullet*p_bullet=Bullet_List.at(i);
        if(p_bullet!=NULL)
        {
            SDL_Rect BulletRect=p_bullet->GetRect();
            SDL_Rect Main_Rect=spaceship.GetHitBox();
            bool ThreatBullet_to_spaceship=CheckCollision(BulletRect,Main_Rect);
            if(ThreatBullet_to_spaceship)
            {
                spaceship.got_hit(dead);
                Mix_PlayChannel(-1,dead,0);
                if(spaceship.get_life()==0)
                {
                    GameOver=true;
                }
                Bullet_List.erase(Bullet_List.begin()+i);
            }
            if(p_bullet->get_is_move()==true)
            {
                p_bullet->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);
                p_bullet->Render(screen);
            }
            else
            {
                Bullet_List.erase(Bullet_List.begin()+i);
                delete p_bullet;
                p_bullet=NULL;
            }
        }
    }
    vector<Bullet*> spaceship_bullet_arr=spaceship.get_bullet_list();
    for(int i=0;i<spaceship_bullet_arr.size();i++)
    {
        Bullet*p_bullet=spaceship_bullet_arr.at(i);
        if(p_bullet!=NULL)
        {
            for(int j=0;j<Enemy_List.size();j++)
            {
                Enemy* p_enemy=Enemy_List.at(j);
                if(p_enemy!=NULL)
                {
                    SDL_Rect ThreatRect;
                    ThreatRect=p_enemy->GetRect();
                    SDL_Rect BulletRect=p_bullet->GetRect();
                    bool SpaceshipBullet_to_Threat=CheckCollision(ThreatRect,BulletRect);
                    if(SpaceshipBullet_to_Threat)
                    {
                        p_enemy->increase_die();
                        spaceship.RemoveBullet(i);
                        if(p_enemy->check_die())
                        {
                            p_enemy->MakeBulletUponDeath(Bullet_List,screen);
                            p_enemy->Generate_Health(Health_List,screen);
                            Mix_PlayChannel(4,hit,0);
                            current_score+=(p_enemy->get_score());
                            Enemy_List.erase(Enemy_List.begin()+j);
                            if(p_enemy!=NULL)
                            {
                                delete p_enemy;
                                p_enemy=NULL;
                            }
                        }
                    }
                }
            }
        }
    }
    for(int i=0;i<Health_List.size();i++)
    {
        Icon*p_health=Health_List.at(i);
        if(p_health!=NULL)
        {
            SDL_Rect HeartRect=p_health->GetRect();
            SDL_Rect MainRect=spaceship.GetHitBox();
            bool Heart_to_spaceship=CheckCollision(HeartRect,MainRect);
            if(Heart_to_spaceship)
            {
                spaceship.life_increase();
                Mix_PlayChannel(4,Power,0);
                Health_List.erase(Health_List.begin()+i);
            }
            if(p_health->get_is_move()==true)
            {
                p_health->MoveEffect(SCREEN_WIDTH,SCREEN_HEIGHT);
                p_health->Render(screen);
            }
            else
            {
                Health_List.erase(Health_List.begin()+i);
                delete p_health;
                p_health=NULL;
            }
        }
    }
}
