#include "Turret.h"


Turret::Turret( SDL_Renderer* renderTarget, float attackSpeed, double range, double width, double height )
{
	projectileLoaded = true;
	pastTime = 0.00f;
	spread = 0.00f;
	setProperties( renderTarget, attackSpeed, range, width, height );
}

Turret::Turret()
{

}


Turret::~Turret()
{

}

void Turret::setProperties( SDL_Renderer* renderTarget, float attackSpeed, double range, double width, double height )
{
	this->renderTarget = renderTarget;
	this->attackSpeed = attackSpeed;
	this->range = range;
	this->w = width;
	this->h = height;
	image_range_correct = Assets::getInstance()->getAsset( Asset_Range_Correct );
	image_range_incorrect = Assets::getInstance()->getAsset( Asset_Range_Incorrect );
}

void Turret::setImages( Asset calm, Asset angry )
{
	image_calm					= Assets::getInstance()->getAsset( calm );
	image_angry					= Assets::getInstance()->getAsset( angry );
	image_current = image_calm;
}

void Turret::update( float deltaTime )
{
	pastTime += deltaTime;

	if( pastTime >= 1.00f / attackSpeed )
		projectileLoaded = true;
}

void Turret::draw( Camera* camera )
{
	SDL_Rect drawingRect = { x - camera->x - w / 2, y - camera->y - h / 2, w, h };
	SDL_RenderCopyEx( renderTarget, image_current, NULL, &drawingRect, 30, NULL, SDL_FLIP_NONE );
	SDL_Rect rangeDrawingRect = {drawingRect.x + w / 2 - range, drawingRect.y + h / 2 - range, range * 2, range * 2 };
	SDL_RenderCopy( renderTarget, image_range_correct, NULL, &rangeDrawingRect );
}

Turret* Turret::clone( double x, double y )
{	
	Turret* newTurret = new Turret( renderTarget, attackSpeed, range, w, h );
	this->x = x;
	this->y = y;
	newTurret->x = this->x;
	newTurret->y = this->y;
	newTurret->image_calm = image_calm;
	newTurret->image_angry = image_angry;
	newTurret->image_current = image_current;
	return newTurret;
}

void Turret::pullTrigger()
{
	if( projectileLoaded )
	{
		fire();
		pastTime = 0.00f;
		projectileLoaded = false;
	}
}

void Turret::fire()
{
	std::cout << "Pew pew!" << std::endl;
}