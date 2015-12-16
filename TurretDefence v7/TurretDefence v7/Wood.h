#pragma once
#include "BaseLevelState.h"
class Wood : public BaseLevelState
{
public:
	Wood( Game* game, Camera* camera );
	~Wood();
	void tick( float deltaTime );
};

