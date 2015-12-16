#pragma once
#include "HUDButton.h"
#include "PlayButton.h"
#include <vector>
class BaseLevelState;
class Game;

class HUD
{
private:
	std::vector<HUDButton*>* buttons;
	Game* game;
	int windowWidth, windowHeight;
	PlayButton* playButton;
	HUDButton* pauseButton;

	int rightMargin;
	
	void positionButtons();
public:
	HUD(Game* game, int windowWidth, int windowHeight);
	~HUD();

	void setWindowDimension( int windowWidth, int windowHeight );

	void onMouseButtonDown( int mouseX, int mouseY );
	void onMouseMotion( int mouseX, int mouseY );
	void animate( float deltaTime );
	void draw();
};

