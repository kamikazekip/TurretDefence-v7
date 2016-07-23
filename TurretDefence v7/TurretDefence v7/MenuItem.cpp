#include "MenuItem.h"


MenuItem::MenuItem( FontAsset font, std::string text, SDL_Color color, SDL_Color selectedColor )
{
	this->font = Assets::getInstance()->getFont(font);
	commonInit( text, color, selectedColor );
}

MenuItem::MenuItem( TTF_Font* font, std::string text, SDL_Color color, SDL_Color selectedColor )
{
	this->font = font;
	commonInit( text, color, selectedColor );
}

void MenuItem::commonInit( std::string text, SDL_Color color, SDL_Color selectedColor )
{
	this->renderTarget = renderTarget;
	this->color = color;
	this->selectedColor = selectedColor;
	normalSprite = new Sprite( font, text, color );
	selectedSprite = new Sprite( font, text, selectedColor );
	currentSprite = normalSprite;
}

MenuItem::~MenuItem()
{
	delete normalSprite;		normalSprite = nullptr;
	delete selectedSprite;		selectedSprite = nullptr;
}

bool MenuItem::isTouching( int mouseX, int mouseY )
{
	int x = currentSprite->positionRect.x;
	int y = currentSprite->positionRect.y;
	int w = currentSprite->positionRect.w;
	int h = currentSprite->positionRect.h;
	return (mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h);
}

bool MenuItem::checkHover( int mouseX, int mouseY )
{

	if( isTouching( mouseX, mouseY ) )
	{
		currentSprite = selectedSprite;
		return true;
	}
	else if( currentSprite = selectedSprite )
	{
		currentSprite = normalSprite;
	}
	return false;
}

int MenuItem::getWidth()
{
	return currentSprite->positionRect.w;
}

int MenuItem::getHeight()
{
	return currentSprite->positionRect.h;
}

void MenuItem::setXPosition( int x )
{
	normalSprite->positionRect.x = x;
	selectedSprite->positionRect.x = x;
}

void MenuItem::setYPosition( int y )
{
	normalSprite->positionRect.y = y;
	selectedSprite->positionRect.y = y;
}

void MenuItem::draw()
{
	currentSprite->draw();
}

void MenuItem::setText( std::string text )
{
	delete normalSprite;
	delete selectedSprite;

	normalSprite = new Sprite( font, text, color );
	selectedSprite = new Sprite( font, text, selectedColor );
	currentSprite = normalSprite;
}