#include "TurretCalmBehaviour.h"
#include "Random.h"

TurretCalmBehaviour::TurretCalmBehaviour(Turret* turret)
	: TurretBehaviour( turret )
{
	pastTime = 8.00f;
	triggerTime = 6.00f;
	rotateFor = 2.00f;
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
	if( turret->target != nullptr )
		turret->changeState( TurretCondition_Enemy_In_Range );
}

void TurretCalmBehaviour::update( float deltaTime )
{
	pastTime += deltaTime;
	if( pastTime >= triggerTime )
	{
		pastTime = 0.00f;
		triggerTime = Random::getInstance().nextFloat( 4.00f, 6.00f );
		rotateFor = Random::getInstance().nextFloat( 0.30f, 0.60f );
		rotationToBeAdded = turret->rotationSpeed * deltaTime;
		if( Random::getInstance().nextBool() )
			rotationToBeAdded *= -1;
		rotationTime = 0.00f;
	}
	else
	{
		rotationTime += deltaTime;
		if( rotationTime < rotateFor )
			turret->rotation += rotationToBeAdded;
	}
}

void TurretCalmBehaviour::move()
{

}

TurretBehaviour* TurretCalmBehaviour::clone()
{
	return new TurretCalmBehaviour( turret );
}