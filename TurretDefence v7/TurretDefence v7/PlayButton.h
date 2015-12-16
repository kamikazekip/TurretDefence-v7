#pragma once
#include "Assets.h"
#include "HUDButton.h"
#include <map>
class Game;

class PlayButton : public HUDButton
{
private:
	Game* game;
	enum PlayButtonState { PlayButton_InBetweenWaves, PlayButton_InWave, PlayButton_FastForward };
	PlayButtonState currentState;
	SDL_Texture* inBetweenWaves;
	SDL_Texture* inBetweenWavesHover;
	SDL_Texture* inWave;
	SDL_Texture* inWaveHover;
	SDL_Texture* fastForward;
	SDL_Texture* fastForwardHover;

	std::map<PlayButtonState, SDL_Texture*> textureMap;
	std::map<PlayButtonState, SDL_Texture*> hoverTextureMap;
public:
	PlayButton(Game* game);
	~PlayButton();
	void onClick();
	void setState( PlayButtonState newState );
};