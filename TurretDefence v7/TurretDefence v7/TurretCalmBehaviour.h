#pragma once
#include "TurretBehaviour.h"

class TurretCalmBehaviour : public TurretBehaviour
{
private:
	float pastTime;
	float triggerTime;
	float rotationTime;
	float rotateFor;
	float rotationToBeAdded;
public:
	TurretCalmBehaviour( Turret* turret );
	~TurretCalmBehaviour();
	
	void setup();
	void checkState();
	void update( float deltaTime );
	void move();

	TurretBehaviour* clone();
};

