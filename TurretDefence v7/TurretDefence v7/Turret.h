#pragma once
#include "Vector.h"
#include <iostream>
#include "Camera.h"
#include "Assets.h"
#include <map>
#include "Animation.h"

class TurretBehaviourFactory;
class TurretBehaviour;

enum TurretConditions { TurretCondition_Enemy_Out_Of_Range, TurretCondition_Enemy_In_Range };
enum TurretImages { TurretImage_Calm, TurretImage_Angry };

class Turret
{
protected:
	/* Model */
	TurretBehaviourFactory* behaviourFactory;
	TurretBehaviour* currentBehaviour;
	bool selected;
	bool projectileLoaded;
	float pastTime;
	float attackSpeed;
	SDL_Point rotationCenter;
	virtual void fire();

	/* View */
	SDL_Renderer* renderTarget;
	SDL_Texture* image_calm;
	SDL_Texture* image_angry;
	SDL_Texture* image_current;
	SDL_Texture* image_range_correct;
	SDL_Texture* image_range_incorrect;
	std::map<TurretImages, SDL_Texture*> imageMap;

	/* Animation */
	Animation* rangeAnimation;
public:
	Turret( SDL_Renderer* renderTarget, Asset calm, Asset angry, double x, double y, double range, float attackSpeed, double width, double height );
	~Turret();

	/* Model */
	Vector direction;
	double x, y, w, h;
	double range;
	float spread;
	float rotation;
	float rotationSpeed;
	virtual void changeState( TurretConditions newCondition );
	virtual void pullTrigger();
	virtual void update( float deltaTime );
	virtual bool isTouching( int xPosition, int yPosition );
	virtual void onClick();
	virtual void onMissClick();

	/* View */
	virtual void setImage( TurretImages turretImage );
	virtual void animate( float deltaTime );
	virtual void draw( Camera* camera );
};

