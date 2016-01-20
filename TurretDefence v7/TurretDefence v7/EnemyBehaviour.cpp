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
	std::cout << "Done" << std::endl;
}

void EnemyBehaviour::move()
{

}

EnemyBehaviour* EnemyBehaviour::clone()
{
	return new EnemyBehaviour( enemy );
}