#include "TurretCalmBehaviour.h"


TurretCalmBehaviour::TurretCalmBehaviour(Turret* turret)
	: TurretBehaviour( turret )
{

}

TurretCalmBehaviour::~TurretCalmBehaviour()
{

}

void TurretCalmBehaviour::setup()
{
	turret->setImage( TurretImage_Calm );
}

void TurretCalmBehaviour::checkState()
{

}

void TurretCalmBehaviour::update( float deltaTime )
{
	float rotationToBeAdded = turret->rotationSpeed * deltaTime;
	turret->rotation += rotationToBeAdded;
}

void TurretCalmBehaviour::move()
{

}

TurretBehaviour* TurretCalmBehaviour::clone()
{
	return new TurretCalmBehaviour( turret );
}