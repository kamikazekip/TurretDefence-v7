#pragma once
#include <vector>
#include "LoopHandler.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "Sprite.h"
#include "global.h"
#include "MenuItem.h"

class Game;

class Menu : public LoopHandler
{
protected:
	int windowWidth, windowHeight;
	std::vector<MenuItem*>* menuItems;
	Game* game;
	SDL_Renderer* renderTarget;
	Assets* assets;
	Sprite* version;

	/* Functions */
	virtual void addMenuItem( std::string text );
	virtual void centerMenuItems();
	virtual void drawMenuItems();
	virtual void checkHover(int mouseX, int mouseY);
public:
	Menu();
	~Menu();
	virtual void draw();
	void tick();
};

