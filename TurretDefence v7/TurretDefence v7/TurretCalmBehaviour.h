#pragma once
#include "TurretBehaviour.h"

class TurretCalmBehaviour : public TurretBehaviour
{
public:
	TurretCalmBehaviour( Turret* turret );
	~TurretCalmBehaviour();
	
	void setup();
	void checkState();
	void update( float deltaTime );
	void move();

	TurretBehaviour* clone();
};

