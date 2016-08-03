#pragma once
#include "SDL.h"

class WindowController
{
private:
	SDL_Window* window;
	SDL_Renderer* renderTarget;

	double gameObjectBoundarySize;
	SDL_Rect gameObjectBoundary;

	void init();
	/* Singleton */
	WindowController();
	WindowController( WindowController const& );
public:
	~WindowController();
	/* Singleton */
	static WindowController* getInstance();

	SDL_Window* getWindow();
	SDL_Renderer* getRenderTarget();
	SDL_Rect getGameObjectBoundary();
	void setResolution( int resX, int resY );
	void setFullScreen( bool fs );

	int width, height;
	Uint32 flags;
};

extern __declspec( dllexport ) void WindowController_Quit();