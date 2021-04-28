#include "Game_Utils.h"
#include "Texture.h"
#include "Character.h"
#include "Enemy.h"
#include "Text.h"
#include "Icon.h"
#include "EnemyArray.h"
#include "Collision.h"
#include "Button.h"
using namespace std;
Texture Background;
Texture GameOverUI;
Texture test_menu;
Texture test_pause;
Texture test_help;
TTF_Font* general_font=NULL;
TTF_Font* paused_font=NULL;
Mix_Chunk* BGM=NULL;
Mix_Chunk* hit=NULL;
Mix_Chunk* dead=NULL;
Mix_Chunk* Menu=NULL;
Mix_Chunk* BBGM=NULL;
Mix_Chunk* Power=NULL;
Character spaceship;
Icon life_icon[3];
Text currentscore;
Text numberofcurrentscore;
Text highscore;
Text numberofhighscore;
Text Lives;
Text Wave;
Text Paused;
Text Rating;
Button PlayButton;
Button HelpButton;
Button ExitButton;
Button BackButton;
Button RestartButton;

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
        paused_font=TTF_OpenFont("fonts//VCR_OSD_MONO_1.001.ttf",55);
        if(general_font==NULL || paused_font==NULL)
        {
            success=false;
        }
        if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0)
        {
            success=false;
        }
        BGM=Mix_LoadWAV("musics//BGM.wav");
        hit=Mix_LoadWAV("musics//SE_enemy_vanish.wav");
        dead=Mix_LoadWAV("musics//SE_dead.wav");
        Menu=Mix_LoadWAV("musics//Menu.wav");
        BBGM=Mix_LoadWAV("musics//BossMusic2.wav");
        Power=Mix_LoadWAV("musics//SE_powerup.wav");
        if(BGM==NULL || hit==NULL || dead==NULL || Menu==NULL || BBGM==NULL || Power==NULL)
        {
            success=false;
        }
    }
    return success;
}
void close()
{
    Background.Free();
    test_help.Free();
    test_menu.Free();
    GameOverUI.Free();
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
    Mix_FreeChunk(BBGM);
    BBGM=NULL;
    Mix_FreeChunk(Power);
    Power=NULL;
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main( int argc, char *argv[] )
{
    long current_score=0;
    int wave=0;
    if(InitData()==false)
    {
        return 0;
    }
    for(int i=0;i<3;i++)
    {
        life_icon[i].LoadTexture("img//heart_icon.png",g_screen);
        life_icon[i].SetRect(SCREEN_WIDTH-25-life_icon[i].get_frame_width()*2-32*(i-1),life_icon[i].get_frame_height());
    }
    Background.LoadTexture("img//background2.png",g_screen);
    spaceship.LoadTexture("img//spaceship_up.png",g_screen);
    spaceship.set_clip();
    test_menu.LoadTexture("img//menu.png",g_screen);
    test_help.LoadTexture("img//help.png",g_screen);
    test_pause.LoadTexture("img//Pause.png",g_screen);
    GameOverUI.LoadTexture("img//GameOver.png",g_screen);

    vector<Enemy*> Enemy_List;
    vector<Bullet*> Bullet_List;
    vector<Icon*> Health_List;

    currentscore.SetColor(Text::REDCOLOR);
    numberofcurrentscore.SetColor(Text::WHITECOLOR);
    numberofhighscore.SetColor(Text::WHITECOLOR);
    highscore.SetColor(Text::REDCOLOR);
    Lives.SetColor(Text::REDCOLOR);
    Paused.SetColor(Text::WHITECOLOR);
    Wave.SetColor(Text::WHITECOLOR);
    Rating.SetColor(Text::REDCOLOR);

    string str_high_score=GetHighScoreFromFile("high_score.txt");
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
    Mix_VolumeChunk(BBGM,MIX_MAX_VOLUME/4);
    Mix_VolumeChunk(Menu,MIX_MAX_VOLUME/4);
    Mix_VolumeChunk(hit,MIX_MAX_VOLUME/10);
    Mix_VolumeChunk(dead,MIX_MAX_VOLUME/10);
    Mix_VolumeChunk(Power,MIX_MAX_VOLUME/10);

    bool play=false;
    bool menu=true;
    bool help=false;
    bool QuitMenu=false;
    while(!QuitMenu)
    {
        if(!Mix_Playing(1))
        {
            Mix_PlayChannel(1,Menu,-1);
        }
        if(menu)
        {
            while(SDL_PollEvent(&g_event)!=0)
            {
                if(g_event.type==SDL_QUIT)
                {
                    QuitMenu=true;

                }
                PlayButton.HandlePlayButton(g_event,g_screen,menu,play,QuitMenu);
                HelpButton.HandleHelpButton(g_event,g_screen,menu,help);
                ExitButton.HandleExitButton(g_event,g_screen,QuitMenu);
            }
            PlayButton.SetRect(SCREEN_WIDTH/2-PlayButton.get_frame_width()/2,SCREEN_HEIGHT/2+110);
            HelpButton.SetRect(SCREEN_WIDTH/2-PlayButton.get_frame_width()/2,SCREEN_HEIGHT/2+210);
            ExitButton.SetRect(SCREEN_WIDTH/2-PlayButton.get_frame_width()/2,SCREEN_HEIGHT/2+310);
            test_menu.Render(g_screen);
            HelpButton.Render(g_screen);
            PlayButton.Render(g_screen);
            ExitButton.Render(g_screen);
            SDL_RenderPresent(g_screen);
        }
        if(help)
        {
            while(SDL_PollEvent(&g_event)!=0)
            {
                if(g_event.type==SDL_QUIT)
                {
                    QuitMenu=true;
                }
                PlayButton.HandlePlayButton(g_event,g_screen,menu,play,QuitMenu);
                BackButton.HandleBackButton(g_event,g_screen,menu,help);
            }
            test_help.Render(g_screen);
            BackButton.SetRect(30,SCREEN_HEIGHT-BackButton.get_frame_height()-30);
            PlayButton.SetRect(SCREEN_WIDTH-PlayButton.get_frame_width()-30,SCREEN_HEIGHT-BackButton.get_frame_height()-30);
            PlayButton.Render(g_screen);
            BackButton.Render(g_screen);
            SDL_RenderPresent(g_screen);
        }
    }
    SDL_WarpMouseInWindow(g_window,SCREEN_WIDTH/2-32,SCREEN_HEIGHT-100);
    bool paused=false;
    bool GameOver=false;
    while(play)
    {
        Mix_HaltChannel(1);
        if(wave%10==0 && wave!=0)
        {
            if(!Mix_Playing(3))
            {
                Mix_PlayChannel(3,BBGM,-1);
            }
            Mix_HaltChannel(2);
        }
        else
        {
            if(!Mix_Playing(2))
            {
                Mix_PlayChannel(2,BGM,-1);
            }
            Mix_HaltChannel(3);
        }
        if(!GameOver)
        {
            if(paused)
            {
                SDL_WarpMouseInWindow(g_window,spaceship.GetRect().x,spaceship.GetRect().y);
                while(SDL_PollEvent(&g_event)!=0)
                {
                    if(g_event.type==SDL_QUIT)
                    {
                        play=false;
                    }
                    if(g_event.type==SDL_KEYDOWN)
                    {
                        if(g_event.key.keysym.sym==SDLK_p)
                        {
                            paused=false;
                        }
                        if(g_event.key.keysym.sym==SDLK_ESCAPE)
                        {
                            play=false;
                        }
                    }
                }
                test_pause.SetRect(0,SCREEN_HEIGHT/3-test_pause.GetRect().h);
                test_pause.Render(g_screen);
                SDL_RenderPresent(g_screen);
            }
            else if(!paused)
            {
                while(SDL_PollEvent(&g_event)!=0)
                {

                    if(g_event.type==SDL_QUIT)
                    {
                        play=false;
                    }
                    if(g_event.type==SDL_KEYDOWN)
                    {
                        if(g_event.key.keysym.sym==SDLK_p)
                        {
                            paused=true;
                        }
                        if(g_event.key.keysym.sym==SDLK_ESCAPE)
                        {
                            play=false;
                        }
                    }
                    spaceship.HandleInputAction(g_event,g_screen);
                }
                SDL_RenderClear(g_screen);
                SDL_ShowCursor(SDL_DISABLE);

                Background.MoveBackGround(g_screen,NULL);
                GenerateEnemy(Enemy_List,g_screen,wave);
                spaceship.Show(g_screen);
                spaceship.SpawnBullet(g_screen);
                spaceship.HandleBullet1(g_screen);
                Collision(Enemy_List,spaceship,Bullet_List,Health_List,g_screen,dead,hit,Power,current_score,GameOver);

                UpdateHighScore("high_score.txt",current_score,str_high_score);
                highscore.RenderText(g_screen,SCREEN_WIDTH/2-50,10);
                currentscore.RenderText(g_screen,10,10);
                Lives.RenderText(g_screen,SCREEN_WIDTH-120,10);

                numberofcurrentscore.Set_Text(number_to_string(current_score));
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
        else
        {
             SDL_ShowCursor(SDL_ENABLE);
             while(SDL_PollEvent(&g_event)!=0)
             {
                if(g_event.type==SDL_QUIT)
                {
                    play=false;
                }
                RestartButton.HandleRestartButton(g_event,g_screen,Enemy_List,spaceship,Bullet_List,Health_List,wave,current_score,GameOver);
                ExitButton.HandleExitButton(g_event,g_screen,play);
             }
             GameOverUI.Render(g_screen);
             RestartButton.SetRect(30,SCREEN_HEIGHT-RestartButton.get_frame_height()-30);
             RestartButton.Render(g_screen);
             ExitButton.SetRect(SCREEN_WIDTH-ExitButton.get_frame_width()-30,SCREEN_HEIGHT-ExitButton.get_frame_height()-30);
             ExitButton.Render(g_screen);

             numberofcurrentscore.Set_Text(number_to_string(current_score));
             numberofcurrentscore.LoadFromRenderText(paused_font,g_screen);
             numberofcurrentscore.RenderText(g_screen,SCREEN_WIDTH/2-50,SCREEN_HEIGHT/2-15);

             Wave.Set_Text(number_to_string(wave));
             Wave.LoadFromRenderText(paused_font,g_screen);
             Wave.RenderText(g_screen,SCREEN_WIDTH/2-50,SCREEN_HEIGHT/2-15+120);

             Rating.Set_Text(RatingBaseOnScore(current_score));
             Rating.LoadFromRenderText(paused_font,g_screen);
             Rating.RenderText(g_screen,SCREEN_WIDTH/2,SCREEN_HEIGHT/2-15+230);

             SDL_RenderPresent(g_screen);
        }
    }
    close();
    return 0;
}
