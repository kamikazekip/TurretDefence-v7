#pragma once
#include "Sprite.h"
#include <string>

class MenuItem
{
private:
	SDL_Renderer* renderTarget;
	Sprite* currentSprite;
	Sprite* normalSprite;
	Sprite* selectedSprite;
	TTF_Font* font;
	SDL_Color color;
	SDL_Color selectedColor;
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
	void setText( std::string text );
};

