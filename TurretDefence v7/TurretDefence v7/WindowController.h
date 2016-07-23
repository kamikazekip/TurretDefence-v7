#pragma once
#include "SDL.h"

class WindowController
{
private:
	SDL_Window* window;
	SDL_Renderer* renderTarget;

	void init();
	/* Singleton */
	WindowController();
	WindowController( WindowController const& );
	~WindowController();
public:
	/* Singleton */
	static WindowController* getInstance();

	SDL_Renderer* getRenderTarget();
	SDL_Window* getWindow();
	void setResolution( int resX, int resY );
	void setFullScreen( bool fs );

	int width, height;
	Uint32 flags;
};

