#include "LoopHandler.h"
#include "Game.h"

LoopHandler::LoopHandler( )
{
	this->camera = Game::getInstance()->getCamera();
	paused = false;
}


LoopHandler::~LoopHandler()
{

}

void LoopHandler::onQuit()
{
	Game::getInstance()->setGameState( GameState::Quitting );
}

void LoopHandler::onMouseMotion( int mouseX, int mouseY )
{

}

void LoopHandler::onMouseButtonDown( int mouseX, int mouseY )
{

}

void LoopHandler::onMouseButtonUp( int mouseX, int mouseY )
{

}

void LoopHandler::onKeyDown( SDL_Keycode keyPressed )
{

}

void LoopHandler::onKeyUp( SDL_Keycode keyPressed )
{

}

void LoopHandler::onEscapeKeyDown()
{

}

void LoopHandler::firstTick()
{

}

void LoopHandler::tick( float deltaTime )
{

}

void LoopHandler::togglePause()
{
	paused = !paused;
}