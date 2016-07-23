#pragma once
#include "GameObject.h"
#include "Vector.h"
#include "Assets.h"

class Projectile : public GameObject
{
protected:
	Vector direction;
	double speed;
	double damage;
	float rotation;
	SDL_Texture* image;
	SDL_Texture* muzzleFlashImage;
	double flashX, flashY, flashW, flashH;
	bool shouldDrawMuzzleFlash;
	Projectile( double objectX, double objectY, double objectW, double objectH, Vector direction, double speed, double damage, float rotation, SDL_Texture* image, SDL_Texture* muzzleFlashImage );
public:
	/* Ammo prototype constructor */
	Projectile( double w, double h, double speed, double damage, SDL_Texture* image );
	~Projectile();

	void update( float deltaTime );
	void draw( Camera* camera );

	virtual Projectile* clone(double x, double y, Vector direction, float rotation, SDL_Texture* muzzleFlashImage);
};

