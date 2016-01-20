#pragma once
#include "Vector.h"
#include <iostream>
#include "Camera.h"
#include "Assets.h"

class Weapon;

class Turret
{
protected:
	SDL_Renderer* renderTarget;
	SDL_Texture* image_calm;
	SDL_Texture* image_angry;
	SDL_Texture* image_current;
	SDL_Texture* image_range_correct;
	SDL_Texture* image_range_incorrect;

	Weapon* weapon;
	bool projectileLoaded;
	float attackSpeed;
	float spread;
	float pastTime;

	virtual void setImages( Asset calm, Asset angry );
	virtual void pullTrigger();
	virtual void fire();
public:
	Turret( SDL_Renderer* renderTarget, float attackSpeed, double range, double width, double height );
	Turret();
	~Turret();
	virtual void setProperties( SDL_Renderer* renderTarget, float attackSpeed, double range, double width, double height );

	virtual void update( float deltaTime );
	virtual void draw( Camera* camera );
	virtual Turret* clone( double x, double y );

	Vector direction;
	double x, y, w, h;
	double range;
};

