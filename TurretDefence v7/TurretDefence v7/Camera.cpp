#include "Camera.h"


Camera::Camera( int windowWidth, int windowHeight, int levelWidth, int levelHeight )
{
	x = 0;
	y = 0;
	w = windowWidth;
	h = windowHeight;
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	this->levelWidth = levelWidth;
	this->levelHeight = levelHeight;
}


Camera::~Camera()
{
}
