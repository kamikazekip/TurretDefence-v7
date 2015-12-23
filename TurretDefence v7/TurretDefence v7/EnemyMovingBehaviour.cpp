#include "EnemyMovingBehaviour.h"
#include "Enemy.h"

EnemyMovingBehaviour::EnemyMovingBehaviour(Enemy* enemy)
	: EnemyBehaviour( enemy )
{

}


EnemyMovingBehaviour::~EnemyMovingBehaviour()
{

}

void EnemyMovingBehaviour::checkState()
{

}

void EnemyMovingBehaviour::update( float deltaTime )
{
	int targetX = enemy->target.x;
	int targetY = enemy->target.y;

	
	float distancex = ( targetX - enemy->x ) * ( targetX - enemy->x );
	float distancey = ( targetY - enemy->y ) * ( targetY - enemy->y );
	double distanceBefore = sqrt( fabsf( distancex - distancey ) );

	float displacement = enemy->speed * deltaTime;
	enemy->x += displacement * enemy->direction.x;
	enemy->y += displacement * enemy->direction.y;

	float distancexAfter = ( targetX - enemy->x ) * ( targetX - enemy->x );
	float distanceyAfter = ( targetY - enemy->y ) * ( targetY - enemy->y );

	double distanceAfter = sqrt( fabsf( distancexAfter - distanceyAfter ) );

	if( distanceBefore < distanceAfter )
	{
		enemy->nextWaypoint();
	}
}


EnemyBehaviour* EnemyMovingBehaviour::clone()
{
	return new EnemyMovingBehaviour( enemy );
}
