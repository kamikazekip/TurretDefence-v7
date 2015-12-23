#pragma once
#include "SDL.h"
class Camera
{
public:
	int levelWidth, levelHeight, x, y, w, h;
	SDL_Rect cameraRect;
	Camera(int windowWidth, int windowHeight, int levelWidth, int levelHeight);
	~Camera();

};

