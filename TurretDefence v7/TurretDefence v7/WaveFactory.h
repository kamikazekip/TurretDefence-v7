#pragma once
#include "SDL.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

class Wave;
class EnemyFactory;

using namespace std;

class WaveFactory
{
private:
	std::vector<SDL_Point> path;
	std::string wavesFile;
	std::vector<Wave*> waves;
	EnemyFactory* enemyFactory;
public:
	WaveFactory( std::vector<SDL_Point> path );
	~WaveFactory();
	Wave* createWave( int wave );
};

