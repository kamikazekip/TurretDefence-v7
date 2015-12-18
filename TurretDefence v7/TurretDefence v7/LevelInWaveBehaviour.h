#pragma once
#include "LevelBehaviour.h"

class LevelInWaveBehaviour : public LevelBehaviour
{
public:
	LevelInWaveBehaviour( BaseLevelState* level );
	~LevelInWaveBehaviour();

	void update( float deltaTime );
	LevelBehaviour* clone();
};

