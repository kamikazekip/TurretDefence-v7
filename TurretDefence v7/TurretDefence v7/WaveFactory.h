#pragma once
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

class Wave;
class EnemyFactory;

using namespace std;

class WaveFactory
{
private:
	std::string wavesFile;
	std::vector<Wave*> waves;
	EnemyFactory* enemyFactory;
public:
	WaveFactory();
	~WaveFactory();
	Wave* createWave( int wave );
};

