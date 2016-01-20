#include "LevelBetweenWavesBehaviour.h"
#include "BaseLevelState.h"

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
	level->nextWave();
	return new LevelBetweenWavesBehaviour( level );
}
