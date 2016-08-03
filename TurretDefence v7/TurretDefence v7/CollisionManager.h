#pragma once
#include "QuadTree.h"
#include "WindowController.h"

class Enemy;
class Projectile;
class Turret;

class CollisionManager
{
private:
	QuadTree* quadTree;
	double calculateDistance( double x1, double y1, double x2, double y2 );
	bool shouldDraw;
	/* Singleton */
	CollisionManager();
	CollisionManager( CollisionManager const& );
public:
	~CollisionManager();
	/* Singleton */
	static CollisionManager* getInstance();

	void clear();
	void insert( GameObject* object );
	std::vector<GameObject*> retrieve( GameObject* object );
	std::vector<GameObject*> retrieve( double x, double y, double w, double h );

	/* Convenience */
	std::vector<Enemy*> retrieveEnemies( double x, double y, double w, double h );
	std::vector<Enemy*> enemiesInRange( double x, double y, double range );

	std::vector<Projectile*> retrieveProjectiles( double x, double y, double w, double h );
	std::vector<Projectile*> projectilesInContact( double x, double y, double w, double h );

	std::vector<Turret*> retrieveTurrets( double x, double y, double w, double h );
	std::vector<Turret*> turretsInRange( double x, double y, double range );

	void draw();
};

extern __declspec( dllexport ) void CollisionManager_Quit();