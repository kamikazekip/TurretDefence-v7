#include "EnemyDeadBehaviour.h"



EnemyDeadBehaviour::EnemyDeadBehaviour( Enemy* enemy )
	: EnemyBehaviour( enemy )
{
}


EnemyDeadBehaviour::~EnemyDeadBehaviour()
{
}

void EnemyDeadBehaviour::setup()
{
	enemy->trash = true;
}

void EnemyDeadBehaviour::checkState()
{

}

void EnemyDeadBehaviour::update( float deltaTime )
{

}

EnemyBehaviour* EnemyDeadBehaviour::clone()
{
	return new EnemyDeadBehaviour( enemy );
}