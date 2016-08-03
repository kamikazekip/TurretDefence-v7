#include "SniperTurret.h"

SniperTurret::SniperTurret( double x, double y, double range, float attackSpeed, float scale )
	: Turret( ImageAsset_Turret_Sniper_Base_Calm, ImageAsset_Turret_Sniper_Base_Angry, ImageAsset_Turret_Sniper_Barrel_Calm, ImageAsset_Turret_Sniper_Barrel_Angry, x, y, range, attackSpeed, scale )
{
	//rotationCenter = SDL_Point{ w / 2, h * 0.5868263473053892 };
	rotationCenter = SDL_Point{ w / 2, h / 2 };
	radius = w / 2;
}

SniperTurret::~SniperTurret()
{
	std::cout << "HALLO" << std::endl;
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