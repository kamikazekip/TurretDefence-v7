#pragma once
#include "SDL.h"
class Vector
{
public:
	float x, y;
	Vector();
	Vector(float x, float y);
	~Vector();
	float getLength();
	Vector getNormalisation();
	void normalize();
	static Vector getVector( SDL_Point one, SDL_Point two );
	static Vector getDirection( SDL_Point one, SDL_Point two );
};

