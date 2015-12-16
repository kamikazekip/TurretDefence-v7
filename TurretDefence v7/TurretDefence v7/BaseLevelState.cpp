#include "BaseLevelState.h"
#include "Game.h"

BaseLevelState::BaseLevelState( Game* game, Camera* camera )
	: LoopHandler( camera )
{
	this->game = game;
	background = new Sprite( game->getRenderer(), Asset::Asset_BaseLevel_Background );	
	hud = new HUD( game, game->getWindowWidth(), game->getWindowHeight() );
	waveCounter = 1;
	waveFactory = new WaveFactory();
	currentWave = waveFactory->createWave( waveCounter );
}


BaseLevelState::~BaseLevelState()
{
	delete background;		background = nullptr;
	delete hud;				hud = nullptr;
	delete waveFactory;		waveFactory = nullptr;
}

void BaseLevelState::update( float deltaTime )
{

}

void BaseLevelState::animate( float deltaTime )
{

}

void BaseLevelState::draw()
{
	background->drawFullScreen();
	hud->draw();
}

void BaseLevelState::changeLevel()
{

}

void BaseLevelState::tick( float deltaTime )
{
	update( deltaTime );
	animate( deltaTime );
	draw();
}

void BaseLevelState::onQuit()
{
	game->setGameState( GameState::Quitting );
}

void BaseLevelState::onMouseButtonDown( int mouseX, int mouseY )
{
	hud->onMouseButtonDown( mouseX, mouseY );
}

void BaseLevelState::onMouseMotion( int mouseX, int mouseY )
{
	hud->onMouseMotion( mouseX, mouseY );
}