#include "LevelBetweenWavesBehaviour.h"


LevelBetweenWavesBehaviour::LevelBetweenWavesBehaviour( BaseLevelState* level )
	: LevelBehaviour( level )
{
}


LevelBetweenWavesBehaviour::~LevelBetweenWavesBehaviour()
{

}

void LevelBetweenWavesBehaviour::update( float deltaTime )
{

}

LevelBehaviour* LevelBetweenWavesBehaviour::clone()
{
	return new LevelBetweenWavesBehaviour( level );
}
