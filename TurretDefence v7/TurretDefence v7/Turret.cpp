#include "Turret.h"
#include "TurretBehaviourFactory.h"


Turret::Turret( SDL_Renderer* renderTarget, float attackSpeed, double range, double width, double height )
{
	projectileLoaded = true;
	pastTime = 0.00f;
	spread = 0.00f;
	rotation = 180.0f;
	rotationSpeed = 10.0f;
	setProperties( renderTarget, attackSpeed, range, width, height );

	currentBehaviour = nullptr;
	behaviourFactory = new TurretBehaviourFactory( this );
	changeState( TurretCondition_Enemy_Out_Of_Range );
}

Turret::Turret( Asset calm, Asset angry )
{	
	image_calm = Assets::getInstance()->getAsset( calm );
	image_angry = Assets::getInstance()->getAsset( angry );

	imageMap.insert( std::make_pair( TurretImage_Calm, image_calm ) );
	imageMap.insert( std::make_pair( TurretImage_Angry, image_angry ) );
}

Turret::~Turret()
{

}


/* --------------------------- Model --------------------------- */


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

void Turret::changeState( TurretConditions newCondition )
{
	if( currentBehaviour )
		delete currentBehaviour;
	currentBehaviour = behaviourFactory->createBehaviour( newCondition );
	currentBehaviour->setup();
}

void Turret::update( float deltaTime )
{
	pastTime += deltaTime;

	if( pastTime >= 1.00f / attackSpeed )
		projectileLoaded = true;

	currentBehaviour->checkState();
	currentBehaviour->update( deltaTime );
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


/* --------------------------- View --------------------------- */

void Turret::setImage( TurretImages turretImage )
{
	image_current = imageMap.at( turretImage );
}

void Turret::animate( float deltaTime )
{

}

void Turret::draw( Camera* camera )
{
	SDL_Rect drawingRect = { x - camera->x - w / 2, y - camera->y - h / 2, w, h };
	SDL_RenderCopyEx( renderTarget, image_current, NULL, &drawingRect, rotation, NULL, SDL_FLIP_NONE );

	/*
	SDL_Rect rangeDrawingRect = {drawingRect.x + w / 2 - range, drawingRect.y + h / 2 - range, range * 2, range * 2 };
	SDL_RenderCopy( renderTarget, image_range_correct, NULL, &rangeDrawingRect );
	*/
}