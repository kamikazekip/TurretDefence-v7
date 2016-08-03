#pragma once

#include "LoopHandler.h"
#include "Sprite.h"
#include "Wave.h"
#include "TurretFactory.h"
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
	TurretFactory* turretFactory;
	int waveCounter;

	std::vector<SDL_Point> path;

	/* Model */
	virtual void update( float deltaTime );
	virtual void collectGarbage();
	virtual void deleteGarbage();
	virtual void collide();
	virtual void changeLevel();

	/* View */
	virtual void animate( float deltaTime );
	virtual void draw();

	/* Events */
	virtual void onMouseButtonDown( int mouseX, int mouseY );
	virtual void onMouseMotion( int mouseX, int mouseY );
	virtual void onEscapeKeyDown();

	/* Destruction */
	virtual void shredVector(std::vector<GameObject*>* vector);
public:
	std::vector<GameObject*>*   gameObjects;
	std::vector<GameObject*>*	gameObjectsRemoveStack;
	std::vector<Enemy*>*		enemies;
	std::vector<Turret*>*		turrets;
	std::vector<Projectile*>*	projectiles;

	BaseLevelState( );
	~BaseLevelState();

	virtual void tick( float deltaTime );
	virtual std::vector<SDL_Point> getPath();
	virtual void setPath( std::vector<SDL_Point> path );
	virtual void changeState( LevelConditions newCondition );
	virtual Wave* getWave();
	virtual void nextWave();
	virtual void addProjectile( Projectile* projectile );
	virtual void addTurret( TurretType turretType, double x, double y );
	virtual void addEnemy( Enemy* enemy );
};

