#include "WindowController.h"


WindowController::WindowController()
{
	width = 1600;
	height = 900;
	flags = SDL_WINDOW_SHOWN;

	window = SDL_CreateWindow( "TurretDefence v7!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags );
}


WindowController::~WindowController()
{
	SDL_DestroyWindow( window );
}

SDL_Window* WindowController::getWindow()
{
	return this->window;
}