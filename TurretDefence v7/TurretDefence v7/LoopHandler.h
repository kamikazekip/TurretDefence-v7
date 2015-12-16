#pragma once
#include "SDL.h"
#include "Camera.h"
class LoopHandler
{
protected:
	Camera* camera;
public:
	LoopHandler(Camera* camera);
	~LoopHandler();
	virtual void onQuit();
	virtual void onMouseMotion( int mouseX, int mouseY );
	virtual void onMouseButtonDown( int mouseX, int mouseY );
	virtual void onMouseButtonUp( int mouseX, int mouseY );
	virtual void onKeyDown( SDL_Keycode keyPressed );
	virtual void onKeyUp( SDL_Keycode keyPressed );
	virtual void firstTick();
	virtual void tick( float deltaTime );
};