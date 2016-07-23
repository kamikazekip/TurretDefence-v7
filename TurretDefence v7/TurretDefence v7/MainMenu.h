#pragma once
#include "Menu.h"
#include "OptionsMenu.h"

class MainMenu : public Menu
{
private:
	OptionsMenu* optionsMenu;
	Sprite* mainTitle;
	enum Choice { Play, Options, Exit };
public:
	MainMenu( );
	~MainMenu();
	void firstTick();
	void tick( float deltaTime );
	void draw();
	void onMouseMotion( int mouseX, int mouseY );
	void onMouseButtonDown( int mouseX, int mouseY );
	void handleChoice( Choice choice );
};