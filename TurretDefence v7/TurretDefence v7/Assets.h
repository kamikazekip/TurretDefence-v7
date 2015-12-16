#pragma once
#include <map>
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

enum Asset
{
	Asset_MainMenu_Background,
	Asset_BaseLevel_Background,
	Asset_WoodLevel_Background,
	Asset_HUD_PlayButton,
	Asset_HUD_PlayButton_Hover,
	Asset_HUD_PlayButton_InWave,
	Asset_HUD_PlayButton_InWaveHover,
	Asset_HUD_PlayButton_FastForward,
	Asset_HUD_PlayButton_FastForwardHover,
	Asset_HUD_PauseButton,
	Asset_HUD_PauseButton_Hover
};

class Assets
{
private:
	std::map<Asset, SDL_Texture*> assetMap;
	SDL_Renderer* renderTarget;

	/* Singleton */
	Assets();
	Assets( Assets const& );
	void operator=(Assets const&);
	SDL_Texture* loadTexture( std::string filePath, SDL_Renderer *renderTarget );
	SDL_Texture* createTextTexture( SDL_Renderer* renderTarget, TTF_Font* font, std::string text, SDL_Color color );

	void insertAssetMapEntry( Asset, std::string filePath );
public:
	/* Singleton */
	static Assets* getInstance();
	~Assets();

	void setRenderTarget( SDL_Renderer* renderTarget );
	SDL_Texture* getAsset( Asset asset );
	SDL_Texture* getAsset( TTF_Font* font, std::string text, SDL_Color color );
};

/**
This function cleans up the entire sound system. You should call it upon all exit conditions.
*/
extern __declspec(dllexport) void Assets_Quit();

