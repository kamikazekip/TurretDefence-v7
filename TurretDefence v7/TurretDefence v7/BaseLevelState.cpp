#include "BaseLevelState.h"
#include "LevelBehaviourFactory.h"
#include "Game.h"

BaseLevelState::BaseLevelState( Game* game, Camera* camera )
	: LoopHandler( camera )
{
	this->game = game;
	background = new Sprite( game->getRenderer(), Asset::Asset_BaseLevel_Background );	
	hud = new HUD( game, this, game->getWindowWidth(), game->getWindowHeight() );
	behaviourFactory = new LevelBehaviourFactory( this );
	currentBehaviour = behaviourFactory->createBehaviour( LevelCondition_Init );
}


BaseLevelState::~BaseLevelState()
{
	delete background;		background = nullptr;
	delete hud;				hud = nullptr;
	delete waveFactory;		waveFactory = nullptr;
}

void BaseLevelState::update( float deltaTime )
{
	currentBehaviour->update( deltaTime );
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

void BaseLevelState::setPath( std::vector<SDL_Point> path )
{
	this->path = path;
	waveCounter = 1;
	waveFactory = new WaveFactory(path);
	currentWave = waveFactory->createWave( waveCounter );
}

void BaseLevelState::changeState( LevelConditions newCondition )
{
	delete currentBehaviour;
	currentBehaviour = behaviourFactory->createBehaviour( newCondition );
}