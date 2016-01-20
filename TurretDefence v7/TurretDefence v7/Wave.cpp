#include "Wave.h"
#include "global.h"
#include <algorithm>

Wave::Wave()
{
	finished = false;
	this->unspawnedEnemies	= new std::vector<Enemy*>();
	this->enemyRemoveStack	= new std::vector<Enemy*>();
	this->enemies			= new std::vector<Enemy*>();
}

Wave::~Wave()
{
	enemies->clear();			delete enemies;				enemies = nullptr;
	unspawnedEnemies->clear();	delete unspawnedEnemies;	unspawnedEnemies = nullptr;
	enemyRemoveStack->clear();	delete enemyRemoveStack;	enemyRemoveStack = nullptr;
}

void Wave::update( float deltaTime )
{
	removeFinishedEnemies();
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

void Wave::removeFinishedEnemies()
{
	for( size_t c = 0; c < enemies->size(); c++ )
		if( enemies->at( c )->reachedEnd )
			enemyRemoveStack->push_back( enemies->at( c ) );

	for( size_t x = 0; x < enemyRemoveStack->size(); x++ )
		enemies->erase( std::remove( enemies->begin(), enemies->end(), enemyRemoveStack->at( x ) ), enemies->end() );
	enemyRemoveStack->clear();

	if( enemies->size() == 0 && unspawnedEnemies->size() == 0 )
	{
		finished = true;
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

void Wave::setEnemies( std::vector<Enemy*>* enemies )
{
	enemies->at( 0 )->spawnTime = 0.00f;
	for( size_t c = 0; c < enemies->size(); c++ )
		unspawnedEnemies->push_back( enemies->at( c ) );
	passedTime = 0.00f;
}