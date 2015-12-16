#include "PlayButton.h"
#include "Game.h"

PlayButton::PlayButton(Game* game)
	: HUDButton( game->getRenderer(), Asset_HUD_PlayButton, Asset_HUD_PlayButton_Hover )
{
	this->game = game;
	inBetweenWaves		= Assets::getInstance()->getAsset( Asset_HUD_PlayButton );
	inBetweenWavesHover = Assets::getInstance()->getAsset( Asset_HUD_PlayButton_Hover );
	inWave				= Assets::getInstance()->getAsset( Asset_HUD_PlayButton_InWave );
	inWaveHover			= Assets::getInstance()->getAsset( Asset_HUD_PlayButton_InWaveHover );
	fastForward			= Assets::getInstance()->getAsset( Asset_HUD_PlayButton_FastForward );
	fastForwardHover	= Assets::getInstance()->getAsset( Asset_HUD_PlayButton_FastForwardHover );

	textureMap.insert( std::pair<PlayButtonState, SDL_Texture*>( PlayButton_InBetweenWaves, inBetweenWaves ) );
	textureMap.insert( std::pair<PlayButtonState, SDL_Texture*>( PlayButton_InWave, inWave ) );
	textureMap.insert( std::pair<PlayButtonState, SDL_Texture*>( PlayButton_FastForward, fastForward ) );

	hoverTextureMap.insert( std::pair<PlayButtonState, SDL_Texture*>( PlayButton_InBetweenWaves, inBetweenWavesHover ) );
	hoverTextureMap.insert( std::pair<PlayButtonState, SDL_Texture*>( PlayButton_InWave, inWaveHover ) );
	hoverTextureMap.insert( std::pair<PlayButtonState, SDL_Texture*>( PlayButton_FastForward, fastForwardHover ) );

	setState( PlayButton_InBetweenWaves );
}


PlayButton::~PlayButton()
{

}

void PlayButton::setState( PlayButtonState newState )
{
	currentState	= newState;
	normalTexture	= textureMap.at( currentState );
	hoverTexture	= hoverTextureMap.at( currentState );
}

void PlayButton::onClick()
{
	switch( currentState )
	{
		case ( PlayButton_InBetweenWaves ) :
			setState( PlayButton_InWave );
			game->setFPS( 60 );
			break;
		case( PlayButton_InWave ) :
			setState( PlayButton_FastForward );
			game->setFPS( 120 );
			break;
		case( PlayButton_FastForward ) :
			setState( PlayButton_InWave );
			game->setFPS( 60 );
			break;
	}
}