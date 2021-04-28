#include "Button.h"
using namespace std;
Button::Button()
{
	width_frame_=0;
    height_frame_=0;
}
Button::~Button()
{

}
bool Button::LoadTexture(string path, SDL_Renderer* screen)
{
    bool ret=Texture::LoadTexture(path,screen);
    if(ret==true)
    {
        width_frame_=rect_.w;
        height_frame_=rect_.h;
    }
    return ret;
}
bool Button::IsInside(SDL_Event event)
{
	if (event.type==SDL_MOUSEMOTION || event.type==SDL_MOUSEBUTTONDOWN || event.type==SDL_MOUSEBUTTONUP)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		bool inside=true;
		if (x<rect_.x)
		{
			inside=false;
		}
		else if (x>rect_.x+width_frame_)
		{
			inside=false;
		}
		else if (y<rect_.y)
		{
			inside=false;
		}
		else if (y>rect_.y+height_frame_)
		{
			inside=false;
		}
		return inside;
	}
	return 0;
}
void Button::HandlePlayButton(SDL_Event event,SDL_Renderer* screen,bool &menu,bool &play,bool &QuitMenu)
{
	if(IsInside(event))
	{
	    LoadTexture("img//PlayButton2.png",screen);
		if(event.type==SDL_MOUSEBUTTONDOWN)
		{
		    play=true;
		    QuitMenu=true;
			menu=false;
		}
	}
	else
	{
		LoadTexture("img//PlayButton.png",screen);
	}
}
void Button::HandleHelpButton(SDL_Event event,SDL_Renderer* screen,bool &menu,bool &help)
{
	if(IsInside(event))
	{
	    LoadTexture("img//HelpButton2.png",screen);
		if(event.type==SDL_MOUSEBUTTONDOWN)
		{
		    help=true;
            menu=false;
		}
	}
	else
	{
		LoadTexture("img//HelpButton.png",screen);
	}
}
void Button::HandleExitButton(SDL_Event event,SDL_Renderer* screen,bool &QuitMenu)
{
    if(IsInside(event))
	{
	    LoadTexture("img//ExitButton2.png",screen);
		if(event.type==SDL_MOUSEBUTTONDOWN)
		{
		    QuitMenu=!QuitMenu;
		}
	}
	else
	{
		LoadTexture("img//ExitButton.png",screen);
	}
}
void Button::HandleBackButton(SDL_Event event,SDL_Renderer* screen,bool &menu,bool &help)
{
    if(IsInside(event))
	{
	    LoadTexture("img//BackButton2.png",screen);
		if(event.type==SDL_MOUSEBUTTONDOWN)
		{
		    menu=true;
		    help=false;
		}
	}
	else
	{
		LoadTexture("img//BackButton.png",screen);
	}
}
void Button::HandleRestartButton(SDL_Event event,SDL_Renderer* screen,
                          vector<Enemy*>&Enemy_List,Character &spaceship,
                          vector<Bullet*> &Bullet_List,vector<Icon*>&Health_List,
                          int &wave,long &current_score,bool &GameOver)
{
    if (IsInside(event))
	{
	    LoadTexture("img//RestartButton2.png",screen);
		if(event.type==SDL_MOUSEBUTTONDOWN)
		{
		    GameOver=false;
            current_score=0;
            wave=0;
            Enemy_List.erase(Enemy_List.begin(),Enemy_List.begin()+Enemy_List.size());
            Bullet_List.erase(Bullet_List.begin(),Bullet_List.begin()+Bullet_List.size());
            Health_List.erase(Health_List.begin(),Health_List.begin()+Health_List.size());
            spaceship.Reset();
            SDL_WarpMouseInWindow(g_window,SCREEN_WIDTH/2-32,SCREEN_HEIGHT-100);
		}
	}
	else
	{
		LoadTexture("img//RestartButton.png",screen);
	}
}

