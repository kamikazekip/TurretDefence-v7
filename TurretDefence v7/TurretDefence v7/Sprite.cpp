#include "Sprite.h"


Sprite::Sprite(SDL_Renderer* renderTarget, Asset asset)
{
	this->renderTarget = renderTarget;
	this->texture = Assets::getInstance()->getAsset( asset );
	SDL_QueryTexture( texture, NULL, NULL, &positionRect.w, &positionRect.h );
	positionRect.x = 0;
	positionRect.y = 0;
}

Sprite::Sprite( SDL_Renderer* renderTarget, TTF_Font* font, std::string text, SDL_Color color)
{
	this->renderTarget = renderTarget;
	this->texture = Assets::getInstance()->getAsset(font, text, color);

	SDL_QueryTexture( texture, NULL, NULL, &positionRect.w, &positionRect.h );
	positionRect.x = 0;
	positionRect.y = 0;
}

Sprite::~Sprite()
{

}

void Sprite::draw()
{
	SDL_RenderCopy( renderTarget, texture, NULL, &positionRect );
}

void Sprite::drawFullScreen()
{
	SDL_RenderCopy( renderTarget, texture, NULL, NULL );
}

void Sprite::setAsset(Asset asset)
{
	this->texture = Assets::getInstance()->getAsset( asset );
	SDL_QueryTexture( texture, NULL, NULL, &positionRect.w, &positionRect.h );
}