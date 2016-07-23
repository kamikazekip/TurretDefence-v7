#include "HUDButton.h"
#include "Game.h"
#include "BaseLevelState.h"
#include "WindowController.h"

HUDButton::HUDButton( Game* game, BaseLevelState* level, ImageAsset normal, ImageAsset hover )
{
	this->game = game;
	this->level = level;
	this->renderTarget = WindowController::getInstance()->getRenderTarget();
	normalTexture = Assets::getInstance()->getImageAsset( normal );
	hoverTexture = Assets::getInstance()->getImageAsset( hover );
	currentTexture = normalTexture;
	SDL_QueryTexture( currentTexture, NULL, NULL, &positionRect.w, &positionRect.h );
}


HUDButton::~HUDButton()
{

}

bool HUDButton::checkHover(int mouseX, int mouseY)
{
	if( isTouching( mouseX, mouseY ) )
	{
		currentTexture = hoverTexture;
		return true;
	}
	else if( currentTexture = hoverTexture )
	{
		currentTexture = normalTexture;
	}
	return false;
}

bool HUDButton::isTouching( int mouseX, int mouseY )
{
	int x = positionRect.x;
	int y = positionRect.y;
	int w = positionRect.w;
	int h = positionRect.h;
	return ( mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h );
}

void HUDButton::onClick()
{

}

void HUDButton::draw()
{
	SDL_RenderCopy( renderTarget, currentTexture, NULL, &positionRect );
}

int HUDButton::getXPosition()
{
	return positionRect.x;
}

int HUDButton::getYPosition()
{
	return positionRect.y;
}

int HUDButton::getWidth()
{
	return positionRect.w;
}

int HUDButton::getHeight()
{
	return positionRect.h;
}

void HUDButton::setXPosition( int x )
{
	positionRect.x = x;
}

void HUDButton::setYPosition( int y )
{
	positionRect.y = y;
}