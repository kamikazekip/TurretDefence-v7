#include "LevelBehaviour.h"


LevelBehaviour::LevelBehaviour(BaseLevelState* level)
{
	this->level = level;
}


LevelBehaviour::~LevelBehaviour()
{

}

void LevelBehaviour::checkState()
{

}

void LevelBehaviour::update( float deltaTime )
{

}

LevelBehaviour* LevelBehaviour::clone()
{
	return new LevelBehaviour( level );
}