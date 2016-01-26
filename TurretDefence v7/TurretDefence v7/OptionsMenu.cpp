#include "OptionsMenu.h"
#include "Input.h"

OptionsMenu::OptionsMenu( Game* game, LoopHandler* previousHandler )
	: Menu( game )
{
	this->previousHandler = previousHandler;
	optionsOverlay = new Sprite( renderTarget, Asset_OptionsMenu_Overlay );
	optionsOverlay->positionRect.h = camera->windowHeight;
	optionsOverlay->positionRect.w = camera->windowWidth;

	backButton = new MenuItem( renderTarget, menuItemFont, "Back", menuFontColor, menuFontColorSelected );
	backButton->setXPosition(40);
	backButton->setYPosition( camera->windowHeight - backButton->getHeight() - 20 );

	menuItems->push_back( backButton );
	white = { 255, 255, 255, 255 };				/* White */
	selectedWhite = { 233, 233, 233, 255 };		/* Selected White */

	possibleResolutions.push_back( Resolution{ 1280, 720 } );
	possibleResolutions.push_back( Resolution{ 1360, 768 } );
	possibleResolutions.push_back( Resolution{ 1366, 768 } );
	possibleResolutions.push_back( Resolution{ 1440, 900 } );
	possibleResolutions.push_back( Resolution{ 1600, 900 } );
	possibleResolutions.push_back( Resolution{ 1680, 1050 } );
	possibleResolutions.push_back( Resolution{ 1920, 1080 } );
	currentResolution = 0;

	optionsFont = nullptr;
	resolutionLabel = nullptr;
	resolutionValue = nullptr;
	fullscreenLabel = nullptr;
	fullscreenValue = nullptr;
	fullscreen = false;
	scale();
}


OptionsMenu::~OptionsMenu()
{

}

void OptionsMenu::firstTick()
{
	int x;
	int y;
	SDL_GetMouseState( &x, &y );
	Menu::checkHover( x, y );
}

void OptionsMenu::tick( float deltaTime )
{
	draw();
}

void OptionsMenu::draw()
{
	optionsOverlay->draw();
	drawMenuItems();
	resolutionLabel->draw();
	resolutionValue->draw();
	fullscreenLabel->draw();
	fullscreenValue->draw();
}

void OptionsMenu::onQuit()
{
	game->setGameState( GameState::Quitting );
}

void OptionsMenu::onMouseMotion( int mouseX, int mouseY )
{
	resolutionValue->checkHover( mouseX, mouseY );
	fullscreenValue->checkHover( mouseX, mouseY );
}

void OptionsMenu::onMouseButtonDown( int mouseX, int mouseY )
{
	for( size_t c = 0; c < menuItems->size(); c++ )
	{
		if( menuItems->at( c )->isTouching( mouseX, mouseY ) )
		{
			handleChoice( static_cast<Choice>( c ) );
		}
	}
	if( resolutionValue->isTouching( mouseX, mouseY ) )
	{
		currentResolution++;
		if( currentResolution == possibleResolutions.size() )
			currentResolution = 0;
		scale();
	}
	if( fullscreenValue->isTouching( mouseX, mouseY ) )
	{
		fullscreen = !fullscreen;
		scale();
	}
}

void OptionsMenu::handleChoice( Choice choice )
{
	switch( choice )
	{
		case ( Back ) :
			game->setLoopHandler( previousHandler );
			break;
	}
}

void OptionsMenu::scale()
{
	if( optionsFont )
		TTF_CloseFont( optionsFont );	optionsFont = nullptr;
	if( resolutionLabel )
		delete resolutionLabel; resolutionLabel = nullptr;
	if( resolutionValue )
		delete resolutionValue; resolutionValue = nullptr;
	if( fullscreenLabel )
		delete fullscreenLabel; fullscreenLabel = nullptr;
	if( fullscreenValue )
		delete fullscreenValue; fullscreenValue = nullptr;

	optionsFont = TTF_OpenFont( action_jackson.c_str(), int(camera->windowWidth * 0.028125f) );

	resolutionLabel = new Sprite( renderTarget, optionsFont, "Resolution", menuFontColor );
	resolutionLabel->positionRect.x = int(camera->windowWidth * 0.046875f);
	resolutionLabel->positionRect.y = int(camera->windowHeight * 0.3703703703703704f);

	resolutionValue = new MenuItem(renderTarget, optionsFont, getCurrentResolution(), white, selectedWhite );
	int xPos = resolutionLabel->positionRect.x + resolutionLabel->positionRect.w + int( camera->windowWidth * 0.03125f );
	resolutionValue->setXPosition(xPos);
	resolutionValue->setYPosition( resolutionLabel->positionRect.y );

	fullscreenLabel = new Sprite( renderTarget, optionsFont, "Fullscreen", menuFontColor );
	fullscreenLabel->positionRect.x = int( camera->windowWidth * 0.046875f );
	fullscreenLabel->positionRect.y = int( camera->windowHeight * 0.48148148148148145f );

	std::string fs = "No";
	if( fullscreen )
		fs = "Yes";

	fullscreenValue = new MenuItem( renderTarget, optionsFont, fs, white, selectedWhite );
	int xPosFS = resolutionLabel->positionRect.x + resolutionLabel->positionRect.w + int( camera->windowWidth * 0.03125f );
	fullscreenValue->setXPosition( xPosFS );
	fullscreenValue->setYPosition( fullscreenLabel->positionRect.y );
}

std::string OptionsMenu::getCurrentResolution()
{
	return to_string( possibleResolutions[currentResolution].ResX ) + " x " + to_string( possibleResolutions[currentResolution].ResY );
}