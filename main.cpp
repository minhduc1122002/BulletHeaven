#include "Game_Utils.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "Enemy.h"
#include "Text.h"
#include "Icon.h"
#include "EnemyArray.h"
using namespace std;

BaseObject g_background;
BaseObject test_menu;
BaseObject test_help;
TTF_Font* general_font=NULL;
TTF_Font* paused_font=NULL;
Mix_Chunk* BGM=NULL;
Mix_Chunk* hit=NULL;
Mix_Chunk* dead=NULL;
Mix_Chunk* Menu=NULL;
MainObject spaceship;
Effect life_icon[3];
Text currentscore;
Text numberofcurrentscore;
Text highscore;
Text numberofhighscore;
Text Lives;
Text Paused;

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
        paused_font=TTF_OpenFont("fonts//VCR_OSD_MONO_1.001.ttf",50);
        if(general_font==NULL || paused_font==NULL)
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
        Menu=Mix_LoadWAV("musics//Menu.wav");
        if(BGM==NULL || hit==NULL || dead==NULL ||Menu==NULL)
        {
            success=false;
        }
    }
    return success;
}
bool LoadBackground()
{
    bool ret=g_background.LoadImg("img//background2.png",g_screen);
    if(ret==false)
        return false;
    return true;
}
void close()
{
    g_background.Free();
    test_help.Free();
    test_menu.Free();
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
    Mix_FreeChunk(Menu);
    Menu=NULL;
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

    for(int i=0;i<3;i++)
    {
        life_icon[i].LoadImg("img//heart_icon.png",g_screen);
        life_icon[i].SetRect(SCREEN_WIDTH-25-life_icon[i].get_frame_width()*2-32*(i-1),life_icon[i].get_frame_height());
    }

    spaceship.LoadImg("img//spaceship_up.png",g_screen);
    spaceship.set_clip();

    test_menu.LoadImg("img//menu.png",g_screen);
    test_help.LoadImg("img//help.png",g_screen);

    vector<Enemy*> Enemy_List;
    vector<BulletObject*> Bullet_List;
    vector<Effect*> Health_List;

    long current_score=0;

    currentscore.SetColor(Text::REDCOLOR);
    numberofcurrentscore.SetColor(Text::WHITECOLOR);
    numberofhighscore.SetColor(Text::WHITECOLOR);
    highscore.SetColor(Text::REDCOLOR);
    Lives.SetColor(Text::REDCOLOR);
    Paused.SetColor(Text::WHITECOLOR);

    string str_high_score=Game_Utils::GetHighScoreFromFile("high_score.txt");
    string str_highscore="HI-SCORE";
    string str_currentscore="SCORE";
    string str_lives="HEALTH";
    string str_paused="PAUSED";

    Lives.Set_Text(str_lives);
    Lives.LoadFromRenderText(general_font,g_screen);

    currentscore.Set_Text(str_currentscore);
    currentscore.LoadFromRenderText(general_font,g_screen);

    highscore.Set_Text(str_highscore);
    highscore.LoadFromRenderText(general_font,g_screen);

    Paused.Set_Text(str_paused);
    Paused.LoadFromRenderText(paused_font,g_screen);

    Mix_VolumeChunk(BGM,MIX_MAX_VOLUME/4);
    Mix_VolumeChunk(Menu,MIX_MAX_VOLUME/4);
    Mix_VolumeChunk(hit,MIX_MAX_VOLUME/10);
    Mix_VolumeChunk(dead,6);


    bool is_quit=true;
    bool play=false;
    bool menu=false;
    bool help=false;

    if(!menu && is_quit && !help)
    {
        Mix_PlayChannel(-1,Menu,-1);
    }
    SDL_Event button;
    while(!menu)
    {
        while(SDL_PollEvent(&button)!=0)
        {
            if(button.type==SDL_QUIT)
            {
                menu=true;
            }
            if(button.type==SDL_KEYDOWN)
            {
                if(button.key.keysym.sym==SDLK_z)
                {
                   menu=true;
                   is_quit=false;
                }
                else if(button.key.keysym.sym==SDLK_h)
                {
                    help=true;
                    menu=true;
                }
                else if(button.key.keysym.sym==SDLK_ESCAPE)
                {
                    menu=true;
                    help=false;
                    is_quit=true;
                }
            }
        }
        test_menu.Render(g_screen);
        SDL_RenderPresent(g_screen);
    }
    while(help)
    {
        while(SDL_PollEvent(&button)!=0)
        {
            if(button.type==SDL_QUIT)
            {
                help=false;
            }
            if(button.type==SDL_KEYDOWN)
            {
                if(button.key.keysym.sym==SDLK_z)
                {
                   is_quit=false;
                   help=false;
                }
                else if(button.key.keysym.sym==SDLK_ESCAPE)
                {
                    is_quit=true;
                    help=false;
                }
            }
        }
        test_help.Render(g_screen);
        SDL_RenderPresent(g_screen);
    }
    if(!is_quit && menu)
    {
        Mix_PlayChannel(-1,BGM,-1);
        Mix_FreeChunk(Menu);
        Menu=NULL;
    }
    SDL_WarpMouseInWindow(g_window,SCREEN_WIDTH/2-32,SCREEN_HEIGHT-100);
    bool paused=false;
    while(!is_quit)
    {
        if(paused)
        {
            SDL_WarpMouseInWindow(g_window,spaceship.GetRect().x,spaceship.GetRect().y);
            while(SDL_PollEvent(&g_event)!=0)
            {
                if(g_event.type==SDL_QUIT)
                {
                    is_quit=true;
                }
                if(g_event.type==SDL_KEYDOWN)
                {
                    if(g_event.key.keysym.sym==SDLK_p)
                    {
                        paused=false;
                    }
                    if(g_event.key.keysym.sym==SDLK_ESCAPE)
                    {
                        is_quit=true;
                    }
                }
            }
            /*Paused.RenderText(g_screen,SCREEN_WIDTH/2-80,SCREEN_HEIGHT/2-20);
            SDL_RenderPresent(g_screen);*/
        }
        else if(!paused)
        {
            while(SDL_PollEvent(&g_event)!=0)
            {

                if(g_event.type==SDL_QUIT)
                {
                    is_quit=true;
                }
                if(g_event.type==SDL_KEYDOWN)
                {
                    if(g_event.key.keysym.sym==SDLK_p)
                    {
                        paused=true;
                    }
                    if(g_event.key.keysym.sym==SDLK_ESCAPE)
                    {
                        is_quit=true;
                    }
                }
                spaceship.HandleInputAction(g_event,g_screen);
            }
            SDL_RenderClear(g_screen);
            SDL_ShowCursor(SDL_DISABLE);

            g_background.MoveBackGround(g_screen,NULL);
            GenerateEnemy(Enemy_List,g_screen);

            spaceship.Show(g_screen);
            spaceship.SpawnBullet(g_screen);
            spaceship.HandleBullet1(g_screen);

            for(int i=0;i<Enemy_List.size();i++)
            {
                Enemy *p_enemy=Enemy_List.at(i);
                if(p_enemy!=NULL)
                {
                    p_enemy->MoveThreat();
                    p_enemy->Show(g_screen);
                    if(p_enemy->canspawnbullet()==1)
                    {
                        p_enemy->MakeBullet(Bullet_List,g_screen,spaceship);
                    }
                    SDL_Rect spaceshipRect=spaceship.GetRectFrame();
                    if(p_enemy!=NULL)
                    {
                        SDL_Rect ThreatRect=p_enemy->GetRect();
                        bool Threat_to_Spaceship=Game_Utils::CheckCollision(spaceshipRect,ThreatRect);
                        if(Threat_to_Spaceship)
                        {
                            spaceship.got_hit(dead);
                            Mix_PlayChannel(-1,dead,0);
                            spaceship.SetRect(-100,SCREEN_HEIGHT-100);
                            if(spaceship.get_life()==3)
                            {

                            }
                            if(p_enemy->get_type_threat()!=6.1)
                            {
                                Enemy_List.erase(Enemy_List.begin()+i);
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
            for(int i=0;i<Bullet_List.size();i++)
            {
                BulletObject*p_bullet=Bullet_List.at(i);
                if(p_bullet!=NULL)
                {
                    SDL_Rect BulletRect=p_bullet->GetRect();
                    SDL_Rect Main_Rect=spaceship.GetRectFrame();
                    bool ThreatBullet_to_spaceship=Game_Utils::CheckCollision(BulletRect,Main_Rect);
                    if(ThreatBullet_to_spaceship)
                    {
                        spaceship.got_hit(dead);
                        Bullet_List.erase(Bullet_List.begin()+i);
                    }
                    if(p_bullet->get_is_move()==true)
                    {
                        p_bullet->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);
                        p_bullet->Render(g_screen);
                    }
                    else
                    {
                        Bullet_List.erase(Bullet_List.begin()+i);
                        delete p_bullet;
                        p_bullet=NULL;
                    }
                }
            }
            vector<BulletObject*> spaceship_bullet_arr=spaceship.get_bullet_list1();
            for(int i=0;i<spaceship_bullet_arr.size();i++)
            {
                BulletObject*p_bullet=spaceship_bullet_arr.at(i);
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
                            bool SpaceshipBullet_to_Threat=Game_Utils::CheckCollision(ThreatRect,BulletRect);
                            if(SpaceshipBullet_to_Threat)
                            {
                                p_enemy->increase_die();
                                spaceship.RemoveBullet(i);
                                if(p_enemy->check_die())
                                {
                                   p_enemy->Generate_Health(Health_List,g_screen);
                                   Mix_PlayChannel(-1,hit,0);
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
                Effect*p_health=Health_List.at(i);
                if(p_health!=NULL)
                {
                    SDL_Rect HeartRect=p_health->GetRect();
                    SDL_Rect MainRect=spaceship.GetRectFrame();
                    bool Heart_to_spaceship=Game_Utils::CheckCollision(HeartRect,MainRect);
                    if(Heart_to_spaceship)
                    {
                        spaceship.life_increase();
                        Health_List.erase(Health_List.begin()+i);
                    }
                    if(p_health->get_is_move()==true)
                    {
                        p_health->MoveEffect(SCREEN_WIDTH,SCREEN_HEIGHT);
                        p_health->Render(g_screen);
                    }
                    else
                    {
                        Health_List.erase(Health_List.begin()+i);
                        delete p_health;
                        p_health=NULL;
                    }
                }
            }
            Game_Utils::UpdateHighScore("high_score.txt",current_score,str_high_score);
            highscore.RenderText(g_screen,SCREEN_WIDTH/2-50,10);
            currentscore.RenderText(g_screen,10,10);
            Lives.RenderText(g_screen,SCREEN_WIDTH-120,10);

            numberofcurrentscore.Set_Text(Game_Utils::number_to_string(current_score));
            numberofcurrentscore.LoadFromRenderText(general_font,g_screen);
            numberofcurrentscore.RenderText(g_screen,10,35);

            numberofhighscore.Set_Text(str_high_score);
            numberofhighscore.LoadFromRenderText(general_font,g_screen);
            numberofhighscore.RenderText(g_screen,SCREEN_WIDTH/2-40,35);

            for(int i=0;i<spaceship.get_life();i++)
            {
                life_icon[i].Render(g_screen);
            }
            SDL_Delay(2);
            SDL_RenderPresent(g_screen);
        }
    }
    close();
    return 0;
}
