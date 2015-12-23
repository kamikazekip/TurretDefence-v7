#pragma once
#include <iostream>

enum EnemyConditions
{
	EnemyCondition_Spawned,
	EnemyCondition_Health_Depleted,
	EnemyCondition_Reached_Last_Waypoint,
};

class Enemy;

class EnemyBehaviour
{
protected:
	Enemy* enemy;
public:
	EnemyBehaviour(Enemy* enemy);
	~EnemyBehaviour();
	virtual void checkState();
	virtual void update( float deltaTime );
	virtual void move();
	virtual EnemyBehaviour* clone();
};

