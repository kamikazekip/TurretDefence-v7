#include "Random.h"

Random& Random::getInstance()
{
	static Random    instance; // Guaranteed to be destroyed.
	// Instantiated on first use.
	return instance;
}

int Random::nextInt( int min, int max )
{
	uniform_int_distribution<int> dist{ min, max };
	return dist( dre );
}

float Random::nextFloat( float min, float max )
{
	uniform_real_distribution<float> dist{ min, max };
	return dist( dre );
}

bool Random::nextBool()
{
	uniform_int_distribution<int> dist{ 0, 1 };
	int result = dist( dre );
	return result == 0;
}