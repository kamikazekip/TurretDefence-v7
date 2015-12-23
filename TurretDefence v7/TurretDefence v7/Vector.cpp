#include "Vector.h"
#include <math.h>

Vector::Vector()
{

}

Vector::Vector(float x, float y)
{
	this->x = x;
	this->y = y;
}


Vector::~Vector()
{

}

// Returns the length of the vector
float Vector::getLength()
{
	return sqrt( x * x + y * y );
}

// Normalizes the vector
Vector Vector::getNormalisation()
{
	Vector vector;
	float length = this->getLength();

	if( length != 0 )
	{
		vector.x = x / length;
		vector.y = y / length;
	}

	return vector;
}

void Vector::normalize()
{
	float length = this->getLength();
	if( length != 0 )
	{
		this->x = this->x / length;
		this->y = this->y / length;
	}
}

Vector Vector::getVector( SDL_Point base, SDL_Point target )
{
	return { float(target.x - base.x), float(target.y - base.y) };
}

Vector Vector::getDirection( SDL_Point base, SDL_Point target )
{
	Vector v = { float( target.x - base.x ), float( target.y - base.y ) };
	return v.getNormalisation();
}