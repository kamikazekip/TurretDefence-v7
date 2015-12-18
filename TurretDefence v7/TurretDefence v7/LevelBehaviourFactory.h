#pragma once
#include "BaseLevelState.h"
#include <map>

class LevelBehaviour;

class LevelBehaviourFactory
{
private:
	std::map<LevelConditions, LevelBehaviour*> behaviourMap;
	void insertEntry( LevelConditions condition, LevelBehaviour* behaviour );
public:
	LevelBehaviourFactory( BaseLevelState* level );
	~LevelBehaviourFactory();

	LevelBehaviour* createBehaviour( LevelConditions newCondition );
};

