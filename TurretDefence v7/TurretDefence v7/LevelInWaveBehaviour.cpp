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

void LevelInWaveBehaviour::update( float deltaTime )
{
	wave->update( deltaTime );
	if( wave->finished )
	{
		level->changeState( LevelCondition_End_Wave );
	}
}

LevelBehaviour* LevelInWaveBehaviour::clone()
{
	return new LevelInWaveBehaviour( level );
}