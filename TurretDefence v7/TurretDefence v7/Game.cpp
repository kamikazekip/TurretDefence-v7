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

Game::Game()
{
	fastForwarded = false;
	setFPS( 60 );
	gameState = GameState::In_Game;

	windowController = new WindowController();
	renderTarget = SDL_CreateRenderer( windowController->getWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	camera = new Camera( getWindowWidth(), getWindowHeight(), getWindowWidth(), getWindowHeight() );
	Assets::getInstance()->setRenderTarget( renderTarget );
	input = Input::getInstance();
	mainMenu = new MainMenu( this );
	levelFactory = new LevelFactory( this, camera );
	currentLevel = levelFactory->getStartLevel();

	setLoopHandler( mainMenu );

	gameLoop();
}

Game::~Game()
{
	delete mainMenu;							mainMenu = nullptr;
	Input_Quit();								input = nullptr;
	SDL_DestroyRenderer( renderTarget );		renderTarget = nullptr;
	delete windowController;					windowController = nullptr;
}

void Game::gameLoop()
{
	prevTime = 0;
	currentTime = SDL_GetTicks( ) - 17; /* <-- forged first deltatime, comes in at about 0.017s */
	deltaTime = 0.0f;
	while( gameState != GameState::Quitting )
	{
		updateDeltaTime();
		input->update();

		SDL_RenderClear( renderTarget );
	    loopHandler->tick( deltaTime );
		SDL_RenderPresent( renderTarget );

		capFramesPerSecond();
	}
}

void Game::setGameState( GameState gameState )
{
	this->gameState = gameState;
	switch( gameState )
	{
		case( GameState::In_Game ) :
			setLoopHandler( currentLevel );
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
	if( fastForwarded )
		deltaTime *= 2;
}

void Game::capFramesPerSecond()
{
	sleepTime = targetSleepTime - ((SDL_GetTicks() - currentTime) / 1000.0f);
	SDL_Delay( Uint32(sleepTime) );
}

int Game::getWindowWidth()
{
	return windowController->width;
}

int Game::getWindowHeight()
{
	return windowController->height;
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

SDL_Renderer* Game::getRenderer()
{
	return renderTarget;
}

Camera* Game::getCamera()
{
	return camera;
}

WindowController* Game::getWindowController()
{
	return windowController;
}