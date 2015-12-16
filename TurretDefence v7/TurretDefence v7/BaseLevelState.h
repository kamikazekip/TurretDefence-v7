#pragma once

#include "LoopHandler.h"
#include "Sprite.h"
#include "HUD.h"
#include "Wave.h"
#include "WaveFactory.h"

class Game;

class BaseLevelState : public LoopHandler
{
protected:
	/* Variables */
	Game* game;
	Sprite* background;
	HUD* hud;
	Wave* currentWave;
	WaveFactory* waveFactory;
	int waveCounter;

	/* Functions */
	virtual void update( float deltaTime );
	virtual void animate( float deltaTime );
	virtual void draw();
	virtual void changeLevel();

	/* Events */
	virtual void onQuit();
	virtual void onMouseButtonDown( int mouseX, int mouseY );
	virtual void onMouseMotion( int mouseX, int mouseY );
public:
	BaseLevelState( Game* game, Camera* camera );
	~BaseLevelState();

	virtual void tick( float deltaTime );
};

