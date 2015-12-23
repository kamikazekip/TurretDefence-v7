#pragma once
#include "SDL.h"
#include "Assets.h"
#include "SDL_ttf.h"
#include <string>
#include "Camera.h"

class Sprite
{
private:
	SDL_Texture* texture;
	SDL_Renderer* renderTarget;
public:
	Sprite( SDL_Renderer* renderTarget, Asset asset );
	Sprite( SDL_Renderer* renderTarget, TTF_Font* font, std::string text, SDL_Color color );
	~Sprite();

	void draw();
	void draw( Camera* camera );
	void drawFullScreen( Camera* camera );

	void setAsset( Asset asset );

	SDL_Rect positionRect;
};

