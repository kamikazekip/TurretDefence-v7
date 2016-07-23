#pragma once
#include "QuadTree.h"
#include "WindowController.h"
#include "Enemy.h"

class CollisionManager
{
private:
	QuadTree* quadTree;
	double calculateDistance( double x1, double y1, double x2, double y2 );
	bool shouldDraw;
public:
	CollisionManager();
	~CollisionManager();

	void clear();
	void insert( GameObject* object );
	std::vector<GameObject*> retrieve( GameObject* object );
	std::vector<GameObject*> retrieve( double x, double y, double w, double h );

	/* Convenience */
	std::vector<Enemy*> retrieveEnemies( double x, double y, double w, double h );
	std::vector<Enemy*> enemiesInRange( double x, double y, double range );

	void draw();
};

