#pragma once
#include <iostream>
class Enemy;

class EnemyBehaviour
{
protected:
	Enemy* enemy;
public:
	EnemyBehaviour(Enemy* enemy);
	~EnemyBehaviour();
	virtual void setup();
	virtual void checkState();
	virtual void update( float deltaTime );
	virtual void move();
	virtual EnemyBehaviour* clone();
};

