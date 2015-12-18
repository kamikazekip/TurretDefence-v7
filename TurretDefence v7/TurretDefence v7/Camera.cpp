#include "Camera.h"


Camera::Camera( int windowWidth, int windowHeight, int levelWidth, int levelHeight )
{
	cameraRect.x = 0;
	cameraRect.y = 0;
	cameraRect.w = windowWidth;
	cameraRect.h = windowHeight;
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	this->levelWidth = levelWidth;
	this->levelHeight = levelHeight;
}


Camera::~Camera()
{
}
