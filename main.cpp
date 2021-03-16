#include <iostream>
#include <vector>
#include "CommonFunc.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "ThreatObject.h"

using namespace std;
BaseObject g_background;

bool InitData()
{
    bool success=true;
    int ret=SDL_Init(SDL_INIT_VIDEO);
    if(ret<0) return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");

    g_window=SDL_CreateWindow("Game",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
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

vector<ThreatObject*> MakeThreatList()
{
    vector<ThreatObject*> Threat_List;

    ThreatObject* threat_object=new ThreatObject[2];
    for(int i=0;i<2;i++)
    {
        ThreatObject* p_threat=(threat_object+i);
        if(p_threat!=NULL)
        {

            p_threat->LoadImg("img//SpaceThreat1.png",g_screen);
            p_threat->set_clip();
            p_threat->set_x_pos_((i+1)*SCREEN_WIDTH/3);
            p_threat->set_y_pos_(0);
            p_threat->set_x_val_(0.5);
            p_threat->set_y_val_(0.5);

            Threat_List.push_back(p_threat);
        }
    }
    return Threat_List;
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

    vector<ThreatObject*> Threat_List=MakeThreatList();

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
        g_background.Render(g_screen,NULL);
        spaceship.HandleBullet1(g_screen);
        spaceship.Show(g_screen);
        spaceship.MovePlayer();
        for(int i=0;i<Threat_List.size();i++)
        {
            ThreatObject *p_threat=Threat_List.at(i);
            if(p_threat!=NULL)
            {
                p_threat->Show(g_screen);
                p_threat->MoveThreat();
                if((p_threat->get_y_pos_())%200==0)
                {
                    BulletObject*p_bullet1=new BulletObject();
                    p_threat->InitBullet(p_bullet1,g_screen);
                }
                p_threat->MakeBullet(g_screen,SCREEN_WIDTH,SCREEN_HEIGHT);
            }
        }
        SDL_RenderPresent(g_screen);


    }
    close();
    return 0;
}
