#pragma once
#include <vector>
#include "Enemy.h"

class Wave
{
private:
	std::vector<Enemy*>* enemies;
	std::vector<Enemy*>* unspawnedEnemies;
	float passedTime;

	void spawn( float deltaTime );
public:
	Wave(std::vector<Enemy*>* enemies);
	~Wave();
	virtual void update( float deltaTime );
	virtual void draw( Camera* camera );
};

