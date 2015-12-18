#include "LevelBehaviourFactory.h"
#include "LevelBehaviour.h"
#include "LevelBetweenWavesBehaviour.h"
#include "LevelInWaveBehaviour.h"

LevelBehaviourFactory::LevelBehaviourFactory(BaseLevelState* level)
{
	LevelBetweenWavesBehaviour* inBetween = new LevelBetweenWavesBehaviour( level );
	insertEntry( LevelCondition_Init,	inBetween);
	insertEntry( LevelCondition_Start,	new LevelInWaveBehaviour( level ) );
	insertEntry( LevelCondition_End,	inBetween );
}


LevelBehaviourFactory::~LevelBehaviourFactory()
{

}

void LevelBehaviourFactory::insertEntry( LevelConditions condition, LevelBehaviour* behaviour )
{
	behaviourMap.insert( std::pair<LevelConditions, LevelBehaviour*>( condition, behaviour ) );
}

LevelBehaviour* LevelBehaviourFactory::createBehaviour( LevelConditions newCondition )
{
	return behaviourMap.at( newCondition )->clone();
}
