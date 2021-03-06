#pragma once
#include <map>
#include "string"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

class BaseLevelState;
class Wood;
class Game;
class Camera;

class LevelFactory
{
private:
	static enum Levels { Level_Wood, Level_Grass };
	Camera* camera;
	std::map<Levels, BaseLevelState*> levelMap;
	void insertMapEntry( Levels levelEnum, BaseLevelState* level, std::string );
	
public:
	LevelFactory();
	~LevelFactory();

	BaseLevelState* getStartLevel();
};