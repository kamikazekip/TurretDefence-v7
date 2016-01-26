#include "WindowController.h"
#include "Assets.h"

WindowController::WindowController()
{
	width = 1600;
	height = 900;
	flags = SDL_WINDOW_SHOWN;

	window = SDL_CreateWindow( "TurretDefence v7!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags );
	SDL_SetWindowIcon( window, Assets::getInstance()->getIcon() );
}


WindowController::~WindowController()
{
	SDL_DestroyWindow( window );
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