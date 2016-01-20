#pragma once
#include "Enemy.h"
#include "Assets.h"
#include <string>
#include <map>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

class EnemyFactory
{
private:
	std::vector<SDL_Point> path;
	std::string enemiesFile;
	std::map<std::string, Enemy*> enemyMap;
	void insertEntry( std::string, Enemy* enemy );
public:
	EnemyFactory( SDL_Renderer* renderTarget, std::vector<SDL_Point> path );
	~EnemyFactory();

	Enemy* createEnemy( std::string type, float spawnTime, Wave* wave );
};

