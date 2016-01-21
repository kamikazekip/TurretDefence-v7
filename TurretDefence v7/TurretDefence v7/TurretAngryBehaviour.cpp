#include "TurretAngryBehaviour.h"


TurretAngryBehaviour::TurretAngryBehaviour( Turret* turret )
	: TurretBehaviour( turret )
{

}

TurretAngryBehaviour::~TurretAngryBehaviour()
{

}

void TurretAngryBehaviour::setup()
{
	turret->setImage( TurretImage_Angry );
}

void TurretAngryBehaviour::checkState()
{

}

void TurretAngryBehaviour::update( float deltaTime )
{

}

void TurretAngryBehaviour::move()
{

}

TurretBehaviour* TurretAngryBehaviour::clone()
{
	return new TurretAngryBehaviour( turret );
}