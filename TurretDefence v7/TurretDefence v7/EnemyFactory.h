#pragma once
#include "Enemy.h"
#include <string>
#include <map>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

class EnemyFactory
{
private:
	std::string enemiesFile;
	std::map<std::string, Enemy*> enemyMap;
	std::map<std::string, Asset> stringToImageMage;
	void insertEntry( std::string, Enemy* enemy );
public:
	EnemyFactory();
	~EnemyFactory();

	Enemy* createEnemy( std::string type, int spawnTimeMS );
};

