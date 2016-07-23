#pragma once
#include "Turret.h"

class SniperTurret : public Turret
{
protected:
	int radius;
public:
	SniperTurret( double x, double y, double range, float attackSpeed, float scale );
	~SniperTurret();
	bool isTouching( int xPosition, int yPosition );
};

