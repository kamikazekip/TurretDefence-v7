#include "LevelInWaveBehaviour.h"
#include "BaseLevelState.h"

LevelInWaveBehaviour::LevelInWaveBehaviour( BaseLevelState* level )
	: LevelBehaviour( level )
{

}


LevelInWaveBehaviour::~LevelInWaveBehaviour()
{

}

void LevelInWaveBehaviour::update( float deltaTime )
{
	level->getWave()->update( deltaTime );
}

LevelBehaviour* LevelInWaveBehaviour::clone()
{
	return new LevelInWaveBehaviour( level );
}