#pragma once
#include "Turret.h"

class SoldierTurret : public Turret
{
public:
	SoldierTurret( double x, double y, double range, float attackSpeed, float scale);
	~SoldierTurret();
};

