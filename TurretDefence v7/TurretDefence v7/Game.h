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
class AssetLoader;

enum GameState
{
	Preloading,
	Running,
	In_Menu,
	In_Game,
	Quitting
};

class Game
{
private:
	void init();
	void gameLoop();
	void updateDeltaTime();
	void capFramesPerSecond();
	bool fastForwarded;

	SDL_Renderer* renderTarget;
	GameState gameState;
	Input* input;
	WindowController* windowController;
	MainMenu* mainMenu;
	LoopHandler* loopHandler;
	Camera* camera;

	AssetLoader* assetLoader;
	LevelFactory* levelFactory;
	BaseLevelState* currentLevel;
	int prevTime;
	int currentTime;
	float deltaTime;
	float fastForwardDeltaTime;
	float targetSleepTime;
	float sleepTime;

	/* Singleton */
	Game();
	Game( Game const& );
public:
	~Game();

	/* Singleton */
	static Game* getInstance();

	float getDeltaTime();
	float getFastForwardDeltaTime();
	bool getFastForwarded();
	void setGameState( GameState gameState );
	void setLoopHandler( LoopHandler* loopHandler );
	void setFPS( float fps );
	void setFastForward(bool fastForward);
	void togglePause();
	Camera* getCamera();
};

/**
This function cleans up the entire sound system. You should call it upon all exit conditions.
*/
extern __declspec( dllexport ) void Game_Quit();