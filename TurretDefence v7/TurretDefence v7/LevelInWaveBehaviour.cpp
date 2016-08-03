#include "LevelInWaveBehaviour.h"
#include "BaseLevelState.h"

LevelInWaveBehaviour::LevelInWaveBehaviour( BaseLevelState* level )
	: LevelBehaviour( level )
{
	wave = level->getWave();
}


LevelInWaveBehaviour::~LevelInWaveBehaviour()
{

}

void LevelInWaveBehaviour::checkState()
{

	if( wave->allEnemiesSpawn && level->enemies->size() == 0 )
		level->changeState( LevelCondition_End_Wave );
}

void LevelInWaveBehaviour::update( float deltaTime )
{
	wave->update( deltaTime );
}

LevelBehaviour* LevelInWaveBehaviour::clone()
{
	return new LevelInWaveBehaviour( level );
}