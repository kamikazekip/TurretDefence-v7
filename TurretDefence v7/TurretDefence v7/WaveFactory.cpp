#include "WaveFactory.h"
#include "Wave.h"

WaveFactory::WaveFactory()
{
}


WaveFactory::~WaveFactory()
{
}

Wave* WaveFactory::createWave( int wave )
{
	return new Wave();
}