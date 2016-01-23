#pragma once
#include "SDL.h"
#include "LoopHandler.h"
#include <map>

typedef void ( LoopHandler::*key_handling_function )( );

class Input
{

private:
	/* Singleton */
	Input();
	Input( Input const& );
	void operator=(Input const&);

	/* Variables */
	LoopHandler* loopHandler;
	int mouseX;
	int mouseY;
	SDL_Keycode keyPressed;
	std::map<SDL_Keycode, key_handling_function> keyMap;

	/* Functions */
	void handleKeys();

public:
	/* Singleton */
	static Input* getInstance();
	~Input();

	/* Functions */
	void update();
	void setLoopHandler( LoopHandler* loopHandler );

	/* Variables */
	SDL_Event event;
	
};

/**
This function cleans up the entire sound system. You should call it upon all exit conditions.
*/
extern __declspec(dllexport) void Input_Quit();