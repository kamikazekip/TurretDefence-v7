#pragma once
#include "Assets.h"
class HUDButton
{
protected:
	SDL_Renderer* renderTarget;
	SDL_Rect positionRect;
	SDL_Texture* currentTexture;
	SDL_Texture* normalTexture;
	SDL_Texture* hoverTexture;
public:
	HUDButton(SDL_Renderer* renderTarget, Asset normal, Asset hover);
	~HUDButton();
	bool checkHover( int mouseX, int mouseY );
	bool isTouching( int mouseX, int mouseY );
	virtual void onClick();
	void draw();
	int getXPosition();
	int getYPosition();
	int getWidth();
	int getHeight();
	void setXPosition( int x );
	void setYPosition( int y );
};

