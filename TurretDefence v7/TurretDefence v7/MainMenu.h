#pragma once
#include "Menu.h"

class MainMenu : public Menu
{
private:
	TTF_Font* mainTitleFont;
	Sprite* mainTitle;
	enum Choice { Play, Options, Exit };
public:
	MainMenu(SDL_Renderer* renderTarget, Game* game, Camera* camera );
	~MainMenu();
	void firstTick();
	void tick( float deltaTime );
	void draw();
	void onQuit();
	void onMouseMotion( int mouseX, int mouseY );
	void onMouseButtonDown( int mouseX, int mouseY );
	void handleChoice( Choice choice );
};