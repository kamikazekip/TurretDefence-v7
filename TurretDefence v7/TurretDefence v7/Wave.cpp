#include "Wave.h"
#include "global.h"
#include <algorithm>
#include "BaseLevelState.h"

Wave::Wave(BaseLevelState* level)
{
	this->level = level;
	allEnemiesSpawn = false;
	this->unspawnedEnemies	= new std::vector<Enemy*>();
}

Wave::~Wave()
{
	for( size_t c = 0; c < unspawnedEnemies->size(); c++ )
	{
		delete unspawnedEnemies->at( c ); unspawnedEnemies->at( c ) = nullptr;
	}
	delete unspawnedEnemies;	unspawnedEnemies = nullptr;
}

void Wave::update( float deltaTime )
{
	if( unspawnedEnemies->size() > 0 )
	{
		passedTime += deltaTime;
		float requiredTime = unspawnedEnemies->at( 0 )->spawnTime;
		if( passedTime > requiredTime )
		{
			passedTime = 0.00f;
			Enemy* enemy = unspawnedEnemies->at( 0 );
			unspawnedEnemies->erase( std::remove( unspawnedEnemies->begin(), unspawnedEnemies->end(), enemy ), unspawnedEnemies->end() );
			level->addEnemy( enemy );
			if( unspawnedEnemies->size() == 0 )
				allEnemiesSpawn = true;
		}
	}
}

void Wave::setEnemies( std::vector<Enemy*>* enemies )
{
	unspawnedEnemies = enemies;
	unspawnedEnemies->at( 0 )->spawnTime = 0.00f;
	passedTime = 0.00f;
}