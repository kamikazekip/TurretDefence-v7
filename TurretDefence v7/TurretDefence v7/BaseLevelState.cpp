#include "BaseLevelState.h"
#include "LevelBehaviourFactory.h"
#include "Game.h"
#include "HUD.h"
#include "TurretFactory.h"

BaseLevelState::BaseLevelState( Game* game, Camera* camera )
	: LoopHandler( camera )
{
	this->game = game;
	background			= new Sprite( game->getRenderer(), Asset_BaseLevel_Background );	
	pausedScreen		= new Sprite( game->getRenderer(), Asset_UI_Paused );
	hud					= new HUD( game, this, game->getWindowWidth(), game->getWindowHeight() );
	behaviourFactory	= new LevelBehaviourFactory( this );
	turretFactory		= new TurretFactory( game->getRenderer() );
	turrets				= new std::vector<Turret*>();
	currentBehaviour	= nullptr;

	turrets->push_back( turretFactory->createTurret( TurretType_Soldier, 250, 700 ) );
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
	/* Background */
	background->drawFullScreen( camera );

	/* Enemies */
	currentWave->draw( camera );

	/* Turrets */
	for( size_t c = 0; c < turrets->size(); c++ )
		turrets->at( c )->draw( camera );

	/* Pause screen */
	if( paused )
	{
		pausedScreen->drawFullScreen( camera );
	}

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