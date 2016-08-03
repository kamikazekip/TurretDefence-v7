#pragma once
#include <vector>
#include "Enemy.h"

class BaseLevelState;

class Wave
{
private:
	BaseLevelState* level;
	std::vector<Enemy*>* unspawnedEnemies;
	float passedTime;
public:
	Wave( BaseLevelState* level );
	~Wave();
	virtual void update( float deltaTime );

	virtual void setEnemies( std::vector<Enemy*>* enemies );
	bool allEnemiesSpawn;
};

