#pragma once
#include "Turret.h"

class SoldierTurret : public Turret
{
public:
	SoldierTurret( SDL_Renderer* renderTarget, double x, double y, double range, float attackSpeed, int width, int height );
	~SoldierTurret();
};

