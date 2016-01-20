#pragma once
#include "LevelBehaviour.h"
#include "Wave.h"

class LevelInWaveBehaviour : public LevelBehaviour
{
private:
	Wave* wave;
public:
	LevelInWaveBehaviour( BaseLevelState* level );
	~LevelInWaveBehaviour();

	void update( float deltaTime );
	LevelBehaviour* clone();
};

