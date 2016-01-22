#pragma once
#include "Turret.h"

class SniperTurret : public Turret
{
protected:
	int radius;
public:
	SniperTurret();
	~SniperTurret();
	bool isTouching( int xPosition, int yPosition );
	Turret* clone(double x, double y);
};

