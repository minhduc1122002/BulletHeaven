#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include "Texture.h"
#include "Game_Utils.h"
#include "Enemy.h"
#include "Icon.h"
#include "Character.h"
#include "Bullet.h"
using namespace std;

class Button : public Texture
{
public:
	Button();
	~Button();
	virtual bool LoadTexture(string path,SDL_Renderer* screen);
    int get_frame_width() const {return width_frame;}
    int get_frame_height() const {return height_frame;}
	bool IsInside(SDL_Event event);
	void HandlePlayButton(SDL_Event event,SDL_Renderer* screen,bool &menu,bool &play,bool &QuitMenu);
	void HandleHelpButton(SDL_Event event,SDL_Renderer* screen,bool &menu,bool &help);
	void HandleExitButton(SDL_Event event,SDL_Renderer* screen,bool &QuitMenu);
	void HandleBackButton(SDL_Event event,SDL_Renderer* screen,bool &menu,bool &help);
	void HandleRestartButton(SDL_Event event,SDL_Renderer* screen,
                          vector<Enemy*>&Enemy_List,Character &spaceship,
                          vector<Bullet*> &Bullet_List,vector<Icon*>&Health_List,
                          int &wave,long &current_score,bool &GameOver);

private:
    int width_frame;
    int height_frame;
};

#endif // BUTTON_H_INCLUDED
