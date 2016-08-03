#pragma once
#include "GameObject.h"
#include "Vector.h"
#include <iostream>
#include "Camera.h"
#include "Assets.h"
#include <map>
#include "Animation.h"
#include "CollisionManager.h"
#include "Enemy.h"
#include "Projectile.h"
#include "TurretBarrel.h"

class BaseLevelState;
class TurretBehaviourFactory;
class TurretBehaviour;

enum TurretConditions { TurretCondition_Enemy_Out_Of_Range, TurretCondition_Enemy_In_Range };
enum TurretImages { TurretImage_Calm, TurretImage_Angry };

class Turret : public GameObject
{
protected:
	/* Model */
	TurretBehaviourFactory* behaviourFactory;
	TurretBehaviour* currentBehaviour;
	Projectile* ammo;
	BaseLevelState* level;
	CollisionManager* collisionManager;
	bool selected;
	bool projectileLoaded;
	float pastTime;
	float attackSpeed;
	double distanceToMuzzle;
	SDL_Point rotationCenter;
	virtual void setAmmo();
	virtual void targetEnemy();
	virtual void fire();

	/* View */
	float scale;
	TurretBarrel* barrel;
	SDL_Texture* image_calm;
	SDL_Texture* image_angry;
	SDL_Texture* image_current;
	SDL_Texture* image_range_correct;
	SDL_Texture* image_range_incorrect;
	SDL_Texture* image_muzzle_flash;
	std::map<TurretImages, SDL_Texture*> imageMap;

	/* Animation */
	Animation* rangeAnimation;
public:
	Turret( ImageAsset calm, ImageAsset angry, ImageAsset barrel_calm, ImageAsset barrel_angry, double x, double y, double range, float attackSpeed, float scale );
	~Turret();

	/* Model */
	Vector direction;
	double range;
	float spread;
	float rotation;
	float rotationSpeed;
	Enemy* target;

	void update( float deltaTime );
	virtual void changeState( TurretConditions newCondition );
	virtual void pullTrigger();
	virtual void onClick();
	virtual void onMissClick();
	virtual void setLevel(BaseLevelState* level);

	/* View */
	virtual void setImage( TurretImages turretImage );
	virtual void animate( float deltaTime );
	virtual void draw( Camera* camera );

	/* Input */
	virtual void onMouseButtonDown( int mouseX, int mouseY );
};

