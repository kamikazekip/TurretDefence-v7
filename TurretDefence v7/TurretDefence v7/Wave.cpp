#include "Wave.h"
#include "global.h"
#include <algorithm>

Wave::Wave(std::vector<Enemy*>* enemies)
{
	enemies->at( 0 )->spawnTime = 0.00f;
	this->enemies = new std::vector<Enemy*>();
	this->unspawnedEnemies = enemies;
	passedTime = 0.00f;
}


Wave::~Wave()
{
	enemies->clear();			delete enemies;				enemies = nullptr;
	unspawnedEnemies->clear();	delete unspawnedEnemies;	unspawnedEnemies = nullptr;
}

void Wave::update( float deltaTime )
{
	spawn( deltaTime );

	for( size_t c = 0; c < enemies->size(); c++ )
	{
		enemies->at( c )->update( deltaTime );
	}	
}

void Wave::draw( Camera* camera )
{
	for( size_t c = 0; c < enemies->size(); c++ )
	{
		enemies->at( c )->draw( camera );
	}
}

void Wave::spawn( float deltaTime )
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
			enemies->push_back( enemy );
		}
	}
}