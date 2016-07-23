#include "AssetLoader.h"
#include "Version.h"
#include "global.h"
#include "WindowController.h"

AssetLoader::AssetLoader()
	: LoopHandler()
{
	this->game		= Game::getInstance();
	windowWidth		= WindowController::getInstance()->width;
	windowHeight	= WindowController::getInstance()->height;

	version = new Sprite( FontAsset_VersionFont, Version::getInstance()->getYorkVersion(), menuFontColor );
	version->positionRect.x = 20;
	version->positionRect.y = windowHeight - version->positionRect.h - 10;
}


AssetLoader::~AssetLoader()
{
	delete version;						version = nullptr;
}

void AssetLoader::tick( float deltaTime )
{
	draw();
}

void AssetLoader::draw()
{
	version->draw();
}