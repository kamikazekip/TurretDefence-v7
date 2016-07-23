#include "BaseLevelState.h"
#include "LevelBehaviourFactory.h"
#include "Game.h"
#include "HUD.h"
#include "TurretContainer.h"
#include "WindowController.h"

BaseLevelState::BaseLevelState( )
	: LoopHandler( )
{
	this->game = Game::getInstance();
	hud					= new HUD( game, this );
	behaviourFactory	= new LevelBehaviourFactory( this );
	currentBehaviour	= nullptr;

	collisionManager	= new CollisionManager();
	turrets = new TurretContainer( this, camera, collisionManager );
	turrets->addTurret( TurretType_Sniper, 360, 420 );
	projectiles = new std::vector<Projectile*>();
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

	/* Projectiles */
	for( Projectile* projectile : *projectiles )
		projectile->update( deltaTime );

	/* Turrets */
	turrets->update( deltaTime );
}

void BaseLevelState::collide()
{
	collisionManager->clear();
	for( Enemy* enemy : *enemies )
		collisionManager->insert( enemy );
	for( Projectile* projectile : *projectiles )
		collisionManager->insert( projectile );
}

void BaseLevelState::animate( float deltaTime )
{
	/* Turrets */
	turrets->animate( deltaTime );

	for( Projectile* projectile : *projectiles )
		projectile->animate( deltaTime );
}

void BaseLevelState::draw()
{
	/* Background */
	background->drawFullScreen( camera );

	/* Enemies */
	currentWave->draw( camera );

	/* Turrets */
	turrets->draw();

	/* Projectiles */
	for( Projectile* projectile : *projectiles )
		projectile->draw( camera );

	/* Collision grid */
	collisionManager->draw();

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
		collide();
		animate( deltaTime );
	}
	draw();
}

void BaseLevelState::onMouseButtonDown( int mouseX, int mouseY )
{
	if( !hud->onMouseButtonDown( mouseX, mouseY ) )
		turrets->onMouseButtonDown( mouseX, mouseY );
	if( paused && !hud->isTouching( mouseX, mouseY ) )
		game->togglePause();
}

void BaseLevelState::onMouseMotion( int mouseX, int mouseY )
{
	hud->onMouseMotion( mouseX, mouseY );
}

void BaseLevelState::onEscapeKeyDown()
{
	hud->onEscapeKeyDown();
}

void BaseLevelState::setPath( std::vector<SDL_Point> path )
{
	this->path = path;
	waveCounter = 0;
	waveFactory = new WaveFactory(path);
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
		enemies = currentWave->getEnemies();
	}
	else
		std::cout << "Gewonnen!" << std::endl;
}

void BaseLevelState::addProjectile( Projectile* projectile )
{
	projectiles->push_back( projectile );
}