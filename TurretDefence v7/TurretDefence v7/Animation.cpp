#include "Animation.h"


Animation::Animation(vector<pair<float, double>> steps )
{
	this->steps = steps;
	currentStep = steps[0];
	pastTime = 0.00f;
}


Animation::~Animation()
{

}

void Animation::animate( float deltaTime )
{
	
}

void Animation::reset()
{
	value = steps[0].second;
	pastTime = 0.00f;
}

void Animation::reverse()
{
	reversed = !reversed;
}

double Animation::getValue()
{
	return value;
}

bool Animation::isDone()
{
	return done;
}

bool Animation::isReversed()
{
	return reversed;
}