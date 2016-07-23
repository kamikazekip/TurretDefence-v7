#include "CollisionManager.h"
#include <cmath>


CollisionManager::CollisionManager()
{
	quadTree = new QuadTree( 0, 0, 0, WindowController::getInstance()->width, WindowController::getInstance()->height );
	shouldDraw = false;
}


CollisionManager::~CollisionManager()
{
	delete quadTree;	 quadTree = nullptr;
}

void CollisionManager::clear()
{
	quadTree->clear();
}

void CollisionManager::insert( GameObject* object )
{
	quadTree->insert( object );
}

std::vector<GameObject*> CollisionManager::retrieve( GameObject* object )
{
	return retrieve( object->x, object->y, object->w, object->h );
}

std::vector<GameObject*> CollisionManager::retrieve( double objectX, double objectY, double objectW, double objectH )
{
	return quadTree->retrieve( objectX, objectY, objectW, objectH );
}

std::vector<Enemy*> CollisionManager::retrieveEnemies( double objectX, double objectY, double objectW, double objectH )
{
	std::vector<Enemy*> enemies;
	for( GameObject* object : retrieve( objectX, objectY, objectW, objectH ))
	{
		if( Enemy* moveable_enemy = dynamic_cast< Enemy* >( object ) )
			enemies.push_back( moveable_enemy );
	}
	return enemies;
}

std::vector<Enemy*> CollisionManager::enemiesInRange( double x, double y, double range )
{
	double objectX = x - range;
	double objectY = y - range;
	double objectW = range * 2;
	double objectH = range * 2;
	std::vector<Enemy*> enemies = retrieveEnemies( objectX, objectY, objectW, objectH );
	std::vector<Enemy*> enemiesInRange;
	for( Enemy* enemy : enemies )
	{
		if( calculateDistance(x, y, enemy->getOriginX(), enemy->getOriginY()) <= range )
			enemiesInRange.push_back( enemy );
	}
	return enemiesInRange;
}

void CollisionManager::draw()
{
	if( shouldDraw )
		quadTree->draw();
}

double CollisionManager::calculateDistance( double x1, double y1, double x2, double y2 )
{
	double diffX = x1 - x2;
	double diffY = y1 - y2;
	return sqrt( ( diffX * diffX ) + ( diffY * diffY ) );
}
