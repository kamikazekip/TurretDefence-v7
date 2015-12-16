#include "Assets.h"
#include "global.h"
static Assets* instance;

Assets::Assets()
{

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
	typedef std::map<Asset, SDL_Texture*>::iterator it_type;
	for( it_type iterator = assetMap.begin(); iterator != assetMap.end(); iterator++ )
	{
		SDL_DestroyTexture( iterator->second );
	}
}

void Assets::insertAssetMapEntry( Asset asset, std::string filePath )
{
	assetMap.insert( std::pair<Asset, SDL_Texture*>( asset, loadTexture( filePath, renderTarget ) ) );
}

void Assets::insertAssetMapEntry( std::string key, std::string filePath )
{
	stringToAssetMap.insert( std::pair<std::string, SDL_Texture*>( key, loadTexture( filePath, renderTarget ) ) );
}

void Assets::setRenderTarget( SDL_Renderer* renderTarget )
{
	this->renderTarget = renderTarget;
	insertAssetMapEntry( Asset_MainMenu_Background,				"MainMenu/background.png" );
	insertAssetMapEntry( Asset_BaseLevel_Background,			"Levels/Base/background.jpg" );
	insertAssetMapEntry( Asset_WoodLevel_Background,			"Levels/Wood/wood.jpg" );
	insertAssetMapEntry( Asset_HUD_PlayButton,					"Buttons/Play/PlayButton.png" );
	insertAssetMapEntry( Asset_HUD_PlayButton_Hover,			"Buttons/Play/PlayButtonHover.png" );
	insertAssetMapEntry( Asset_HUD_PlayButton_InWave,			"Buttons/Play/PlayButtonInWave.png" );
	insertAssetMapEntry( Asset_HUD_PlayButton_InWaveHover,		"Buttons/Play/PlayButtonInWaveHover.png" );
	insertAssetMapEntry( Asset_HUD_PlayButton_FastForward,		"Buttons/Play/PlayButtonFastForwarded.png" );
	insertAssetMapEntry( Asset_HUD_PlayButton_FastForwardHover, "Buttons/Play/PlayButtonFastForwardedHover.png" );
	insertAssetMapEntry( Asset_HUD_PauseButton,					"Buttons/Pause/PauseButton.png" );
	insertAssetMapEntry( Asset_HUD_PauseButton_Hover,			"Buttons/Pause/PauseButtonHover.png" );

	insertAssetMapEntry( "easy",								"Enemies/Weak.png" );
	insertAssetMapEntry( "medium",								"Enemies/Intermediate.png" );
}

SDL_Texture* Assets::getAsset( Asset asset )
{
	return assetMap.at( asset );
}

SDL_Texture* Assets::getAsset( TTF_Font* font, std::string text, SDL_Color color )
{
	return createTextTexture( renderTarget, font, text, color );
}

SDL_Texture* Assets::getAsset( std::string key )
{
	return stringToAssetMap.at( key );
}

SDL_Texture* Assets::loadTexture( std::string filePath, SDL_Renderer *renderTarget )
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

SDL_Texture* Assets::createTextTexture( SDL_Renderer* renderTarget, TTF_Font* font, std::string text, SDL_Color color )
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