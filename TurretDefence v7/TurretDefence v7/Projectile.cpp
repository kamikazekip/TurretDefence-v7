#include "Projectile.h"

Projectile::Projectile( double objectX, double objectY, double objectW, double objectH, Vector direction, double speed, double damage, float rotation, SDL_Texture* image,  SDL_Texture* muzzleFlashImage )
	: GameObject(objectX, objectY, objectW, objectH)
{
	this->x -= w / 2;
	this->y -= h / 2;
	this->direction				= direction;
	this->speed					= speed;
	this->damage				= damage;
	this->rotation				= rotation;
	this->image					= image;
	this->muzzleFlashImage		= muzzleFlashImage;
	this->shouldDrawMuzzleFlash = true;

	int muzzleFlashW;
	int muzzleFlashH;
	SDL_QueryTexture( muzzleFlashImage, NULL, NULL, &muzzleFlashW, &muzzleFlashH );
	this->flashW = muzzleFlashW;
	this->flashH = muzzleFlashH;

	this->flashX = objectX - (flashW / 2);
	this->flashX += ( flashW / 2 ) * direction.x;

	this->flashY = objectY - (flashH / 2);
	this->flashY += (flashH / 2) * direction.y;
}

/* Ammo prototype constructor */
Projectile::Projectile( double w, double h, double speed, double damage, SDL_Texture* image )
	: GameObject( w, h )
{
	this->speed					= speed;
	this->damage				= damage;
	this->image					= image;
}

Projectile::~Projectile()
{

}

void Projectile::update( float deltaTime )
{
	x += direction.x * speed * deltaTime;
	y += direction.y * speed * deltaTime;
}

void Projectile::draw( Camera* camera )
{
	if( shouldDrawMuzzleFlash )
	{
		SDL_Rect drawingRect = { flashX, flashY, flashW, flashH };
		SDL_RenderCopyEx( renderTarget, muzzleFlashImage, NULL, &drawingRect, rotation, NULL, SDL_FLIP_NONE );
		shouldDrawMuzzleFlash = false;
	}
	else
	{
		SDL_Rect drawingRect = getDrawingRect( camera );
		SDL_RenderCopyEx( renderTarget, image, NULL, &drawingRect, rotation, NULL, SDL_FLIP_NONE );
	}
}

Projectile* Projectile::clone( double x, double y, Vector direction, float rotation, SDL_Texture* muzzleFlashImage )
{
	return new Projectile( x, y, w, h, direction, speed, damage, rotation, image, muzzleFlashImage );
}
