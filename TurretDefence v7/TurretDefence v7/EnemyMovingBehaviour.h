#pragma once
#include "EnemyBehaviour.h"

class EnemyMovingBehaviour : public EnemyBehaviour
{
public:
	EnemyMovingBehaviour(Enemy* enemy);
	~EnemyMovingBehaviour();

	virtual void checkState();
	virtual void update( float deltaTime );
	virtual EnemyBehaviour* clone();
};

