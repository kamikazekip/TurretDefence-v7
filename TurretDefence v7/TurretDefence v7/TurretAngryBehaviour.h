#pragma once
#include "TurretBehaviour.h"

class TurretAngryBehaviour : public TurretBehaviour
{
public:
	TurretAngryBehaviour(Turret* turret);
	~TurretAngryBehaviour();

	void setup();
	void checkState();
	void update( float deltaTime );
	void move();

	TurretBehaviour* clone();
};

