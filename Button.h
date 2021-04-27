#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include "Texture.h"
#include "Game_Utils.h"
using namespace std;

class Button : public Texture
{
public:
	Button();
	~Button();
	virtual bool LoadTexture(string path,SDL_Renderer* screen);
    int get_frame_width() const {return width_frame_;}
    int get_frame_height() const {return height_frame_;}
	bool IsInside(SDL_Event event);
	void HandlePlayButton(SDL_Event event,SDL_Renderer* screen,bool &menu,bool &play,bool &QuitMenu);
	void HandleHelpButton(SDL_Event event,SDL_Renderer* screen,bool &menu,bool &help);
	void HandleExitButton(SDL_Event event,SDL_Renderer* screen,bool &QuitMenu);
private:
    int width_frame_;
    int height_frame_;
};

#endif // BUTTON_H_INCLUDED
