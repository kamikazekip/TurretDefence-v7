#include "Sprite.h"
#include "WindowController.h"

Sprite::Sprite( ImageAsset asset )
{
	this->renderTarget = WindowController::getInstance()->getRenderTarget();
	this->texture = Assets::getInstance()->getImageAsset( asset );
	SDL_QueryTexture( texture, NULL, NULL, &positionRect.w, &positionRect.h );
	positionRect.x = 0;
	positionRect.y = 0;
}

Sprite::Sprite( FontAsset font, std::string text, SDL_Color color)
{
	this->renderTarget = WindowController::getInstance()->getRenderTarget();
	this->texture = Assets::getInstance()->getText(font, text, color);

	SDL_QueryTexture( texture, NULL, NULL, &positionRect.w, &positionRect.h );
	positionRect.x = 0;
	positionRect.y = 0;
}

Sprite::Sprite( TTF_Font* font, std::string text, SDL_Color color )
{
	this->renderTarget = WindowController::getInstance()->getRenderTarget();
	this->texture = Assets::getInstance()->getText( font, text, color );

	SDL_QueryTexture( texture, NULL, NULL, &positionRect.w, &positionRect.h );
	positionRect.x = 0;
	positionRect.y = 0;
}


Sprite::~Sprite()
{

}

void Sprite::draw( Camera* camera )
{
	SDL_Rect drawingRect = { positionRect.x - camera->x, positionRect.y - camera->y, positionRect.w, positionRect.h };
	SDL_RenderCopy( renderTarget, texture, NULL, &drawingRect );
}

void Sprite::draw()
{
	SDL_RenderCopy( renderTarget, texture, NULL, &positionRect );
}

void Sprite::drawFullScreen( Camera* camera )
{
	SDL_Rect drawingRect = { positionRect.x - camera->x, positionRect.y - camera->y, camera->w, camera->h };
	SDL_RenderCopy( renderTarget, texture, NULL, &drawingRect );
}

void Sprite::setImageAsset( ImageAsset asset )
{
	this->texture = Assets::getInstance()->getImageAsset( asset );
	SDL_QueryTexture( texture, NULL, NULL, &positionRect.w, &positionRect.h );
}