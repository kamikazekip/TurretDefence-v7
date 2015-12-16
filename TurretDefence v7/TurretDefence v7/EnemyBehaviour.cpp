#include "EnemyBehaviour.h"


EnemyBehaviour::EnemyBehaviour(Enemy* enemy)
{
	this->enemy = enemy;
}


EnemyBehaviour::~EnemyBehaviour()
{

}

void EnemyBehaviour::checkState()
{

}

void EnemyBehaviour::update( float deltaTime )
{

}

void EnemyBehaviour::move()
{

}

EnemyBehaviour* EnemyBehaviour::clone()
{
	return new EnemyBehaviour( enemy );
}