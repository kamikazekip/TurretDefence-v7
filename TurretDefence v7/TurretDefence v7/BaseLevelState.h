#pragma once

#include "LoopHandler.h"
#include "Sprite.h"
#include "HUD.h"
#include "Wave.h"
#include "WaveFactory.h"
#include "LevelBehaviour.h"

class LevelBehaviourFactory;
class Game;

enum LevelConditions
{
	LevelCondition_Init,
	LevelCondition_Start,
	LevelCondition_End
};

class BaseLevelState : public LoopHandler
{
protected:
	/* Variables */
	LevelBehaviour* currentBehaviour;
	LevelBehaviourFactory* behaviourFactory;
	Game* game;
	Sprite* background;
	HUD* hud;
	Wave* currentWave;
	WaveFactory* waveFactory;
	int waveCounter;

	std::vector<SDL_Point> path;

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
	virtual void setPath( std::vector<SDL_Point> path );
	virtual void changeState( LevelConditions newCondition );
	virtual Wave* getWave();
};

