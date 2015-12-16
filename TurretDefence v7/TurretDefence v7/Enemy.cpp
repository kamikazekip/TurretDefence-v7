#include "Enemy.h"

Enemy::Enemy( SDL_Renderer* renderTarget, Asset asset, int maxHealth, int movementSpeed )
{
	sprite				= new Sprite( renderTarget, asset );
	this->maxHealth		= maxHealth;
	this->health		= this->maxHealth;
	this->takenDamage	= 0;
	behaviourFactory	= new EnemyBehaviourFactory( this );
}

Enemy::~Enemy()
{

}

void Enemy::takeDamage( int damage )
{

}

void Enemy::changeState(EnemyConditions condition)
{
	currentCondition = condition;
	this->behaviour = behaviourFactory->createBehaviour( currentCondition );
}

void Enemy::update( float deltaTime )
{

}

void Enemy::animate( float deltaTime )
{

}

void Enemy::draw( )
{

}