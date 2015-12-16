#pragma once
class BaseLevelState;
class Wood;
class Game;
class Camera;

class LevelFactory
{
private:
	Game* game;
	Camera* camera;
public:
	LevelFactory(Game* game, Camera* camera);
	~LevelFactory();

	BaseLevelState* getStartLevel();
};

