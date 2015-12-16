#include "Enemy.h"

Enemy::Enemy( SDL_Texture* image, int maxHealth, int speed, int width, int height )
{
	this->maxHealth = maxHealth;
	health = this->maxHealth;
	takenDamage = 0;
	this->speed = speed;
	this->position.w = width;
	this->position.h = height;
	this->image = image;
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

Enemy* Enemy::clone( int spawnTimeMS )
{
	Enemy* newEnemy = new Enemy( image, maxHealth, speed, position.w, position.h );
	newEnemy->spawnTimeMS = spawnTimeMS;
	return newEnemy;
}