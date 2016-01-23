#pragma once
#include "Turret.h"

class SniperTurret : public Turret
{
protected:
	int radius;
public:
	SniperTurret( SDL_Renderer* renderTarget, double x, double y );
	~SniperTurret();
	bool isTouching( int xPosition, int yPosition );
};

