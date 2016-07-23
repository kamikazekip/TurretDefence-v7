#include "PlayButton.h"
#include "Game.h"

PlayButton::PlayButton(Game* game, BaseLevelState* level)
	: HUDButton( game, level, ImageAsset_HUD_PlayButton, ImageAsset_HUD_PlayButton_Hover )
{
	inBetweenWaves			= Assets::getInstance()->getImageAsset( ImageAsset_HUD_PlayButton );
	inBetweenWavesHover		= Assets::getInstance()->getImageAsset( ImageAsset_HUD_PlayButton_Hover );
	inWave					= Assets::getInstance()->getImageAsset( ImageAsset_HUD_PlayButton_InWave );
	inWaveHover				= Assets::getInstance()->getImageAsset( ImageAsset_HUD_PlayButton_InWaveHover );
	fastForward				= Assets::getInstance()->getImageAsset( ImageAsset_HUD_PlayButton_FastForward );
	fastForwardHover		= Assets::getInstance()->getImageAsset( ImageAsset_HUD_PlayButton_FastForwardHover );

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
			level->changeState( LevelCondition_Start_Wave );
			break;
		case( PlayButton_InWave ) :
			setState( PlayButton_FastForward );
			game->setFastForward( true );
			break;
		case( PlayButton_FastForward ) :
			setState( PlayButton_InWave );
			game->setFastForward( false );
			break;
	}
}