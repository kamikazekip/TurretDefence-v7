#include "Enemy.h"

Enemy::Enemy( SDL_Renderer* renderTarget, SDL_Texture* image, int maxHealth, int speed, int width, int height, std::vector<SDL_Point> path, float spawnTime )
{
	this->renderTarget = renderTarget;
	this->path = path;
	this->maxHealth = maxHealth;
	health = this->maxHealth;
	takenDamage = 0;
	this->speed = speed;
	w = width;
	h = height;
	x = path[0].x;
	y = path[0].y;
	this->image = image;
	this->spawnTime = spawnTime;

	behaviourFactory = new EnemyBehaviourFactory( this );
	changeState( EnemyCondition_Spawned );

	target = path[1];
	currentTarget = 1;
	direction = Vector::getDirection( path[0], target );
}

Enemy::~Enemy()
{

}

void Enemy::takeDamage( int damage )
{

}

void Enemy::changeState(EnemyConditions condition)
{
	currentCondition = condition;
	behaviour = behaviourFactory->createBehaviour( currentCondition );
}

void Enemy::update( float deltaTime )
{
	behaviour->update( deltaTime );
}

void Enemy::animate( float deltaTime )
{

}

void Enemy::draw( Camera* camera )
{
	SDL_Rect drawingRect = { x - camera->x - w / 2, y - camera->y - h / 2, w, h };
	SDL_RenderCopy( renderTarget, image, NULL, &drawingRect );
}

void Enemy::nextWaypoint()
{
	currentTarget++;
	if( currentTarget < path.size() )
		target = path[ currentTarget ];
	direction = Vector::getDirection( SDL_Point{ x, y }, target );
}

Enemy* Enemy::clone( float spawnTime )
{
	Enemy* newEnemy = new Enemy(renderTarget, image, maxHealth, speed, w, h, path, spawnTime );
	return newEnemy;
}