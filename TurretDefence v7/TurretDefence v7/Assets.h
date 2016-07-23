#pragma once
#include <map>
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

enum ImageAsset
{
	ImageAsset_OptionsMenu_Overlay,
	ImageAsset_WoodLevel_Background,
	ImageAsset_HUD_PlayButton,
	ImageAsset_HUD_PlayButton_Hover,
	ImageAsset_HUD_PlayButton_InWave,
	ImageAsset_HUD_PlayButton_InWaveHover,
	ImageAsset_HUD_PlayButton_FastForward,
	ImageAsset_HUD_PlayButton_FastForwardHover,
	ImageAsset_HUD_PauseButton,
	ImageAsset_HUD_PauseButton_Hover,
	ImageAsset_UI_Paused,
	ImageAsset_Turret_Soldier_Calm,
	ImageAsset_Turret_Soldier_Angry,
	ImageAsset_Turret_Sniper_Base_Calm,
	ImageAsset_Turret_Sniper_Base_Angry,
	ImageAsset_Turret_Sniper_Barrel_Calm,
	ImageAsset_Turret_Sniper_Barrel_Angry,
	ImageAsset_Range_Correct,
	ImageAsset_Range_Incorrect,
	ImageAsset_MuzzleFlash_Default
};

enum FontAsset
{
	FontAsset_Action_Jackson,
	FontAsset_York,
	FontAsset_VersionFont,
	FontAsset_TitleFont,
	FontAsset_MenuItemFont
};

class Assets
{
private:
	std::map<ImageAsset, SDL_Texture*> imageAssetMap;
	std::map<std::string, SDL_Texture*> stringToImageMap;
	std::map<FontAsset, TTF_Font*> fontAssetMap;
	std::map<FontAsset, std::string> fontAssetToFilePathMap;
	SDL_Renderer* renderTarget;

	SDL_Texture*	loadImage( std::string filePath, SDL_Renderer *renderTarget );
	TTF_Font*		loadFont( std::string filePath, int ptsize );
	SDL_Texture*	loadText( SDL_Renderer* renderTarget, TTF_Font* font, std::string text, SDL_Color color );
	void insertImageAssetEntry( ImageAsset key, std::string filePath );
	void insertFontAssetEntry( FontAsset key, std::string filePath, int ptsize );

	/* Singleton */
	Assets();
	Assets( Assets const& );
public:
	/* Singleton */
	static Assets* getInstance();
	~Assets();
	SDL_Texture* getImageAsset( ImageAsset asset );
	SDL_Texture* getImageAsset( std::string key );
	SDL_Texture* getText( FontAsset font, std::string text, SDL_Color color );
	SDL_Texture* getText( TTF_Font* font, std::string text, SDL_Color color );
	TTF_Font*	 getFont( FontAsset font, int ptsize );
	TTF_Font*	 getFont( FontAsset font );
	SDL_Surface* getIcon();
};

extern __declspec(dllexport) void Assets_Quit();

