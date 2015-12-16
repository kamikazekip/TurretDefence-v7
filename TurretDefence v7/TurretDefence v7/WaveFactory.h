#pragma once
class Wave;

class WaveFactory
{
public:
	WaveFactory();
	~WaveFactory();
	Wave* createWave( int wave );
};

