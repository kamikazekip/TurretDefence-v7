#pragma once
#include "Sprite.h"
#include "EnemyBehaviour.h"
#include "EnemyBehaviourFactory.h"

class Enemy
{
private:
	int takenDamage;
	Sprite* sprite;
	EnemyConditions currentCondition;
	EnemyBehaviour* behaviour;
	EnemyBehaviourFactory* behaviourFactory;
public:
	Enemy( SDL_Renderer* renderTarget, Asset asset, int maxHealth, int movementSpeed );
	~Enemy();

	virtual void changeState( EnemyConditions condition );
	virtual void takeDamage( int damage );

	virtual void update( float deltaTime );
	virtual void animate( float deltaTime );
	virtual void draw();

	int health;
	int maxHealth;
	float movementSpeed;

};

