#include "Wave.h"
#include "Enemy.h"

Wave::Wave(std::vector<Enemy*>* enemies)
{
	this->enemies = enemies;
}


Wave::~Wave()
{
	for( size_t c = 0; c < enemies->size(); c++ )
	{
		delete enemies->at( c );	enemies->at( c ) = nullptr;
	}
	delete enemies;
}

void Wave::update( float deltaTime )
{

}