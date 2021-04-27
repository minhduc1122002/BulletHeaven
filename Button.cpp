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
	if (IsInside(event))
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
	if (IsInside(event))
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
    if (IsInside(event))
	{
	    LoadTexture("img//ExitButton2.png",screen);
		if(event.type==SDL_MOUSEBUTTONDOWN)
		{
		    QuitMenu=true;
		}
	}
	else
	{
		LoadTexture("img//ExitButton.png",screen);
	}
}
