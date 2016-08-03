#include "CollisionManager.h"
#include <cmath>
#include "Enemy.h"
#include "Projectile.h"
#include "Turret.h"

static CollisionManager* instance;

CollisionManager::CollisionManager()
{
	quadTree = new QuadTree( 0, 0, 0, WindowController::getInstance()->width, WindowController::getInstance()->height );
	shouldDraw = false;
}


CollisionManager::~CollisionManager()
{
	delete quadTree;	 quadTree = nullptr;
}

/* Singleton */
CollisionManager* CollisionManager::getInstance()
{
	if( !instance )
		instance = new CollisionManager();
	return instance;
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
		if( Enemy* moveable_enemy = dynamic_cast< Enemy* >( object ) )
			enemies.push_back( moveable_enemy );
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
		if( calculateDistance(x, y, enemy->getOriginX(), enemy->getOriginY()) <= range )
			enemiesInRange.push_back( enemy );
	return enemiesInRange;
}

std::vector<Projectile*> CollisionManager::retrieveProjectiles( double objectX, double objectY, double objectW, double objectH )
{
	std::vector<Projectile*> enemies;
	for( GameObject* object : retrieve( objectX, objectY, objectW, objectH ) )
		if( Projectile* moveable_projectile = dynamic_cast< Projectile* >( object ) )
			enemies.push_back( moveable_projectile );
	return enemies;
}

std::vector<Projectile*> CollisionManager::projectilesInContact( double x, double y, double w, double h )
{
	std::vector<Projectile*> projectiles = retrieveProjectiles( x, y, w, h );
	std::vector<Projectile*> projectilesInContact;
	for( Projectile* projectile : projectiles )
		if( projectile->overlaps(x, y, w, h ) && !projectile->trash )
			projectilesInContact.push_back( projectile );
	return projectilesInContact;
}

std::vector<Turret*> CollisionManager::retrieveTurrets( double objectX, double objectY, double objectW, double objectH )
{
	std::vector<Turret*> turrets;
	for( GameObject* object : retrieve( objectX, objectY, objectW, objectH ) )
		if( Turret* moveable_turret = dynamic_cast< Turret* >( object ) )
			turrets.push_back( moveable_turret );
	return turrets;
}

std::vector<Turret*> CollisionManager::turretsInRange( double x, double y, double range )
{
	double objectX = x - range;
	double objectY = y - range;
	double objectW = range * 2;
	double objectH = range * 2;
	std::vector<Turret*> turrets = retrieveTurrets( objectX, objectY, objectW, objectH );
	std::vector<Turret*> turretsInRange;
	for( Turret* turret : turrets )
		if( calculateDistance( x, y, turret->getOriginX(), turret->getOriginY() ) <= range )
			turretsInRange.push_back( turret );
	return turretsInRange;
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

extern __declspec( dllexport ) void CollisionManager_Quit()
{
	delete instance; instance = nullptr;
}