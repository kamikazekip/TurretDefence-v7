#include "TurretContainer.h"


TurretContainer::TurretContainer( BaseLevelState* level, Camera* camera )
{
	this->level = level;
	this->camera = camera;
	turretFactory = new TurretFactory( );
}


TurretContainer::~TurretContainer()
{

}

void TurretContainer::update( float deltaTime )
{
	for( Turret* turret : turrets )
		turret->update( deltaTime );
}

void TurretContainer::animate( float deltaTime )
{
	for( Turret* turret : turrets )
		turret->animate( deltaTime );
}

void TurretContainer::draw()
{
	for( Turret* turret : turrets )
		turret->draw( camera );
}

void TurretContainer::addTurret( TurretType turretType, double x, double y )
{
	Turret* turret = turretFactory->createTurret( turretType, x, y );
	turret->setLevel( level );
	turrets.push_back( turret );
}

void TurretContainer::onMouseButtonDown( int mouseX, int mouseY )
{
	for( Turret* turret : turrets )
	{
		if( turret->isTouching( mouseX, mouseY ) )
			turret->onClick();
		else
			turret->onMissClick();
	}
}