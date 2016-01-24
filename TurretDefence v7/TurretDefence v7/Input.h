#pragma once
#include "SDL.h"
#include "LoopHandler.h"
#include <map>
#include <vector>

typedef void ( LoopHandler::*key_handling_function )( );
using namespace std;

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
	map<SDL_Keycode, key_handling_function> keyMap;
	map<SDL_Keycode, bool> keyPressedMap;
	vector<SDL_Keycode> multiplePressExceptions;

	/* Functions */
	void handleDownKeys();
	void handleUpKeys( );

	void link( SDL_Keycode, key_handling_function );
	void linkMultiplePress( SDL_Keycode, key_handling_function );

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