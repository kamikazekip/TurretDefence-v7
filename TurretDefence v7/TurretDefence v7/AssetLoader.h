#pragma once
#include "LoopHandler.h"
#include "Game.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Assets.h"


class AssetLoader : public LoopHandler
{
protected:
	Game* game;
	std::string action_jackson;
	std::string york;
	TTF_Font* versionFont;
	TTF_Font* menuItemFont;
	TTF_Font* titleFont;
	Sprite* version;
	int windowWidth, windowHeight;
	/* Functions */
public:
	AssetLoader();
	~AssetLoader();
	void tick( float deltaTime );
	void draw();
};

