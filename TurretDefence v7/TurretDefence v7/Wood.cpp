#include "Wood.h"
#include "Game.h"

Wood::Wood( Game* game, Camera* camera )
	: BaseLevelState( game, camera )
{
	background = new Sprite( game->getRenderer(), Asset::Asset_WoodLevel_Background );
}


Wood::~Wood()
{

}