#include "Bullet.h"


Bullet::Bullet( SDL_Renderer* renderTarget )
{
	this->renderTarget = renderTarget;
}


Bullet::~Bullet()
{

}

void Bullet::update( float deltaTime )
{

}

Bullet* Bullet::clone()
{
	return new Bullet( renderTarget );
}