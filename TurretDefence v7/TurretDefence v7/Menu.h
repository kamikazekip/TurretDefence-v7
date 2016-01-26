#pragma once
#include <vector>
#include "LoopHandler.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "Game.h"
#include "Sprite.h"
#include "global.h"
#include "MenuItem.h"

class Menu : public LoopHandler
{
protected:
	std::vector<MenuItem*>* menuItems;
	SDL_Color menuFontColor;
	SDL_Color menuFontColorSelected;
	SDL_Renderer* renderTarget;
	Game* game;
	std::string action_jackson;
	std::string york;
	TTF_Font* versionFont;
	TTF_Font* menuItemFont;
	TTF_Font* titleFont;
	Sprite* version;

	/* Functions */
	virtual void addMenuItem( std::string text );
	virtual void centerMenuItems();
	virtual void drawMenuItems();
	virtual void checkHover(int mouseX, int mouseY);
public:
	Menu(Game* game);
	~Menu();
	virtual void draw();
	void tick();
};

