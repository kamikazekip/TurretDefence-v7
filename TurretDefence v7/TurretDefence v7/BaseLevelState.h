#pragma once

#include "LoopHandler.h"
#include "Sprite.h"
#include "Wave.h"
#include "WaveFactory.h"
#include "LevelBehaviour.h"
#include "Turret.h"
#include "CollisionManager.h"
#include "Projectile.h"

class LevelBehaviourFactory;
class TurretContainer;
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
	CollisionManager* collisionManager;
	LevelBehaviour* currentBehaviour;
	LevelBehaviourFactory* behaviourFactory;
	Game* game;
	Sprite* background;
	HUD* hud;
	Wave* currentWave;
	WaveFactory* waveFactory;
	int waveCounter;

	std::vector<SDL_Point> path;
	std::vector<Enemy*>* enemies;
	TurretContainer* turrets;
	std::vector<Projectile*>* projectiles;

	/* Functions */
	virtual void update( float deltaTime );
	virtual void collide();
	virtual void animate( float deltaTime );
	virtual void draw();
	virtual void changeLevel();

	/* Events */
	virtual void onMouseButtonDown( int mouseX, int mouseY );
	virtual void onMouseMotion( int mouseX, int mouseY );
	virtual void onEscapeKeyDown();
public:
	BaseLevelState( );
	~BaseLevelState();

	virtual void tick( float deltaTime );
	virtual void setPath( std::vector<SDL_Point> path );
	virtual void changeState( LevelConditions newCondition );
	virtual Wave* getWave();
	virtual void nextWave();
	virtual void addProjectile( Projectile* projectile );
};

