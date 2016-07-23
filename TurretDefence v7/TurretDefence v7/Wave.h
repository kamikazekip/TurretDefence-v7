#pragma once
#include <vector>
#include "Enemy.h"

class Wave
{
private:
	std::vector<Enemy*>* enemies;
	std::vector<Enemy*>* unspawnedEnemies;
	std::vector<Enemy*>* enemyRemoveStack;
	float passedTime;

	void removeFinishedEnemies();
	void spawn( float deltaTime );
public:
	Wave();
	~Wave();
	virtual void update( float deltaTime );
	virtual void draw( Camera* camera );

	virtual void setEnemies( std::vector<Enemy*>* enemies );
	virtual std::vector<Enemy*>* getEnemies();
	bool finished;
};

