#pragma once
#include <iostream>
class BaseLevelState;

class LevelBehaviour
{
protected:
	BaseLevelState* level;
public:
	LevelBehaviour( BaseLevelState* level );
	~LevelBehaviour();

	virtual void checkState();
	virtual void update( float deltaTime );
	virtual LevelBehaviour* clone();
};

