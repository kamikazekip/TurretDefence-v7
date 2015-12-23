#include "LoopHandler.h"


LoopHandler::LoopHandler(Camera* camera)
{
	this->camera = camera;
	paused = false;
}


LoopHandler::~LoopHandler()
{

}

void LoopHandler::onQuit()
{

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