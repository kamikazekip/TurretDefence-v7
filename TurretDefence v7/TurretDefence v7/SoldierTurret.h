#pragma once
#include "Turret.h"

class SoldierTurret : public Turret
{
public:
	SoldierTurret( SDL_Renderer* renderTarget, double x, double y );
	~SoldierTurret();
};

