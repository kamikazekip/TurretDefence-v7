#pragma once
#include <map>
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

enum Asset
{
	Asset_OptionsMenu_Overlay,
	Asset_WoodLevel_Background,
	Asset_HUD_PlayButton,
	Asset_HUD_PlayButton_Hover,
	Asset_HUD_PlayButton_InWave,
	Asset_HUD_PlayButton_InWaveHover,
	Asset_HUD_PlayButton_FastForward,
	Asset_HUD_PlayButton_FastForwardHover,
	Asset_HUD_PauseButton,
	Asset_HUD_PauseButton_Hover,
	Asset_UI_Paused,
	Asset_Turret_Soldier_Calm,
	Asset_Turret_Soldier_Angry,
	Asset_Turret_Sniper_Calm,
	Asset_Turret_Sniper_Angry,
	Asset_Range_Correct,
	Asset_Range_Incorrect
};

class Assets
{
private:
	std::map<Asset, SDL_Texture*> assetMap;
	std::map<std::string, SDL_Texture*> stringToAssetMap;
	SDL_Renderer* renderTarget;

	/* Singleton */
	Assets();
	Assets( Assets const& );
	void operator=(Assets const&);
	SDL_Texture* loadTexture( std::string filePath, SDL_Renderer *renderTarget );
	SDL_Texture* createTextTexture( SDL_Renderer* renderTarget, TTF_Font* font, std::string text, SDL_Color color );

	void insertAssetMapEntry( Asset, std::string filePath );
	void insertAssetMapEntry( std::string key, std::string filePath );
public:
	/* Singleton */
	static Assets* getInstance();
	~Assets();

	void setRenderTarget( SDL_Renderer* renderTarget );
	SDL_Texture* getAsset( Asset asset );
	SDL_Texture* getAsset( TTF_Font* font, std::string text, SDL_Color color );
	SDL_Texture* getAsset( std::string key );
	SDL_Surface* getIcon();
};

/**
This function cleans up the entire sound system. You should call it upon all exit conditions.
*/
extern __declspec(dllexport) void Assets_Quit();

