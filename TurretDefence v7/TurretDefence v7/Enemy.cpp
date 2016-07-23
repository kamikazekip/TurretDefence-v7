#include "Enemy.h"

Enemy::Enemy( Wave* wave, SDL_Texture* image, int maxHealth, int speed, int width, int height, std::vector<SDL_Point> path, float spawnTime )
	: GameObject(path[x].x - (width / 2), path[0].y - (height / 2), width, height)
{
	this->path = path;
	this->maxHealth = maxHealth;
	this->wave = wave;
	health = this->maxHealth;
	takenDamage = 0;
	reachedEnd = false;
	this->speed = speed;
	this->image = image;
	this->spawnTime = spawnTime;

	behaviourFactory = new EnemyBehaviourFactory( this );
	changeState( EnemyCondition_Spawned );

	setTarget(path[1]);
	currentTarget = 1;
	direction = Vector::getDirection( SDL_Point{ x, y }, target );
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
	behaviour->checkState();
	behaviour->update( deltaTime );
}

void Enemy::draw( Camera* camera )
{
	SDL_Rect drawingRect = { x - camera->x, y - camera->y, w, h };
	SDL_RenderCopy( renderTarget, image, NULL, &drawingRect );
}

void Enemy::nextWaypoint()
{
	currentTarget++;
	if( currentTarget < path.size() )
		setTarget( path[currentTarget] );
	else
		reachedEnd = true;
	direction = Vector::getDirection( x, y, target );
}

void Enemy::setTarget( SDL_Point point )
{
	target = point;
	target.x = target.x - ( w / 2 );
	target.y = target.y - ( h / 2 );
}

Enemy* Enemy::clone( float spawnTime, Wave* wave )
{
	Enemy* newEnemy = new Enemy(wave, image, maxHealth, speed, w, h, path, spawnTime );
	return newEnemy;
}