#include "BaseLevelState.h"
#include "LevelBehaviourFactory.h"
#include "Game.h"
#include "HUD.h"
#include "TurretContainer.h"
#include "WindowController.h"
#include <algorithm>

BaseLevelState::BaseLevelState( )
	: LoopHandler( )
{
	this->game					= Game::getInstance();
	hud							= new HUD( game, this );
	behaviourFactory			= new LevelBehaviourFactory( this );
	currentBehaviour			= nullptr;
	turretFactory				= new TurretFactory();
	
	gameObjects					= new std::vector<GameObject*>();
	gameObjectsRemoveStack		= new std::vector<GameObject*>();
	enemies						= new std::vector<Enemy*>();
	turrets						= new std::vector<Turret*>();
	projectiles					= new std::vector<Projectile*>();

	collisionManager			= CollisionManager::getInstance();
	addTurret( TurretType_Sniper, 700, 220 );
	addTurret( TurretType_Sniper, 300, 400 );
}


BaseLevelState::~BaseLevelState()
{
	
	for( size_t c = 0; c < enemies->size(); c++ )
	{
		gameObjects->erase( std::remove( gameObjects->begin(), gameObjects->end(), enemies->at(c) ), gameObjects->end() );
		delete enemies->at( c ); enemies->at( c ) = nullptr;
	}
	enemies->clear();
	delete enemies; enemies = nullptr;

	for( size_t c = 0; c < projectiles->size(); c++ )
	{
		gameObjects->erase( std::remove( gameObjects->begin(), gameObjects->end(), projectiles->at(c) ), gameObjects->end() );
		delete projectiles->at( c ); projectiles->at( c ) = nullptr;
	}
	projectiles->clear();
	delete projectiles; projectiles = nullptr;

	for( size_t c = 0; c < turrets->size(); c++ )
	{
		gameObjects->erase( std::remove( gameObjects->begin(), gameObjects->end(), turrets->at(c) ), gameObjects->end() );
		delete turrets->at( c ); turrets->at( c ) = nullptr;
	}
	turrets->clear();
	delete turrets; turrets = nullptr;

	shredVector( gameObjects );
	shredVector( gameObjectsRemoveStack );

	delete turretFactory;				turretFactory = nullptr;
	delete currentBehaviour;			currentBehaviour = nullptr;
	delete behaviourFactory;			behaviourFactory = nullptr;
	delete background;					background = nullptr;
	delete hud;							hud = nullptr;
	delete waveFactory;					waveFactory = nullptr;
}

void BaseLevelState::update( float deltaTime )
{
	std::cout << gameObjects->size() << std::endl;
	/* Level */
	currentBehaviour->checkState();
	currentBehaviour->update( deltaTime );

	/* GameObjects */
	for( size_t c = 0; c < gameObjects->size(); c++ )
		gameObjects->at(c)->update( deltaTime );
}

void BaseLevelState::collectGarbage()
{
	/* Enemies */
	for( size_t c = 0; c < enemies->size(); c++ )
	{
		Enemy* enemyToRemove = enemies->at( c );
		if( enemies->at( c )->reachedEnd )
		{	
			//TODO: remove lives
			gameObjectsRemoveStack->push_back( enemyToRemove );
			gameObjects->erase( std::remove( gameObjects->begin(), gameObjects->end(), enemyToRemove ), gameObjects->end() );
			enemies->erase( std::remove( enemies->begin(), enemies->end(), enemyToRemove ), enemies->end() );
		}
		else if( enemies->at( c )->trash )
		{
			
			gameObjectsRemoveStack->push_back( enemyToRemove );
			gameObjects->erase( std::remove( gameObjects->begin(), gameObjects->end(), enemyToRemove ), gameObjects->end() );
			enemies->erase( std::remove( enemies->begin(), enemies->end(), enemyToRemove ), enemies->end() );
		}
	}

	/* Projectiles */
	for( size_t c = 0; c < projectiles->size(); c++ )
	{
		if( projectiles->at( c )->trash )
		{
			Projectile* projectileToRemove = projectiles->at( c );
			gameObjectsRemoveStack->push_back( projectileToRemove );
			gameObjects->erase( std::remove( gameObjects->begin(), gameObjects->end(), projectileToRemove ), gameObjects->end() );
			projectiles->erase( std::remove( projectiles->begin(), projectiles->end(), projectileToRemove ), projectiles->end() );
		}
	}
}

void BaseLevelState::deleteGarbage()
{
	for( size_t i = 0; i < gameObjectsRemoveStack->size(); i++ )
	{
		delete gameObjectsRemoveStack->at( i ); gameObjectsRemoveStack->at( i ) = nullptr;
	}
	gameObjectsRemoveStack->clear();
}

void BaseLevelState::collide()
{
	/* Preparing */
	collisionManager->clear();

	for( size_t c = 0; c < gameObjects->size(); c++ )
		if( gameObjects->at(c)->canCollide() )
			collisionManager->insert( gameObjects->at(c) );

	/* Colliding */
	for( size_t x = 0; x < gameObjects->size(); x++ )
		gameObjects->at(x)->collide();
}

void BaseLevelState::animate( float deltaTime )
{
	/* GameObjects */
	for( size_t c = 0; c < gameObjects->size(); c++ )
		gameObjects->at(c)->animate( deltaTime );
}

void BaseLevelState::draw()
{
	/* Background */
	background->drawFullScreen( camera );

	/* GameObjects */
	for( size_t c = 0; c < gameObjects->size(); c++ )
		gameObjects->at(c)->draw( camera );

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
		collectGarbage();
		deleteGarbage();
		collide();
		animate( deltaTime );
	}
	draw();
}

void BaseLevelState::onMouseButtonDown( int mouseX, int mouseY )
{
	if( !hud->onMouseButtonDown( mouseX, mouseY ) )
		for( size_t c = 0; c < gameObjects->size(); c++ )		//TODO: Optimize by not checking all of the gameobjects, but only the ones in that quadrant.
			gameObjects->at(c)->onMouseButtonDown( mouseX, mouseY );
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

std::vector<SDL_Point> BaseLevelState::getPath()
{
	return path;
}

void BaseLevelState::setPath( std::vector<SDL_Point> path )
{
	this->path = path;
	waveCounter = 0;
	waveFactory = new WaveFactory( this );
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
		currentWave = waveFactory->createWave( waveCounter );
	else
		std::cout << "Gewonnen!" << std::endl;
}

void BaseLevelState::addProjectile( Projectile* projectile )
{
	gameObjects->push_back( projectile );
	projectiles->push_back( projectile );
}

void BaseLevelState::addTurret( TurretType turretType, double x, double y )
{
	Turret* turret = turretFactory->createTurret( turretType, x, y );
	turret->setLevel( this );
	gameObjects->push_back( turret );
	turrets->push_back( turret );
}

void BaseLevelState::addEnemy( Enemy* enemy )
{
	gameObjects->push_back( enemy );
	enemies->push_back( enemy );
}

void BaseLevelState::shredVector( std::vector<GameObject*>* vector )
{
	for( size_t c = 0; c < vector->size(); c++ )
	{
		delete vector->at( c ); vector->at( c ) = nullptr;
	}
	vector->clear();
	delete vector; vector = nullptr;
}