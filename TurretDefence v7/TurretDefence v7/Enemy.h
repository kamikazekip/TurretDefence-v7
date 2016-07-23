#pragma once
#include "GameObject.h"
#include "EnemyBehaviour.h"
#include "EnemyBehaviourFactory.h"
#include <vector>
#include "Vector.h"
#include "Camera.h"

class Wave;

class Enemy : public GameObject
{
protected:
	int takenDamage;
	SDL_Texture* image;
	EnemyConditions currentCondition;
	EnemyBehaviour* behaviour;
	EnemyBehaviourFactory* behaviourFactory;
	Wave* wave;
public:
	Enemy( Wave* wave, SDL_Texture* image, int maxHealth, int speed, int width, int height, std::vector<SDL_Point> path, float spawnTime );
	~Enemy();

	virtual void changeState( EnemyConditions condition );
	virtual void takeDamage( int damage );

	void update( float deltaTime );
	void draw( Camera* camera );

	virtual void nextWaypoint();
	virtual void setTarget(SDL_Point point);

	virtual Enemy* clone( float spawnTime, Wave* wave );

	Vector direction;
	std::vector<SDL_Point> path;
	SDL_Point target;
	int currentTarget;
	int health;
	int maxHealth;
	int speed;
	float spawnTime;
	bool reachedEnd;
};

