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
	if( enemy->reachedEnd )
	{
		enemy->changeState( EnemyConditions::EnemyCondition_Reached_Last_Waypoint );
	}
}

void EnemyMovingBehaviour::update( float deltaTime )
{
	int targetX = enemy->target.x;
	int targetY = enemy->target.y;

	float distanceX = ( targetX - enemy->x ) * ( targetX - enemy->x );
	float distanceY = ( targetY - enemy->y ) * ( targetY - enemy->y );
	double distanceBefore = sqrt( fabsf( distanceX - distanceY ) );

	float displacement = enemy->speed * deltaTime;

	double theoreticalX = enemy->x + displacement * enemy->direction.x;
	double theoreticalY = enemy->y + displacement * enemy->direction.y;

	if( distanceBefore < displacement )
	{
		double oldTheoreticalX = theoreticalX;
		double oldTheoreticalY = theoreticalY;

		SDL_Point oldWaypoint = enemy->target;
		double remainder = displacement - distanceBefore;

		theoreticalX = oldWaypoint.x;
		theoreticalY = oldWaypoint.y;
		enemy->x = theoreticalX;
		enemy->y = theoreticalY;

		enemy->nextWaypoint();

		SDL_Point newWaypoint = enemy->target;
		theoreticalX = enemy->x + remainder * enemy->direction.x;
		theoreticalY = enemy->y + remainder * enemy->direction.y;

		if( oldWaypoint.x == newWaypoint.x && oldWaypoint.y == newWaypoint.y )
		{
			theoreticalX = oldTheoreticalX;
			theoreticalY = oldTheoreticalY;
		}
	}

	enemy->x = theoreticalX;
	enemy->y = theoreticalY;
}


EnemyBehaviour* EnemyMovingBehaviour::clone()
{
	return new EnemyMovingBehaviour( enemy );
}
