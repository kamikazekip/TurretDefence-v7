#include "LevelBehaviourFactory.h"
#include "LevelBehaviour.h"
#include "LevelBetweenWavesBehaviour.h"
#include "LevelInWaveBehaviour.h"

LevelBehaviourFactory::LevelBehaviourFactory(BaseLevelState* level)
{
	insertEntry( LevelCondition_Init,			new LevelBetweenWavesBehaviour( level ) );
	insertEntry( LevelCondition_Start_Wave,		new LevelInWaveBehaviour( level ) );
	insertEntry( LevelCondition_End_Wave,		new LevelBetweenWavesBehaviour( level ) );
}


LevelBehaviourFactory::~LevelBehaviourFactory()
{
	for( std::map<LevelConditions, LevelBehaviour*>::iterator iterator = behaviourMap.begin(); iterator != behaviourMap.end(); iterator++ )
		delete iterator->second;
}

void LevelBehaviourFactory::insertEntry( LevelConditions condition, LevelBehaviour* behaviour )
{
	behaviourMap.insert( std::pair<LevelConditions, LevelBehaviour*>( condition, behaviour ) );
}

LevelBehaviour* LevelBehaviourFactory::createBehaviour( LevelConditions newCondition )
{
	return behaviourMap.at( newCondition )->clone();
}
