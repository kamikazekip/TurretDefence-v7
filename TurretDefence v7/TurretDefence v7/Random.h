#pragma once
#include <random>

using namespace std;

class Random
{
public:
	static Random& getInstance();
	int nextInt( int min, int max );
	float nextFloat( float min, float max );
	bool nextBool();
private:
	random_device dev;
	default_random_engine dre{ dev() };
	Random()
	{};
	Random( Random const& ) = delete;
	void operator=(Random const&) = delete;
};