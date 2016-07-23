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
	Sprite( ImageAsset asset );
	Sprite( FontAsset font, std::string text, SDL_Color color );
	Sprite( TTF_Font* font, std::string text, SDL_Color color );
	~Sprite();

	void draw();
	void draw( Camera* camera );
	void drawFullScreen( Camera* camera );

	void setImageAsset( ImageAsset asset );

	SDL_Rect positionRect;
};

