#pragma once
#include "EnemyBehaviour.h"

class EnemyMovingBehaviour : public EnemyBehaviour
{
public:
	EnemyMovingBehaviour(Enemy* enemy);
	~EnemyMovingBehaviour();
};
