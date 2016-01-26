#pragma once
#include "Menu.h"
#include <vector>

struct Resolution
{
	int ResX;
	int ResY;
};

class OptionsMenu : public Menu
{
private:
	LoopHandler* previousHandler;
	Sprite* optionsOverlay;
	MenuItem* backButton;
	TTF_Font* optionsFont;
	SDL_Color white;
	SDL_Color selectedWhite;
	Sprite* resolutionLabel;
	MenuItem* resolutionValue;
	Sprite* fullscreenLabel;
	MenuItem* fullscreenValue;

	std::vector<Resolution> possibleResolutions;
	int currentResolution;
	bool fullscreen;
	enum Choice { Back };
public:
	OptionsMenu( Game* game, LoopHandler* previousHandler );
	~OptionsMenu();
	void firstTick();
	void tick( float deltaTime );
	void draw();
	void onQuit();
	void onMouseMotion( int mouseX, int mouseY );
	void onMouseButtonDown( int mouseX, int mouseY );
	void handleChoice( Choice choice );
	void scale();
	std::string getCurrentResolution();
};

