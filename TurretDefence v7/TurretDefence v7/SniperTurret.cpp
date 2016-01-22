#include "SniperTurret.h"

SniperTurret::SniperTurret()
	: Turret( Asset_Turret_Sniper_Calm, Asset_Turret_Sniper_Angry )
{
	rotationCenter = SDL_Point{ 67, 98 };
}

SniperTurret::~SniperTurret()
{

}

bool SniperTurret::isTouching( int xPosition, int yPosition )
{
	return true;
}

void SniperTurret::clone( double x, double y )
{
	this->x = x;
	this->y = y;
	Turret* newTurret = new Turret( renderTarget, attackSpeed, range, w, h );
	transferOrgans( this, newTurret );
	return newTurret;
}
