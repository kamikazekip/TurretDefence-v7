#pragma once
#include "Turret.h"

class TurretBehaviour
{
protected:
	Turret* turret;
public:
	TurretBehaviour( Turret* turret );
	~TurretBehaviour();
	virtual void setup();
	virtual void checkState();
	virtual void update( float deltaTime );
	virtual void move();
	
	virtual TurretBehaviour* clone( );
};

