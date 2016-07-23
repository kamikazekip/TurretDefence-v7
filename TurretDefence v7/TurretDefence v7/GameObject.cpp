#include "GameObject.h"
#include <iostream>
#include "WindowController.h"

GameObject::GameObject()
{
	this->renderTarget = WindowController::getInstance()->getRenderTarget();
	this->x = 0;
	this->y = 0;
	this->w = 50;
	this->h = 50;
}

GameObject::GameObject( double w, double h )
{
	this->renderTarget = WindowController::getInstance()->getRenderTarget();
	this->w = w;
	this->h = h;
}

GameObject::GameObject( double x, double y, double w, double h )
{
	this->renderTarget = WindowController::getInstance()->getRenderTarget();
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}


GameObject::~GameObject()
{

}

void GameObject::update( float deltaTime )
{

}

void GameObject::animate( float deltaTime )
{

}

void GameObject::draw( Camera* camera )
{

}

void GameObject::drawDebug()
{
	SDL_Rect rectToDraw = { x, y, w, h };
	SDL_SetRenderDrawColor( renderTarget, 0, 0, 255, 255 );
	SDL_RenderDrawRect( renderTarget, &rectToDraw );
}

bool GameObject::isTouching( double objectX, double objectY )
{
	return ( objectX >= x && objectX <= x + w && objectY >= y && objectY <= y + h );
}

bool GameObject::overlaps( double objectX, double objectY, double objectW, double objectH )
{
	return ( x < objectX + objectW && x + w > objectX &&
			 y < objectY + objectH && y + h > objectY );
}

SDL_Rect GameObject::getDrawingRect( Camera* camera )
{
	return  { x - camera->x, y - camera->y, w, h };
}

double GameObject::getOriginX()
{
	return x + ( w / 2 );
}

double GameObject::getOriginY()
{
	return y + ( h / 2 );
}