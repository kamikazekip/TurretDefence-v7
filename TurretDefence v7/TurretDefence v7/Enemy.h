#pragma once
#include "EnemyBehaviour.h"
#include "EnemyBehaviourFactory.h"
#include <vector>
#include "Vector.h"
#include "Camera.h"

class Enemy
{
protected:
	SDL_Renderer* renderTarget;
	int takenDamage;
	SDL_Texture* image;
	EnemyConditions currentCondition;
	EnemyBehaviour* behaviour;
	EnemyBehaviourFactory* behaviourFactory;
	
public:
	Enemy( SDL_Renderer* renderTarget, SDL_Texture* image, int maxHealth, int speed, int width, int height, std::vector<SDL_Point> path, float spawnTime );
	~Enemy();

	virtual void changeState( EnemyConditions condition );
	virtual void takeDamage( int damage );

	virtual void update( float deltaTime );
	virtual void animate( float deltaTime );
	virtual void draw( Camera* camera );

	virtual void nextWaypoint();

	virtual Enemy* clone( float spawnTime );

	double x, y, w, h;
	Vector direction;
	std::vector<SDL_Point> path;
	SDL_Point target;
	int currentTarget;
	int health;
	int maxHealth;
	int speed;
	float spawnTime;
};

