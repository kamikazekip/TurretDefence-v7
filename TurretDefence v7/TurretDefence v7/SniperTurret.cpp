#include "SniperTurret.h"

SniperTurret::SniperTurret( SDL_Renderer* renderTarget, double x, double y )
	: Turret( renderTarget, Asset_Turret_Sniper_Calm, Asset_Turret_Sniper_Angry, 1.00f, 350, x, y, 137, 167 )
{
	rotationCenter = SDL_Point{ w / 2, 98 };
	radius = w / 2;
}

SniperTurret::~SniperTurret()
{

}

bool SniperTurret::isTouching( int xPosition, int yPosition )
{
	double centerX = x + rotationCenter.x;
	double centerY = y + rotationCenter.y;
	int distancex = ( centerX - xPosition ) * ( centerX - xPosition );
	int distancey = ( centerY - yPosition ) * ( centerY - yPosition );
	double distance = sqrt( distancex + distancey );
	return ( distance <= radius );
}