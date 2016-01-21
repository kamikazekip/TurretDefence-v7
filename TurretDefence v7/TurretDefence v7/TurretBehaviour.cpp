#include "TurretBehaviour.h"


TurretBehaviour::TurretBehaviour(Turret* turret)
{
	this->turret = turret;
}


TurretBehaviour::~TurretBehaviour()
{

}

void TurretBehaviour::setup()
{
	
}

void TurretBehaviour::checkState()
{

}

void TurretBehaviour::update( float deltaTime )
{

}

void TurretBehaviour::move()
{

}

TurretBehaviour* TurretBehaviour::clone() 
{
	return new TurretBehaviour( turret );
}