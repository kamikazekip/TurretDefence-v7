#pragma once

#include "LoopHandler.h"
#include "Sprite.h"
#include "Wave.h"
#include "WaveFactory.h"
#include "LevelBehaviour.h"
#include "Turret.h"
#include "TurretContainer.h"

class LevelBehaviourFactory;
class TurretFactory;
class Game;
class HUD;

enum LevelConditions
{
	LevelCondition_Init,
	LevelCondition_Start_Wave,
	LevelCondition_End_Wave
};

class BaseLevelState : public LoopHandler
{
protected:
	/* Variables */
	LevelBehaviour* currentBehaviour;
	LevelBehaviourFactory* behaviourFactory;
	Game* game;
	Sprite* background;
	Sprite* pausedScreen;
	HUD* hud;
	Wave* currentWave;
	WaveFactory* waveFactory;
	TurretFactory* turretFactory;
	int waveCounter;

	std::vector<SDL_Point> path;
	TurretContainer* turrets;

	/* Functions */
	virtual void update( float deltaTime );
	virtual void animate( float deltaTime );
	virtual void draw();
	virtual void changeLevel();

	/* Events */
	virtual void onQuit();
	virtual void onMouseButtonDown( int mouseX, int mouseY );
	virtual void onMouseMotion( int mouseX, int mouseY );
	virtual void onEscapeKeyDown();
public:
	BaseLevelState( Game* game, Camera* camera );
	~BaseLevelState();

	virtual void tick( float deltaTime );
	virtual void setPath( std::vector<SDL_Point> path );
	virtual void changeState( LevelConditions newCondition );
	virtual Wave* getWave();
	virtual void nextWave();
};

