#include "HUD.h"
#include "BaseLevelState.h"
#include "Game.h"
#include "BaseLevelState.h"

HUD::HUD(Game* game, BaseLevelState* level, int windowWidth, int windowHeight )
{
	this->game = game;
	this->level = level;
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	buttons = new std::vector<HUDButton*>();
	playButton = new PlayButton( this->game, this->level );
	pauseButton = new PauseButton( this->game, this->level );
	buttons->push_back( playButton );
	buttons->push_back( pauseButton );

	rightMargin = 20;
	positionButtons();
}


HUD::~HUD()
{
	for( size_t c = 0; c < buttons->size(); c++ )
	{
		delete buttons->at( c );	 buttons->at( c ) = nullptr;
	}
	delete buttons;			buttons = nullptr;
}

void HUD::setWindowDimension( int windowWidth, int windowHeight )
{
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	positionButtons();
}

void HUD::positionButtons()
{
	int x = windowWidth - rightMargin;
	playButton->setXPosition( x - playButton->getWidth() );
	playButton->setYPosition( 20 );
	pauseButton->setXPosition( x - pauseButton->getWidth() );
	pauseButton->setYPosition( playButton->getYPosition() + playButton->getHeight() + 20 );
}

void HUD::onMouseButtonDown( int mouseX, int mouseY )
{
	for( size_t c = 0; c < buttons->size(); c++ )
	{
		if( buttons->at( c )->isTouching( mouseX, mouseY ) )
		{
			buttons->at( c )->onClick();
			buttons->at( c )->checkHover( mouseX, mouseY );
		}	
	}
}

void HUD::onMouseMotion( int mouseX, int mouseY )
{
	for( size_t c = 0; c < buttons->size(); c++ )
	{
		buttons->at( c )->checkHover( mouseX, mouseY );
	}
}

void HUD::animate( float deltaTime )
{

}

void HUD::draw()
{
	for( size_t c = 0; c < buttons->size(); c++ )
	{
		buttons->at( c )->draw();
	}
}