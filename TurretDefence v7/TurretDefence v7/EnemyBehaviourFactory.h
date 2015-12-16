#pragma once
#include "EnemyBehaviour.h"
#include <map>

class Enemy;

class EnemyBehaviourFactory
{
private:
	Enemy* enemy;
	std::map<EnemyConditions, EnemyBehaviour*> behaviourMap;
	void linkCondition( EnemyConditions condition, EnemyBehaviour* enemyBehaviour );
public:
	EnemyBehaviourFactory(Enemy* enemy);
	~EnemyBehaviourFactory();

	EnemyBehaviour* createBehaviour( EnemyConditions condition );
};

