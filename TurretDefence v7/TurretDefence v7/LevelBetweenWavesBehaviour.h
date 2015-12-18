#pragma once
#include "LevelBehaviour.h"
class LevelBetweenWavesBehaviour : public LevelBehaviour
{
public:
	LevelBetweenWavesBehaviour( BaseLevelState* level );
	~LevelBetweenWavesBehaviour();
	void update( float deltaTime );
	LevelBehaviour* clone( );
};

