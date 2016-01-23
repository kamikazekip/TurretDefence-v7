#include "SoldierTurret.h"


SoldierTurret::SoldierTurret( SDL_Renderer* renderTarget, double x, double y )
	: Turret( renderTarget, Asset_Turret_Soldier_Calm, Asset_Turret_Soldier_Angry, 1.00f, 250, x, y, 100, 100 )
{

}


SoldierTurret::~SoldierTurret()
{
}
                                                                                                                                   