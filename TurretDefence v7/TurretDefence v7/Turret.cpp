#include "Turret.h"
#include "TurretBehaviourFactory.h"


Turret::Turret( SDL_Renderer* renderTarget, Asset calm, Asset angry, float attackSpeed, double range, double x, double y, double width, double height )
{
	/* View */
	this->renderTarget = renderTarget;
	image_calm = Assets::getInstance()->getAsset( calm );
	image_angry = Assets::getInstance()->getAsset( angry );
	image_range_correct = Assets::getInstance()->getAsset( Asset_Range_Correct );
	image_range_incorrect = Assets::getInstance()->getAsset( Asset_Range_Incorrect );
	
	imageMap.insert( std::make_pair( TurretImage_Calm, image_calm ) );
	imageMap.insert( std::make_pair( TurretImage_Angry, image_angry ) );

	/* Animation */
	vector<pair<float, double>> rangeAnimationSteps;
	rangeAnimationSteps.push_back( make_pair( 0.00f, 0.0 ) );
	rangeAnimationSteps.push_back( make_pair( 0.08f, range + 40 ) );
	rangeAnimationSteps.push_back( make_pair( 0.20f, range ) );
	rangeAnimation = new Animation( rangeAnimationSteps );

	/* Model */
	this->attackSpeed = attackSpeed;
	this->range = range;
	this->x = x;
	this->y = y;
	w = width;
	h = height;
	projectileLoaded = true;
	pastTime = 0.00f;
	spread = 0.00f;
	rotation = 180.0f;
	rotationSpeed = 100.0f;
	selected = false;

	/* Behaviour */
	currentBehaviour = nullptr;
	behaviourFactory = new TurretBehaviourFactory( this );
	changeState( TurretCondition_Enemy_Out_Of_Range );
}

Turret::~Turret()
{

}


/* --------------------------- Model --------------------------- */


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
	if( selected )
		rangeAnimation->setState( AnimationState_Normal );
	else
		rangeAnimation->setState( AnimationState_Reversed );
}

void Turret::onMissClick()
{
	if( selected )
	{
		selected = false;
		rangeAnimation->setState( AnimationState_Reversed );
	}
}

/* --------------------------- View --------------------------- */


void Turret::setImage( TurretImages turretImage )
{
	image_current = imageMap.at( turretImage );
}

void Turret::animate( float deltaTime )
{
	rangeAnimation->animate( deltaTime );
}

void Turret::draw( Camera* camera )
{
	SDL_Rect drawingRect = { x - camera->x, y - camera->y, w, h };

	if( rangeAnimation->getState() != AnimationState_Idle_Waiting && rangeAnimation->getValue() > 0 )
	{
		double visualRange = rangeAnimation->getValue();
		SDL_Rect rangeDrawingRect = { drawingRect.x + w / 2 - visualRange, drawingRect.y + h / 2 - visualRange, visualRange * 2, visualRange * 2 };
		SDL_RenderCopy( renderTarget, image_range_correct, NULL, &rangeDrawingRect );
	}
	SDL_RenderCopyEx( renderTarget, image_current, NULL, &drawingRect, rotation, &rotationCenter, SDL_FLIP_NONE );
}