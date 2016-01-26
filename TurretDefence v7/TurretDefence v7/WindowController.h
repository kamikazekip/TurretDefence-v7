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
	void setResolution( int resX, int resY );
	void setFullScreen( bool fs );

	int width, height;
	Uint32 flags;
	
};

