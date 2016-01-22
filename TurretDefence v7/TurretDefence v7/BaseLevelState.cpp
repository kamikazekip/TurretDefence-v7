#include "BaseLevelState.h"
#include "LevelBehaviourFactory.h"
#include "Game.h"
#include "HUD.h"
#include "TurretFactory.h"

BaseLevelState::BaseLevelState( Game* game, Camera* camera )
	: LoopHandler( camera )
{
	this->game = game;
	pausedScreen		= new Sprite( game->getRenderer(), Asset_UI_Paused );
	hud					= new HUD( game, this, game->getWindowWidth(), game->getWindowHeight() );
	behaviourFactory	= new LevelBehaviourFactory( this );
	turretFactory		= new TurretFactory( game->getRenderer() );
	turrets				= new TurretContainer( game->getRenderer(), camera );
	currentBehaviour	= nullptr;

	turrets->addTurret( TurretType_Sniper, 800, 500 );
}


BaseLevelState::~BaseLevelState()
{
	delete background;		background = nullptr;
	delete hud;				hud = nullptr;
	delete waveFactory;		waveFactory = nullptr;
}

void BaseLevelState::update( float deltaTime )
{
	/* Level */
	currentBehaviour->update( deltaTime );

	/* Turrets */
	turrets->update( deltaTime );

}

void BaseLevelState::animate( float deltaTime )
{
	/* Turrets */
	turrets->animate( deltaTime );
}

void BaseLevelState::draw()
{
	/* Background */
	background->drawFullScreen( camera );

	/* Enemies */
	currentWave->draw( camera );

	/* Turrets */
	turrets->draw();

	/* Pause screen */
	if( paused )
		pausedScreen->drawFullScreen( camera );

	/* HUD */
	hud->draw();
}

void BaseLevelState::changeLevel()
{

}

void BaseLevelState::tick( float deltaTime )
{
	if( !paused )
	{
		update( deltaTime );
		animate( deltaTime );
	}
	draw();
}

void BaseLevelState::onQuit()
{
	game->setGameState( GameState::Quitting );
}

void BaseLevelState::onMouseButtonDown( int mouseX, int mouseY )
{
	hud->onMouseButtonDown( mouseX, mouseY );
	turrets->onMouseButtonDown( mouseX, mouseY );
	
	if( paused && !hud->isTouching( mouseX, mouseY ) )
	{
		game->togglePause();
	}
}

void BaseLevelState::onMouseMotion( int mouseX, int mouseY )
{
	hud->onMouseMotion( mouseX, mouseY );
}

void BaseLevelState::setPath( std::vector<SDL_Point> path )
{
	this->path = path;
	waveCounter = 0;
	waveFactory = new WaveFactory(game->getRenderer(), path);
	changeState( LevelCondition_Init );
}

void BaseLevelState::changeState( LevelConditions newCondition )
{
	if( currentBehaviour )
		delete currentBehaviour;
	currentBehaviour = behaviourFactory->createBehaviour( newCondition );
	hud->updateState( newCondition );
}

Wave* BaseLevelState::getWave()
{
	return currentWave;
}

void BaseLevelState::nextWave()
{
	waveCounter++;
	if( waveFactory->canCreateWave( waveCounter ) )
	{
		currentWave = waveFactory->createWave( waveCounter );
	}
	else
	{
		std::cout << "Gewonnen!" << std::endl;
	}
}