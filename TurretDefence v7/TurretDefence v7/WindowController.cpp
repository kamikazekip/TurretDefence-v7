#include "WindowController.h"
#include "Assets.h"

static WindowController* instance;

WindowController::WindowController()
{
	
}

void WindowController::init()
{
	width = 1366;
	height = 768;
	flags = SDL_WINDOW_SHOWN;

	window = SDL_CreateWindow( "TurretDefence v7!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags );
	renderTarget = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	gameObjectBoundarySize = 200;
	gameObjectBoundary = { 0 - gameObjectBoundarySize, 0 - gameObjectBoundarySize, width + ( 2 * gameObjectBoundarySize ), height + ( 2 * gameObjectBoundarySize ) };
	SDL_SetWindowIcon( window, Assets::getInstance()->getIcon() );
}

WindowController::~WindowController()
{
	SDL_DestroyRenderer( renderTarget );		renderTarget = nullptr;
	SDL_DestroyWindow( window );				window = nullptr;
}

/* Singleton */
WindowController* WindowController::getInstance()
{
	if( !instance )
	{
		instance = new WindowController();
		instance->init();
	}

	return instance;
}

SDL_Window* WindowController::getWindow()
{
	return this->window;
}

SDL_Renderer* WindowController::getRenderTarget()
{
	return this->renderTarget;
}

SDL_Rect WindowController::getGameObjectBoundary()
{
	return this->gameObjectBoundary;
}

void WindowController::setResolution( int resX, int resY )
{
	SDL_SetWindowSize( window, resX, resY );
}

void WindowController::setFullScreen( bool fs )
{
	Uint32 flags = 0;
	if( fs )
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	SDL_SetWindowFullscreen( window, flags );
}

extern __declspec( dllexport ) void WindowController_Quit()
{
	delete instance; instance = nullptr;
}