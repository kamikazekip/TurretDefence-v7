#pragma once
#include "SDL.h"
#include <iostream>
#include "BaseLevelState.h"

class Input;
class WindowController;
class MainMenu;
class LoopHandler;
class LevelFactory;
class Camera;

enum GameState
{
	Running,
	Paused,
	In_Menu,
	In_Game,
	Quitting
};

class Game
{
private:
	void gameLoop();
	void updateDeltaTime();
	void capFramesPerSecond();

	SDL_Renderer* renderTarget;
	GameState gameState;
	Input* input;
	WindowController* windowController;
	MainMenu* mainMenu;
	LoopHandler* loopHandler;
	Camera* camera;

	LevelFactory* levelFactory;
	BaseLevelState* currentLevel;
	int prevTime;
	int currentTime;
	float deltaTime;
	float targetSleepTime;
	float sleepTime;
public:
	Game();
	~Game();
	void setGameState( GameState gameState );
	void setLoopHandler( LoopHandler* loopHandler );
	
	int getWindowWidth();
	int getWindowHeight();
	void setFPS( float fps );
	SDL_Renderer* getRenderer();
};

