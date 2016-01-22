#include "Turret.h"
#include "TurretBehaviourFactory.h"


Turret::Turret( SDL_Renderer* renderTarget, Asset calm, Asset angry, float attackSpeed, double range, double width, double height )
{
	/* View */
	this->renderTarget = renderTarget;
	image_calm = Assets::getInstance()->getAsset( calm );
	image_angry = Assets::getInstance()->getAsset( angry );

	image_range_correct = Assets::getInstance()->getAsset( Asset_Range_Correct );
	image_range_incorrect = Assets::getInstance()->getAsset( Asset_Range_Incorrect );
	
	/* Model */
	projectileLoaded = true;
	pastTime = 0.00f;
	spread = 0.00f;
	rotation = 180.0f;
	rotationSpeed = 100.0f;
	selected = false;
	setProperties( renderTarget, attackSpeed, range, width, height );

	currentBehaviour = nullptr;
	behaviourFactory = new TurretBehaviourFactory( this );
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

bool Turret::isTouching( int xPosition, int yPosition )
{
	return ( xPosition >= x && xPosition <= x + w && yPosition >= y && yPosition <= y + h );
}

void Turret::onClick()
{
	selected = !selected;
}


void Turret::transferOrgans( Turret* turret1, Turret* turret2 )
{
	turret2->x						= turret1->x;
	turret2->y						= turret1->y;
	turret2->image_calm				= turret1->image_calm;
	turret2->image_angry			= turret1->image_angry;
	turret2->image_range_correct	= turret1->image_range_correct;
	turret2->image_range_incorrect	= turret1->image_range_incorrect;
	turret2->rotationCenter			= turret1->rotationCenter;
	turret2->fillImageMap();
	turret2->changeState( TurretCondition_Enemy_Out_Of_Range );
}

Turret* Turret::clone( double x, double y )
{
	this->x = x;
	this->y = y;
	Turret* newTurret = new Turret( renderTarget, attackSpeed, range, w, h );
	transferOrgans( this, newTurret );
	return newTurret;
}


/* --------------------------- View --------------------------- */

void Turret::fillImageMap()
{
	imageMap.insert( std::make_pair( TurretImage_Calm, image_calm ) );
	imageMap.insert( std::make_pair( TurretImage_Angry, image_angry ) );
}

void Turret::setImage( TurretImages turretImage )
{
	image_current = imageMap.at( turretImage );
}

void Turret::animate( float deltaTime )
{

}

void Turret::draw( Camera* camera )
{
	SDL_Rect drawingRect = { x - camera->x, y - camera->y - h / 2, w, h };
	SDL_RenderCopyEx( renderTarget, image_current, NULL, &drawingRect, rotation, &rotationCenter, SDL_FLIP_NONE );

	if( selected )
	{
		SDL_Rect rangeDrawingRect = { drawingRect.x + w / 2 - range, drawingRect.y + h / 2 - range, range * 2, range * 2 };
		SDL_RenderCopy( renderTarget, image_range_correct, NULL, &rangeDrawingRect );
	}
}