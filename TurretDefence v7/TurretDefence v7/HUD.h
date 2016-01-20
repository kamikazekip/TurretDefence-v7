#pragma once
#include "HUDButton.h"
#include "PlayButton.h"
#include "PauseButton.h"
#include "BaseLevelState.h"
#include <vector>

class Game;

class HUD
{
private:
	std::vector<HUDButton*>* buttons;
	Game* game;
	BaseLevelState* level;
	int windowWidth, windowHeight;
	PlayButton* playButton;
	PauseButton* pauseButton;

	int rightMargin;
	
	void positionButtons();
public:
	HUD(Game* game, BaseLevelState* level, int windowWidth, int windowHeight);
	~HUD();

	void setWindowDimension( int windowWidth, int windowHeight );

	void onMouseButtonDown( int mouseX, int mouseY );
	void onMouseMotion( int mouseX, int mouseY );
	void animate( float deltaTime );
	void draw();
	void updateState( LevelConditions newCondition );
	bool isTouching( int mouseX, int mouseY );

	PlayButton* getPlayButton();
};

