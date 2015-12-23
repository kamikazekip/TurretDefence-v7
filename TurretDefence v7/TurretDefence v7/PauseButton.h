#pragma once
#include "HUDButton.h"

class PauseButton : public HUDButton
{
public:
	PauseButton( Game* game, BaseLevelState* level );
	~PauseButton();
	void onClick();
};

