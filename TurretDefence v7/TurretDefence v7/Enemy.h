#pragma once
#include "GameObject.h"
#include "EnemyBehaviour.h"
#include "EnemyBehaviourFactory.h"
#include <vector>
#include "Vector.h"
#include "Camera.h"
#include "CollisionManager.h"
#include "Projectile.h"


enum EnemyConditions
{
	EnemyCondition_Spawned,
	EnemyCondition_Health_Depleted,
};


class Enemy : public GameObject
{
protected:
	CollisionManager* collisionManager;
	EnemyConditions currentCondition;
	EnemyBehaviour* behaviour;
	EnemyBehaviourFactory* behaviourFactory;

	/* View */
	SDL_Texture* image;
	double healthBarOffset;
	SDL_Rect maxHealthBar;
	SDL_Rect healthBar;
	SDL_Rect takenDamageBar;
public:
	Enemy( SDL_Texture* image, int maxHealth, int speed, int width, int height, std::vector<SDL_Point> path, float spawnTime );
	~Enemy();

	virtual void changeState( EnemyConditions condition );
	virtual void takeDamage( int damage );

	void update( float deltaTime );
	void collide();
	void draw( Camera* camera );

	virtual void nextWaypoint();
	virtual void setTarget(SDL_Point point);
	virtual void drawHealthBar( Camera* camera );
	virtual bool canCollide();

	virtual Enemy* clone( float spawnTime );

	Vector direction;
	std::vector<SDL_Point> path;
	SDL_Point target;
	int currentTarget;
	int health;
	int maxHealth;
	int takenDamage;
	int speed;
	float spawnTime;
	bool reachedEnd;
	bool dead;
};

