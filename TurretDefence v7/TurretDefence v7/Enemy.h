#pragma once
#include "Sprite.h"
#include "EnemyBehaviour.h"
#include "EnemyBehaviourFactory.h"

class Enemy
{
protected:
	int takenDamage;
	SDL_Rect position;
	SDL_Texture* image;
	EnemyConditions currentCondition;
	EnemyBehaviour* behaviour;
	EnemyBehaviourFactory* behaviourFactory;
public:
	Enemy( SDL_Texture* image, int maxHealth, int speed, int width, int height );
	~Enemy();

	virtual void changeState( EnemyConditions condition );
	virtual void takeDamage( int damage );

	virtual void update( float deltaTime );
	virtual void animate( float deltaTime );
	virtual void draw();

	virtual Enemy* clone( int spawnTimeMS );

	int health;
	int maxHealth;
	int speed;
	int spawnTimeMS;
};

