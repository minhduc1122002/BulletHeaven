#include <iostream>
#include <vector>
#include "CommonFunc.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "ThreatObject.h"
#include "GUI.h"
using namespace std;

BaseObject g_background;
TTF_Font* Score=NULL;

bool InitData()
{
    bool success=true;
    int ret=SDL_Init(SDL_INIT_VIDEO);
    if(ret<0) return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");

    g_window=SDL_CreateWindow("SHMUP",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if(g_window==NULL)
    {
        success=false;
    }
    else
    {
        g_screen=SDL_CreateRenderer(g_window,-1,SDL_RENDERER_ACCELERATED);
        if(g_screen==NULL)
        {
            success=false;
        }
        else
        {
            SDL_SetRenderDrawColor(g_screen,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);
            int imgFlags=IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) && imgFlags))
                success=false;
        }
        if(TTF_Init()==-1)
        {
            success=false;
        }
        Score=TTF_OpenFont("fonts//Minecraft.ttf",20);
        if(Score==NULL)
        {
            success=false;
        }
    }
    return success;
}
bool LoadBackground()
{
    bool ret=g_background.LoadImg("img//background.png",g_screen);
    if(ret==false)
        return false;
    return true;
}
void close()
{
    g_background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen=NULL;
    SDL_DestroyWindow(g_window);
    g_window=NULL;
    IMG_Quit();
    SDL_Quit();
}

int main( int argc, char *argv[] )
{
    if(InitData()==false)
        return -1;
    if(LoadBackground()==false)
        return -1;

    MainObject spaceship;
    spaceship.LoadImg("img//spaceship_up.png",g_screen);
    spaceship.set_clip();


    vector<ThreatObject*> Threat_List;

    Text score_game;
    score_game.SetColor(1);

    bool is_quit=false;
    while(!is_quit)
    {
        while(SDL_PollEvent(&g_event)!=0)
        {

            if(g_event.type==SDL_QUIT)
            {
                is_quit=true;
            }
            spaceship.HandleInputAction(g_event,g_screen);
        }
        SDL_SetRenderDrawColor(g_screen,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);


        g_background.MoveBackGround(g_screen,NULL);

        spaceship.Show(g_screen);
        spaceship.MovePlayer();
        spaceship.HandleBullet1(g_screen);
        ThreatObject* threat_object=new ThreatObject();
        if(Threat_List.size()<=0)
        {
            threat_object->random_type_threat();
            threat_object->set_stats(g_screen);
            Threat_List.push_back(threat_object);
        }
        else
        {
            if(Threat_List.at(Threat_List.size()-1)->get_type_threat()==1&& Threat_List.at(Threat_List.size()-1)->get_y_pos_()==500)
            {
                threat_object->random_type_threat();
                threat_object->set_stats(g_screen);
                Threat_List.push_back(threat_object);
            }
            if(Threat_List.at(Threat_List.size()-1)->get_type_threat()==2 && Threat_List.at(Threat_List.size()-1)->get_x_pos_()==400)
            {
                threat_object->random_type_threat();
                threat_object->set_stats(g_screen);
                Threat_List.push_back(threat_object);
            }
        }
        for(int i=0;i<Threat_List.size();i++)
        {
            ThreatObject *p_threat=Threat_List.at(i);
            if(p_threat!=NULL)
            {

                p_threat->MoveThreat_Type1();
                p_threat->InitBullet(g_screen);
                p_threat->MakeBullet(g_screen,SCREEN_WIDTH,SCREEN_HEIGHT);
                p_threat->Show(g_screen);
                if(p_threat->get_y_pos_()>SCREEN_HEIGHT || p_threat->get_x_pos_()>SCREEN_HEIGHT+500 || p_threat->get_x_pos_()<0-500)
                {
                    Threat_List.erase(Threat_List.begin()+i);
                    if(p_threat!=NULL)
                    {
                        delete p_threat;
                        p_threat=NULL;
                    }
                }
                bool ThreatBulletCol=0;
                SDL_Rect spaceshipRect=spaceship.GetRectFrame();
                if(p_threat!=NULL)
                {
                   std::vector<BulletObject*> ThreatBullet_arr=p_threat->get_bullet_list1();
                   for(int k=0;k<ThreatBullet_arr.size();k++)
                    {
                        BulletObject* p_bullet=ThreatBullet_arr.at(k);
                        if(p_bullet!=NULL)
                        {
                            SDL_Rect BulletRect=p_bullet->GetRect();
                            ThreatBulletCol=SDLCommonFunc::CheckCollision(spaceshipRect,BulletRect);
                            if(ThreatBulletCol)
                            {
                                p_threat->RemoveBullet(k);
                                spaceship.life_decrease();
                                break;

                            }
                        }
                    }
                    SDL_Rect ThreatRect=p_threat->GetRect();
                    bool ThreatCol=SDLCommonFunc::CheckCollision(spaceshipRect,ThreatRect);
                    if(ThreatCol)
                    {
                        spaceship.life_decrease();
                        Threat_List.erase(Threat_List.begin()+i);
                        delete p_threat;
                        p_threat=NULL;
                    }

                }
            }
        }
        std::vector<BulletObject*> spaceship_bullet_arr=spaceship.get_bullet_list1();
        for(int i=0;i<spaceship_bullet_arr.size();i++)
        {
            BulletObject*p_bullet=spaceship_bullet_arr.at(i);
            if(p_bullet!=NULL)
            {
                for(int j=0;j<Threat_List.size();j++)
                {
                    ThreatObject*p_threat=Threat_List.at(j);
                    if(p_threat!=NULL)
                    {
                        SDL_Rect ThreatRect;
                        ThreatRect=p_threat->GetRect();
                        SDL_Rect BulletRect=p_bullet->GetRect();
                        bool BulletCol=SDLCommonFunc::CheckCollision(ThreatRect,BulletRect);
                        if(BulletCol)
                        {
                            spaceship.RemoveBullet(i);
                            p_threat->increase_die();
                            if(p_threat->get_die()==2)
                            {
                                Threat_List.erase(Threat_List.begin()+j);
                                if(p_threat!=NULL)
                                {
                                    delete p_threat;
                                    p_threat=NULL;
                                }
                            }
                        }
                    }
                }
            }
        }
        std::string str_score="HIGH SCORE";
        score_game.Set_Text(str_score);
        score_game.LoadFromRenderText(Score,g_screen);
        score_game.RenderText(g_screen,SCREEN_WIDTH-200,20);

        SDL_Delay(2);
        SDL_RenderPresent(g_screen);
    }
    close();
    return 0;
}
