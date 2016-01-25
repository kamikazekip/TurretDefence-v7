#include "SniperTurret.h"

SniperTurret::SniperTurret( SDL_Renderer* renderTarget, double x, double y, double range, float attackSpeed, int width, int height )
	: Turret( renderTarget, Asset_Turret_Sniper_Calm, Asset_Turret_Sniper_Angry, x, y, range, attackSpeed, width, height )
{
	rotationCenter = SDL_Point{ w / 2, h * 0.5868263473053892 };
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