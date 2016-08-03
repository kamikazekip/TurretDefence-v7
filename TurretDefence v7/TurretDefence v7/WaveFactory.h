#pragma once
#include "SDL.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

class Wave;
class EnemyFactory;
class BaseLevelState;

using namespace std;

class WaveFactory
{
private:
	BaseLevelState* level;
	std::vector<SDL_Point> path;
	std::string wavesFile;
	std::vector<Wave*>* waves;
	EnemyFactory* enemyFactory;
	SDL_Renderer* renderTarget;
public:
	WaveFactory( BaseLevelState* level );
	~WaveFactory();
	bool canCreateWave( int wave );
	Wave* createWave( int wave );
};

