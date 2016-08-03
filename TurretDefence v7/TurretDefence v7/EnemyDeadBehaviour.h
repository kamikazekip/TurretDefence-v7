#pragma once
#include "EnemyBehaviour.h"
#include "Enemy.h"

class EnemyDeadBehaviour : public EnemyBehaviour
{
public:
	EnemyDeadBehaviour( Enemy* enemy );
	~EnemyDeadBehaviour();

	void setup();
	void checkState();
	void update( float deltaTime );
	EnemyBehaviour* clone();
};

