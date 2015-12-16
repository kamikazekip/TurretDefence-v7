#include "LevelFactory.h"
#include "BaseLevelState.h"
#include "Wood.h"
#include "Camera.h"

LevelFactory::LevelFactory(Game* game, Camera* camera)
{
	this->game = game;
	this->camera = camera;
}


LevelFactory::~LevelFactory()
{

}

BaseLevelState* LevelFactory::getStartLevel()
{
	return new Wood( game, camera );
}