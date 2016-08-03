#include "Enemy.h"

Enemy::Enemy( SDL_Texture* image, int maxHealth, int speed, int width, int height, std::vector<SDL_Point> path, float spawnTime )
	: GameObject(path[x].x - (width / 2), path[0].y - (height / 2), width, height)
{
	this->collisionManager = CollisionManager::getInstance();
	this->path = path;
	this->maxHealth = maxHealth;
	health = this->maxHealth;
	takenDamage = 0;
	reachedEnd = false;
	this->speed = speed;
	this->image = image;
	maxHealthBar.w = w * 0.70;
	this->maxHealthBar.h = 7;
	this->healthBar.h = maxHealthBar.h;
	this->takenDamageBar.h = maxHealthBar.h;
	this->healthBarOffset = 10 + maxHealthBar.h;
	this->spawnTime = spawnTime;
	this->dead = false;
	this->behaviour = nullptr;
	behaviourFactory = new EnemyBehaviourFactory( this );
	changeState( EnemyCondition_Spawned );

	setTarget(path[1]);
	currentTarget = 1;
	direction = Vector::getDirection( SDL_Point{ x, y }, target );
}

Enemy::~Enemy()
{
	delete behaviour; behaviour = nullptr;
	delete behaviourFactory; behaviourFactory = nullptr;
}

void Enemy::takeDamage( int damage )
{
	if( health > 0 )
	{
		health -= damage;
		takenDamage += damage;
	
		if( health <= 0 )
		{
			health = 0;
			dead = true;
		}
		if( takenDamage > maxHealth )
			takenDamage = maxHealth;
	}
}

void Enemy::changeState(EnemyConditions condition)
{
	currentCondition = condition;
	if( behaviour != nullptr )
		delete behaviour;
	behaviour = behaviourFactory->createBehaviour( currentCondition );
	behaviour->setup();
}

void Enemy::update( float deltaTime )
{
	behaviour->checkState();
	behaviour->update( deltaTime );

	if( takenDamage <= 0 )
		takenDamage = 0;
	else
		takenDamage -= maxHealth * 0.05;
}

void Enemy::collide()
{
	std::vector<Projectile*> projectiles = collisionManager->projectilesInContact( x, y, w, h );
	for( Projectile* projectile : projectiles )
	{
		takeDamage( projectile->damage );
		projectile->trash = true;
	}
}

void Enemy::draw( Camera* camera )
{
	SDL_Rect drawingRect = { x - camera->x, y - camera->y, w, h };
	SDL_RenderCopy( renderTarget, image, NULL, &drawingRect );

	if( health < maxHealth )
		drawHealthBar( camera );
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

void Enemy::drawHealthBar( Camera* camera )
{
	int widthDifference = w - maxHealthBar.w;
	maxHealthBar.x = x - camera->x + ( widthDifference / 2 );
	maxHealthBar.y = y - camera->y - healthBarOffset;

	float healthPercentage = float( health ) / float( maxHealth );
	healthBar.w = maxHealthBar.w * healthPercentage;
	healthBar.x = maxHealthBar.x;
	healthBar.y = maxHealthBar.y;

	float takenDamagePercentage = float( takenDamage ) / float( maxHealth );
	takenDamageBar.w = maxHealthBar.w * takenDamagePercentage;
	takenDamageBar.x = healthBar.x + healthBar.w;
	takenDamageBar.y = maxHealthBar.y;

	SDL_SetRenderDrawColor( renderTarget, 255, 0, 0, 255 );
	SDL_RenderFillRect( renderTarget, &takenDamageBar );

	SDL_SetRenderDrawColor( renderTarget, 0, 255, 0, 255 );
	SDL_RenderFillRect( renderTarget, &healthBar );

	SDL_SetRenderDrawColor( renderTarget, 0, 0, 0, 255 );
	SDL_RenderDrawRect( renderTarget, &maxHealthBar );
}

bool Enemy::canCollide()
{
	return !dead;
}

Enemy* Enemy::clone( float spawnTime )
{
	Enemy* newEnemy = new Enemy(image, maxHealth, speed, w, h, path, spawnTime );
	return newEnemy;
}