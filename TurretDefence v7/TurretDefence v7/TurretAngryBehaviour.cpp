#include "TurretAngryBehaviour.h"
#include "global.h"


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
	if( turret->target == nullptr )
		turret->changeState( TurretCondition_Enemy_Out_Of_Range );
}

void TurretAngryBehaviour::update( float deltaTime )
{
	double newAngle = fmod( 450 + RADTODEG * atan2( ( turret->target->getOriginY() - turret->getOriginY() ), ( turret->target->getOriginX() - turret->getOriginX() ) ), 360 );
	if( deltaTime * turret->rotationSpeed < abs( newAngle - turret->rotation ) )
	{
		if( fmod( turret->rotation - newAngle + 360, 360 ) > 180 )
		{
			turret->rotation += deltaTime * turret->rotationSpeed;
			if( turret->rotation > 360 )
				turret->rotation = 0;
		}
		else
		{
			turret->rotation -= deltaTime * turret->rotationSpeed;
			if( turret->rotation < 0 )
				turret->rotation = 360;
		}
	}
	else
		turret->rotation = newAngle;
	turret->pullTrigger();
}

void TurretAngryBehaviour::move()
{

}

TurretBehaviour* TurretAngryBehaviour::clone()
{
	return new TurretAngryBehaviour( turret );
}