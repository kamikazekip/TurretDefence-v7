#include "SoldierTurret.h"


SoldierTurret::SoldierTurret( double x, double y, double range, float attackSpeed, float scale )
	: Turret( ImageAsset_Turret_Soldier_Calm, ImageAsset_Turret_Soldier_Angry, ImageAsset_HUD_PauseButton, ImageAsset_HUD_PauseButton, x, y, range, attackSpeed, scale )
{

}


SoldierTurret::~SoldierTurret()
{
}
                                                                                                                                   