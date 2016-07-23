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
	SDL_SetWindowIcon( window, Assets::getInstance()->getIcon() );
}

WindowController::~WindowController()
{
	SDL_DestroyWindow( window );
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

SDL_Renderer* WindowController::getRenderTarget()
{
	return this->renderTarget;
}

SDL_Window* WindowController::getWindow()
{
	return this->window;
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