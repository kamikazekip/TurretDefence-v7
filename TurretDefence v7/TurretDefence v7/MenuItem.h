#pragma once
#include "Sprite.h"
#include <string>

class MenuItem
{
private:
	Sprite* currentSprite;
	Sprite* normalSprite;
	Sprite* selectedSprite;
public:
	MenuItem( SDL_Renderer* renderTarget, TTF_Font* font, std::string text, SDL_Color color, SDL_Color selectedColor );
	~MenuItem();

	bool checkHover(int mouseX, int mouseY);
	bool isTouching(int mouseX, int mouseY);
	int getWidth();
	int getHeight();
	void setXPosition( int x );
	void setYPosition( int y );
	void draw();
};

