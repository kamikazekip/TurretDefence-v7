#pragma once
#include "SDL.h"

class WindowController
{
private:
	SDL_Window* window;
public:
	WindowController();
	~WindowController();
	SDL_Window* getWindow();

	int width, height;
	Uint32 flags;
};

