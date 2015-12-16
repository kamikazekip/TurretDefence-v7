#pragma once
#include <vector>

class Enemy;

class Wave
{
private:
	std::vector<Enemy*>* enemies;
public:
	Wave(std::vector<Enemy*>* enemies);
	~Wave();
	virtual void update( float deltaTime );
};

