#include "Wood.h"
#include "Game.h"
#include "WindowController.h"

Wood::Wood()
	: BaseLevelState( )
{
	background = new Sprite( ImageAsset_WoodLevel_Background );
}


Wood::~Wood()
{

}