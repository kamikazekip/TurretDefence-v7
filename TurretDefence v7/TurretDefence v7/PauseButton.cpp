#include "PauseButton.h"
#include "Game.h"

PauseButton::PauseButton( Game* game, BaseLevelState* level )
	: HUDButton(game, level, Asset_HUD_PauseButton, Asset_HUD_PauseButton_Hover )
{

}


PauseButton::~PauseButton()
{

}

void PauseButton::onClick()
{
	game->togglePause();
}
