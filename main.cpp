#include <iostream>
#include "CommonFunc.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "ThreatObject.h"
#include "Text.h"
#include "Effect.h"
using namespace std;

BaseObject g_background;
TTF_Font* general_font=NULL;
Mix_Chunk* BGM=NULL;
Mix_Chunk* hit=NULL;
Mix_Chunk* dead=NULL;
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
            int imgFlags=IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) && imgFlags))
                success=false;
        }
        if(TTF_Init()==-1)
        {
            success=false;
        }
        general_font=TTF_OpenFont("fonts//VCR_OSD_MONO_1.001.ttf",25);
        if(general_font==NULL)
        {
            success=false;
        }
        if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0)
        {
            success=false;
        }
        BGM=Mix_LoadWAV("musics//bgm.wav");
        hit=Mix_LoadWAV("musics//SE_enemy_vanish.wav");
        dead=Mix_LoadWAV("musics//SE_dead.wav");
        if(BGM==NULL)
        {
            success=false;
        }
        else if(hit==NULL)
        {
            success=false;
        }
        else if(dead==NULL)
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
    Mix_FreeChunk(BGM);
    BGM=NULL;
    Mix_FreeChunk(hit);
    hit=NULL;
    Mix_FreeChunk(dead);
    dead=NULL;
    Mix_Quit();
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

    Effect shockwave;
    shockwave.LoadImg("img//unnamed.png",g_screen);


    vector<ThreatObject*> Threat_List;

    Text currentscore,numberofcurrentscore;
    Text highscore;
    Text score_of_enemy;
    Text Lives,numberoflives;
    currentscore.SetColor(Text::REDCOLOR);
    numberofcurrentscore.SetColor(Text::WHITECOLOR);
    highscore.SetColor(Text::REDCOLOR);
    Lives.SetColor(Text::REDCOLOR);
    numberoflives.SetColor(Text::WHITECOLOR);
    score_of_enemy.SetColor(Text::WHITECOLOR);

    string str_highscore="HI-SCORE";
    string str_currentscore="SCORE";
    string str_lives="LIVES";

    Lives.Set_Text(str_lives);
    Lives.LoadFromRenderText(general_font,g_screen);
    currentscore.Set_Text(str_currentscore);
    currentscore.LoadFromRenderText(general_font,g_screen);
    highscore.Set_Text(str_highscore);
    highscore.LoadFromRenderText(general_font,g_screen);
    score_of_enemy.Set_Text("100");
    score_of_enemy.LoadFromRenderText(general_font,g_screen);


    Mix_VolumeChunk(BGM,MIX_MAX_VOLUME/4);
    Mix_VolumeChunk(hit,MIX_MAX_VOLUME/10);
    Mix_VolumeChunk(dead,6);

    Mix_PlayChannel(-1,BGM,-1);


    long current_score=0;

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
                if(p_threat->get_y_pos_()>SCREEN_HEIGHT || p_threat->get_x_pos_()>SCREEN_WIDTH+400 || p_threat->get_x_pos_()<-400)
                {
                    Threat_List.erase(Threat_List.begin()+i);
                    if(p_threat!=NULL)
                    {
                        delete p_threat;
                        p_threat=NULL;
                    }
                }
                bool ThreatBullet_to_Spaceship=0;
                SDL_Rect spaceshipRect=spaceship.GetRectFrame();
                if(p_threat!=NULL)
                {
                   vector< vector<BulletObject*> > ThreatBullet_arr=p_threat->get_bullet_list1();
                   for(int k=0;k<ThreatBullet_arr.size();k++)
                    {
                        for(int z=0;z<ThreatBullet_arr.at(k).size();z++)
                        {
                            BulletObject* p_bullet=ThreatBullet_arr.at(k).at(z);
                            if(p_bullet!=NULL)
                            {
                                SDL_Rect BulletRect=p_bullet->GetRect();
                                ThreatBullet_to_Spaceship=SDLCommonFunc::CheckCollision(spaceshipRect,BulletRect);
                                if(ThreatBullet_to_Spaceship)
                                {
                                    p_threat->RemoveBullet(k,z);
                                    spaceship.life_decrease();
                                    Mix_PlayChannel(-1,dead,0);
                                    if(spaceship.get_life()==3)
                                    {

                                    }
                                    break;

                                }
                            }
                        }
                    }
                    SDL_Rect ThreatRect=p_threat->GetRect();
                    bool Threat_to_Spaceship=SDLCommonFunc::CheckCollision(spaceshipRect,ThreatRect);
                    if(Threat_to_Spaceship)
                    {
                        spaceship.life_decrease();
                        Mix_PlayChannel(-1,dead,0);
                        spaceship.SetRect(-100,SCREEN_HEIGHT-100);
                        if(spaceship.get_life()==3)
                        {

                        }
                        Threat_List.erase(Threat_List.begin()+i);
                        if(p_threat!=NULL)
                        {
                            delete p_threat;
                            p_threat=NULL;
                        }
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
                        bool SpaceshipBullet_to_Threat=SDLCommonFunc::CheckCollision(ThreatRect,BulletRect);
                        if(SpaceshipBullet_to_Threat)
                        {
                            p_threat->increase_die();
                            spaceship.RemoveBullet(i);
                            if(p_threat->get_die()==3)
                            {
                               Mix_PlayChannel(-1,hit,0);
                               current_score+=(p_threat->get_score());
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


        int n=spaceship.get_life();

        highscore.RenderText(g_screen,SCREEN_WIDTH/2-50,10);
        currentscore.RenderText(g_screen,10,10);
        Lives.RenderText(g_screen,SCREEN_WIDTH-120,10);

        numberofcurrentscore.Set_Text(SDLCommonFunc::number_to_string(current_score));
        numberofcurrentscore.LoadFromRenderText(general_font,g_screen);
        numberofcurrentscore.RenderText(g_screen,10,35);

        numberoflives.Set_Text(SDLCommonFunc::number_to_string(n));
        numberoflives.LoadFromRenderText(general_font,g_screen);
        numberoflives.RenderText(g_screen,SCREEN_WIDTH-120,35);


        SDL_Delay(1);
        SDL_RenderPresent(g_screen);
    }
    close();
    return 0;
}
