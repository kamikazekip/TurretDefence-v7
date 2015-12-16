#include "MainMenu.h"
#include "Assets.h"

MainMenu::MainMenu( SDL_Renderer* renderTarget, Game* game, Camera* camera )
	: Menu( renderTarget, game, camera )
{
	std::string fontPath = assetBasePath + "Fonts/action_jackson.ttf";
	mainTitleFont = TTF_OpenFont( fontPath.c_str(), 140 );
	
	mainTitle = new Sprite( renderTarget, mainTitleFont, "TurretDefence!", menuFontColor );
	mainTitle->positionRect.x = (game->getWindowWidth() - mainTitle->positionRect.w ) / 2;
	mainTitle->positionRect.y = 50;

	background = new Sprite( renderTarget, Asset::Asset_MainMenu_Background );

	addMenuItem( "Play" );
	addMenuItem( "Options" );
	addMenuItem( "Exit" );
}


MainMenu::~MainMenu()
{

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

void MainMenu::onQuit()
{
	game->setGameState( GameState::Quitting );
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
		case ( Choice::Play ) :
			game->setGameState( GameState::In_Game );
	}
}