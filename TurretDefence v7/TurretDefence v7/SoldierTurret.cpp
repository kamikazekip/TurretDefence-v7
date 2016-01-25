#include "SoldierTurret.h"


SoldierTurret::SoldierTurret( SDL_Renderer* renderTarget, double x, double y, double range, float attackSpeed, int width, int height )
	: Turret( renderTarget, Asset_Turret_Soldier_Calm, Asset_Turret_Soldier_Angry, x, y, range, attackSpeed, width, height )
{

}


SoldierTurret::~SoldierTurret()
{
}
                                                                                                                                   