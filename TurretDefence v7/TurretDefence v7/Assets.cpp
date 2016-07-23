#include "Assets.h"
#include "global.h"
#include "WindowController.h"

static Assets* instance;

Assets::Assets()
{
	this->renderTarget = WindowController::getInstance()->getRenderTarget();

	/* ImageAssets */
	insertImageAssetEntry( ImageAsset_OptionsMenu_Overlay, "Menu/Options/OptionsOverlay.png" );
	insertImageAssetEntry( ImageAsset_WoodLevel_Background, "Levels/Wood/wood.jpg" );
	insertImageAssetEntry( ImageAsset_HUD_PlayButton, "Buttons/Play/PlayButton.png" );
	insertImageAssetEntry( ImageAsset_HUD_PlayButton_Hover, "Buttons/Play/PlayButtonHover.png" );
	insertImageAssetEntry( ImageAsset_HUD_PlayButton_InWave, "Buttons/Play/PlayButtonInWave.png" );
	insertImageAssetEntry( ImageAsset_HUD_PlayButton_InWaveHover, "Buttons/Play/PlayButtonInWaveHover.png" );
	insertImageAssetEntry( ImageAsset_HUD_PlayButton_FastForward, "Buttons/Play/PlayButtonFastForwarded.png" );
	insertImageAssetEntry( ImageAsset_HUD_PlayButton_FastForwardHover, "Buttons/Play/PlayButtonFastForwardedHover.png" );
	insertImageAssetEntry( ImageAsset_HUD_PauseButton, "Buttons/Pause/PauseButton.png" );
	insertImageAssetEntry( ImageAsset_HUD_PauseButton_Hover, "Buttons/Pause/PauseButtonHover.png" );
	insertImageAssetEntry( ImageAsset_UI_Paused, "UI/paused.png" );
	insertImageAssetEntry( ImageAsset_Turret_Soldier_Calm, "Turrets/Soldier/soldier_calm.png" );
	insertImageAssetEntry( ImageAsset_Turret_Soldier_Angry, "Turrets/Soldier/soldier_angry.png" );
	insertImageAssetEntry( ImageAsset_Turret_Sniper_Base_Calm, "Turrets/Sniper/sniper_base_calm.png" );
	insertImageAssetEntry( ImageAsset_Turret_Sniper_Base_Angry, "Turrets/Sniper/sniper_base_angry.png" );
	insertImageAssetEntry( ImageAsset_Turret_Sniper_Barrel_Calm, "Turrets/Sniper/sniper_barrel_calm.png" );
	insertImageAssetEntry( ImageAsset_Turret_Sniper_Barrel_Angry, "Turrets/Sniper/sniper_barrel_angry.png" );
	insertImageAssetEntry( ImageAsset_Range_Correct, "UI/range_correct.png" );
	insertImageAssetEntry( ImageAsset_Range_Incorrect, "UI/range_incorrect.png" );
	insertImageAssetEntry( ImageAsset_MuzzleFlash_Default, "Turrets/MuzzleFlashes/sides.png" );

	/* FontAssets */
	insertFontAssetEntry( FontAsset_TitleFont, "action_jackson.ttf", 140 );
	insertFontAssetEntry( FontAsset_MenuItemFont, "action_jackson.ttf", 70 );
	insertFontAssetEntry( FontAsset_VersionFont, "yorkwhiteletter.ttf", 45 );
}

/* Singleton */
Assets* Assets::getInstance()
{
	if( !instance )
		instance = new Assets();
	return instance;
}

Assets::~Assets()
{
	for( std::map<ImageAsset, SDL_Texture*>::iterator	iterator = imageAssetMap.begin(); iterator != imageAssetMap.end(); iterator++ )
		SDL_DestroyTexture( iterator->second );
	for( std::map<FontAsset, TTF_Font*>::iterator		iterator = fontAssetMap.begin(); iterator != fontAssetMap.end(); iterator++ )
		TTF_CloseFont( iterator->second );
}

void Assets::insertImageAssetEntry( ImageAsset asset, std::string filePath )
{
	imageAssetMap.insert( std::make_pair( asset, loadImage( filePath, renderTarget ) ) );
}

void Assets::insertFontAssetEntry( FontAsset key, std::string filePath, int ptsize )
{
	fontAssetToFilePathMap.insert( std::make_pair( key, filePath ) );
	fontAssetMap.insert( std::make_pair( key, loadFont( filePath, ptsize ) ) );
}

SDL_Texture* Assets::getImageAsset( ImageAsset asset )
{
	return imageAssetMap.at( asset );
}

SDL_Texture* Assets::getText( FontAsset font, std::string text, SDL_Color color )
{
	return loadText( renderTarget, getFont(font), text, color );
}

SDL_Texture* Assets::getText( TTF_Font* font, std::string text, SDL_Color color )
{
	return loadText( renderTarget, font, text, color );
}

TTF_Font* Assets::getFont( FontAsset font, int ptsize )
{
	return loadFont(fontAssetToFilePathMap.at( font ), ptsize);
}

TTF_Font* Assets::getFont( FontAsset font )
{
	return fontAssetMap.at( font );
}

SDL_Texture* Assets::getImageAsset( std::string key )
{
	if( stringToImageMap.find( key ) == stringToImageMap.end() )
		stringToImageMap[key] = loadImage( key, renderTarget );
	return stringToImageMap.at( key );
}

SDL_Surface* Assets::getIcon()
{
	std::string filePath = assetBasePath + "Images/UI/icon.png";
	SDL_Surface *icon = IMG_Load( filePath.c_str() );
	if( icon == NULL )
		std::cout << "Error loading image from " << filePath << std::endl;
	return icon;
}

SDL_Texture* Assets::loadImage( std::string filePath, SDL_Renderer *renderTarget )
{
	filePath = assetBasePath + "Images/" + filePath;
	SDL_Texture *texture = nullptr;
	SDL_Surface *surface = IMG_Load( filePath.c_str() );
	if( surface == NULL )
		std::cout << "Error loading image from " << filePath << std::endl;
	else
	{
		texture = SDL_CreateTextureFromSurface( renderTarget, surface );
		if( texture == NULL )
			std::cout << "Error loading texture for image!" << std::endl;
	}
	SDL_FreeSurface( surface );
	return texture;
}

TTF_Font* Assets::loadFont( std::string filePath, int ptsize )
{
	filePath = assetBasePath + "Fonts/" + filePath;
	return TTF_OpenFont( filePath.c_str(), ptsize );
}

SDL_Texture* Assets::loadText( SDL_Renderer* renderTarget, TTF_Font* font, std::string text, SDL_Color color )
{
	SDL_Surface* textSurface = TTF_RenderText_Solid( font, text.c_str(), color );
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface( renderTarget, textSurface );
	SDL_FreeSurface( textSurface );
	return textTexture;
}


extern __declspec(dllexport) void Assets_Quit()
{
	delete instance; instance = nullptr;
}