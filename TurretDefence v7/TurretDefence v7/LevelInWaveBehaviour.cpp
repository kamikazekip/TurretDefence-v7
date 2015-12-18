#include "LevelInWaveBehaviour.h"


LevelInWaveBehaviour::LevelInWaveBehaviour( BaseLevelState* level )
	: LevelBehaviour( level )
{

}


LevelInWaveBehaviour::~LevelInWaveBehaviour()
{

}

void LevelInWaveBehaviour::update( float deltaTime )
{
	
}

LevelBehaviour* LevelInWaveBehaviour::clone()
{
	return new LevelInWaveBehaviour( level );
}