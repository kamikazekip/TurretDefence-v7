#pragma once
#include "Vector.h"

class Bullet
{
protected:
	SDL_Renderer* renderTarget;
	Vector direction;
public:
	Bullet( SDL_Renderer* renderTarget );
	~Bullet();

	virtual void update( float deltaTime );
	virtual Bullet* clone();
};

