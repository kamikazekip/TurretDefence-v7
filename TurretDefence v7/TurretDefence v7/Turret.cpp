#include "Turret.h"
#include "TurretBehaviourFactory.h"
#include "WindowController.h"
#include "ProjectileFactory.h"
#include "global.h"
#include "BaseLevelState.h"

Turret::Turret(  ImageAsset calm, ImageAsset angry, ImageAsset barrel_calm, ImageAsset barrel_angry, double x, double y, double range, float attackSpeed, float scale )
{
	/* View */
	this->scale				= scale;
	image_calm				= Assets::getInstance()->getImageAsset( calm );
	image_angry				= Assets::getInstance()->getImageAsset( angry );
	image_range_correct		= Assets::getInstance()->getImageAsset( ImageAsset_Range_Correct );
	image_range_incorrect	= Assets::getInstance()->getImageAsset( ImageAsset_Range_Incorrect );
	image_muzzle_flash		= Assets::getInstance()->getImageAsset( ImageAsset_MuzzleFlash_Default );
	
	imageMap.insert( std::make_pair( TurretImage_Calm, image_calm ) );
	imageMap.insert( std::make_pair( TurretImage_Angry, image_angry ) );

	/* Animation */
	vector<pair<float, double>> rangeAnimationSteps;
	rangeAnimationSteps.push_back( make_pair( 0.00f, 0.0 ) );
	rangeAnimationSteps.push_back( make_pair( 0.15f, range + 60 ) );	/* 0.08f default */
	rangeAnimationSteps.push_back( make_pair( 0.25f, range ) );			/* 0.20f default */
	rangeAnimation = new Animation( rangeAnimationSteps, AnimationSpeed_Fixed_Speed );

	/* Model */
	this->attackSpeed = attackSpeed;
	this->range = range;
	int imageWidth = 0;
	int imageHeight = 0;
	SDL_QueryTexture( image_calm, NULL, NULL, &imageWidth, &imageHeight );
	this->x = x;
	this->y = y;
	this->w = imageWidth * scale;
	this->h = imageHeight * scale;
	projectileLoaded = true;
	pastTime = 0.00f;
	spread = 0.00f;
	rotation = 180.0f;
	rotationSpeed = 360.0f;
	target = nullptr;
	selected = false;
	ammo = nullptr;
	setAmmo();
	barrel = new TurretBarrel( barrel_calm, barrel_angry, rotation, getOriginX(), getOriginY(), scale );
	this->distanceToMuzzle = barrel->getDistanceToMuzzle();

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

void Turret::targetEnemy( )
{
	std::vector<Enemy*> enemiesInRange = collisionManager->enemiesInRange( getOriginX(), getOriginY(), range );
	if( enemiesInRange.size() > 0 )
		target = enemiesInRange[0];
	else
		target = nullptr;
}

void Turret::update( float deltaTime )
{
	pastTime += deltaTime;

	if( pastTime >= 1.00f / attackSpeed )
		projectileLoaded = true;

	targetEnemy();

	currentBehaviour->checkState();
	currentBehaviour->update( deltaTime );
	barrel->updateRotation( rotation );
}

void Turret::setAmmo()
{
	if( ammo != nullptr )
		delete ammo;
	ammo = ProjectileFactory::getInstance()->getProjectilePrototype( "default" );
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
	float radians = ( rotation - 90 ) * DEGTORAD;
	Vector direction = { cos( radians ), sin( radians ) };
	direction.normalize();
	double projectileX = getOriginX() + ( direction.x * distanceToMuzzle );
	double projectileY = getOriginY() + ( direction.y * distanceToMuzzle );
	Projectile* newProjectile = ammo->clone( projectileX, projectileY, direction, rotation, image_muzzle_flash );
	level->addProjectile( newProjectile );
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

void Turret::setLevel( BaseLevelState* level )
{
	this->level = level;
}

void Turret::setCollisionManager( CollisionManager* collisionManager )
{
	this->collisionManager = collisionManager;
}

/* --------------------------- View --------------------------- */

void Turret::setImage( TurretImages turretImage )
{
	image_current				= imageMap.at( turretImage );
	barrel->setImage( turretImage );
}

void Turret::animate( float deltaTime )
{
	rangeAnimation->animate( deltaTime );
}

void Turret::draw( Camera* camera )
{
	SDL_Rect drawingRect = getDrawingRect( camera );

	if( rangeAnimation->getState() != AnimationState_Idle_Waiting && rangeAnimation->getValue() > 0 )
	{
		double visualRange = rangeAnimation->getValue();
		SDL_Rect rangeDrawingRect = { drawingRect.x + w / 2 - visualRange, drawingRect.y + h / 2 - visualRange, visualRange * 2, visualRange * 2 };
		SDL_RenderCopy( renderTarget, image_range_correct, NULL, &rangeDrawingRect );
	}
	SDL_RenderCopyEx( renderTarget, image_current, NULL, &drawingRect, rotation, &rotationCenter, SDL_FLIP_NONE );

	barrel->draw( camera );
}