#pragma once
#include "Vector.h"
#include <iostream>
#include "Camera.h"
#include "Assets.h"
#include <map>

class TurretBehaviourFactory;
class TurretBehaviour;

enum TurretConditions { TurretCondition_Enemy_Out_Of_Range, TurretCondition_Enemy_In_Range };
enum TurretImages { TurretImage_Calm, TurretImage_Angry };

class Turret
{
protected:
	/* View */
	SDL_Renderer* renderTarget;
	SDL_Texture* image_calm;
	SDL_Texture* image_angry;
	SDL_Texture* image_current;
	SDL_Texture* image_range_correct;
	SDL_Texture* image_range_incorrect;
	std::map<TurretImages, SDL_Texture*> imageMap;

	/* Model */
	TurretBehaviourFactory* behaviourFactory;
	TurretBehaviour* currentBehaviour;
	bool projectileLoaded;
	float pastTime;
	float attackSpeed;
	virtual void fire();
public:
	Turret( SDL_Renderer* renderTarget, float attackSpeed, double range, double width, double height );
	Turret( Asset calm, Asset angry );
	~Turret();

	/* Model */
	Vector direction;
	double x, y, w, h;
	double range;
	float spread;
	float rotation;
	float rotationSpeed;
	virtual void setProperties( SDL_Renderer* renderTarget, float attackSpeed, double range, double width, double height );
	virtual void changeState( TurretConditions newCondition );
	virtual void pullTrigger();
	virtual void update( float deltaTime );
	virtual Turret* clone( double x, double y );

	/* View */
	virtual void setImage( TurretImages turretImage );
	virtual void animate( float deltaTime );
	virtual void draw( Camera* camera );
};

