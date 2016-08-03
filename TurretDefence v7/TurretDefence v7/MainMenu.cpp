#include "MainMenu.h"
#include "Assets.h"
#include "Game.h"

MainMenu::MainMenu( )
	: Menu( )
{
	mainTitle = new Sprite( FontAsset_TitleFont, "TurretDefence!", menuFontColor );
	mainTitle->positionRect.x = (windowWidth - mainTitle->positionRect.w ) / 2;
	mainTitle->positionRect.y = 50;

	addMenuItem( "Play" );
	addMenuItem( "Options" );
	addMenuItem( "Exit" );

	optionsMenu = new OptionsMenu( this );
}


MainMenu::~MainMenu()
{
	delete mainTitle; mainTitle = nullptr;
	delete optionsMenu; optionsMenu = nullptr;
}

void MainMenu::firstTick()
{
	centerMenuItems();
}

void MainMenu::tick( float deltaTime )
{
	draw();
}

void MainMenu::draw()
{
	version->draw();
	mainTitle->draw();
	drawMenuItems();
}

void MainMenu::onMouseMotion( int mouseX, int mouseY )
{
	checkHover( mouseX, mouseY );
}

void MainMenu::onMouseButtonDown( int mouseX, int mouseY )
{
	for( size_t c = 0; c < menuItems->size(); c++ )
	{
		if( menuItems->at( c )->isTouching( mouseX, mouseY ) )
		{
			handleChoice( static_cast<Choice>(c) );
		}
	}
}

void MainMenu::handleChoice( Choice choice )
{
	switch( choice )
	{
		case (Choice::Exit) :
			onQuit();
			break;
		case( Choice::Options ) :
			game->setLoopHandler( optionsMenu );
			break;
		case ( Choice::Play ) :
			game->setGameState( GameState::In_Game );
			break;
	}
}