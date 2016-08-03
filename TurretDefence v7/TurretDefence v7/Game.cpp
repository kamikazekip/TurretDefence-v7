#include "Game.h"
#include "Input.h"
#include "WindowController.h"
#include "MainMenu.h"
#include "Assets.h"
#include "LoopHandler.h"
#include "LevelFactory.h"
#include "HUD.h"
#include "Camera.h"
#include "BaseLevelState.h"
#include "AssetLoader.h"

static Game* instance;

Game::Game()
{
	
}

void Game::init()
{
	fastForwarded = false;
	setFPS( 60 );
	gameState = GameState::In_Game;
	windowController = WindowController::getInstance();
	renderTarget = windowController->getRenderTarget();
	camera = new Camera( windowController->width, windowController->height, windowController->width, windowController->height );
	assetLoader = new AssetLoader();
	input = Input::getInstance();
	mainMenu = new MainMenu();
	levelFactory = new LevelFactory();
	currentLevel = levelFactory->getStartLevel();

	setLoopHandler( currentLevel );
	gameLoop();
}

/* Singleton */
Game* Game::getInstance()
{
	if( !instance )
	{
		instance = new Game();
		instance->init();
	}
	return instance;
}

Game::~Game()
{
	delete levelFactory; levelFactory = nullptr;
	delete assetLoader; assetLoader = nullptr;
	delete camera;		camera = nullptr;
	delete mainMenu;	mainMenu = nullptr;
	Input_Quit();		input = nullptr;
}

void Game::gameLoop()
{
	prevTime = 0;
	currentTime = SDL_GetTicks();
	deltaTime = 0.0f;
	while( gameState != GameState::Quitting )
	{
		updateDeltaTime();
		input->update();

		SDL_RenderClear( renderTarget );
		if( fastForwarded )
			loopHandler->tick( getFastForwardDeltaTime() );
		else 
			loopHandler->tick( getDeltaTime() );

		/* DEBUG DRAW A LINE AT A LOCATION
		SDL_SetRenderDrawColor( renderTarget, 255, 0, 0, 255 );
		SDL_RenderDrawLine( renderTarget, 0, 193.5, WindowController::getInstance()->width, 193.5 );
		SDL_RenderDrawLine( renderTarget, 0, 212, WindowController::getInstance()->width, 212 );
		*/

		SDL_SetRenderDrawColor( renderTarget, 0, 0, 0, 255 );
		SDL_RenderPresent( renderTarget );

		capFramesPerSecond();
	}
}

float Game::getDeltaTime()
{
	return deltaTime;
}

float Game::getFastForwardDeltaTime()
{
	return deltaTime * 2;
}

bool Game::getFastForwarded()
{
	return fastForwarded;
}

void Game::setGameState( GameState gameState )
{
	this->gameState = gameState;
	switch( gameState )
	{
		case ( GameState::In_Game ) :
			setLoopHandler( currentLevel );
			break;
		case ( GameState::Preloading ) :
			setLoopHandler( assetLoader );
			break;
	}
}

void Game::setLoopHandler( LoopHandler* loopHandler )
{
	this->loopHandler = loopHandler;
	input->setLoopHandler( this->loopHandler );
	this->loopHandler->firstTick();
}

void Game::updateDeltaTime()
{
	prevTime = currentTime;
	currentTime = SDL_GetTicks();
	deltaTime = (currentTime - prevTime) / 1000.0f;
}

void Game::capFramesPerSecond()
{
	sleepTime = targetSleepTime - ((SDL_GetTicks() - currentTime) / 1000.0f);
	SDL_Delay( Uint32(sleepTime) );
}

void Game::setFPS( float fps )
{
	targetSleepTime = 1000.0f / fps;
}

void Game::setFastForward( bool fastForward )
{
	fastForwarded = fastForward;
}

void Game::togglePause()
{
	loopHandler->togglePause();
}

Camera* Game::getCamera()
{
	return camera;
}

extern __declspec( dllexport ) void Game_Quit()
{
	delete instance; instance = nullptr;
}
