#include "TurretContainer.h"


TurretContainer::TurretContainer( SDL_Renderer* renderTarget, Camera* camera )
{
	this->renderTarget = renderTarget;
	this->camera = camera;
	turretFactory = new TurretFactory( renderTarget );
}


TurretContainer::~TurretContainer()
{
}

void TurretContainer::update( float deltaTime )
{
	for( size_t c = 0; c < turrets.size(); c++ )
	{
		turrets[c]->update( deltaTime );
	}
}

void TurretContainer::animate( float deltaTime )
{
	for( size_t c = 0; c < turrets.size(); c++ )
	{
		turrets[c]->animate( deltaTime );
	}
}

void TurretContainer::draw()
{
	for( size_t c = 0; c < turrets.size(); c++ )
	{
		turrets[c]->draw( camera );
	}
}

void TurretContainer::addTurret( TurretType turret, double x, double y )
{
	turrets.push_back( turretFactory->createTurret( turret, x, y ) );
}

void TurretContainer::onMouseButtonDown( int mouseX, int mouseY )
{
	for( size_t c = 0; c < turrets.size(); c++ )
	{
		if( turrets[c]->isTouching( mouseX, mouseY ) )
		{
			turrets[c]->onClick();
		}
		else
		{
			turrets[c]->onMissClick();
		}	
	}
}