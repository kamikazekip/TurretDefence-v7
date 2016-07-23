#include "Animation.h"
#include "Game.h"

Animation::Animation(vector<pair<float, double>> steps, AnimationSpeed animationSpeed )
{
	this->steps = steps;
	reversed = false;
	reset();
	currentState = AnimationState_Idle_Waiting;
	this->animationSpeed = animationSpeed;
}


Animation::~Animation()
{

}

void Animation::calculateVPS()
{
	pastTime = 0.00f;

	/* TimeDelta cannot be negative! */
	float timeDelta = nextStep.first - currentStep.first;
	if( timeDelta < 0 )
		timeDelta *= -1;

	double valueDelta = nextStep.second - currentStep.second;
	currentVPS = 1.0 / timeDelta * valueDelta;
	triggerTime = timeDelta;
}

void Animation::animate( float deltaTime )
{
	if( currentState != AnimationState_Idle_Waiting )
	{		
		if( animationSpeed == AnimationSpeed_Fixed_Speed )
			deltaTime = Game::getInstance()->getDeltaTime();
		pastTime += deltaTime;
		if( pastTime >= triggerTime )
			calculateNextStep();
		if( !done )
			value += currentVPS * deltaTime;
	}
}

void Animation::reset()
{
	currentStep = steps[0];
	nextStep = steps[1];
	value = currentStep.second;
	done = false;
	calculateVPS();
}

void Animation::setState(AnimationState newState)
{
	currentState = newState;
	if( currentState == AnimationState_Reversed )
	{
		reverse( steps.begin(), steps.end() );
		reversed = true;
		reset();
	}
	else if( currentState == AnimationState_Normal )
	{
		if( reversed )
		{
			reverse( steps.begin(), steps.end() );
			reversed = false;
		}
		reset();
	}
}

AnimationState Animation::getState()
{
	return currentState;
}

double Animation::getValue()
{
	return value;
}

bool Animation::isDone()
{
	return done;
}

void Animation::calculateNextStep()
{
	value = nextStep.second;
	vector<pair<float, double>>::iterator stepIt = next( find( steps.begin(), steps.end(), nextStep ), 1 );
	if( stepIt != steps.end() )
	{
		currentStep = nextStep;
		nextStep = *stepIt;
		calculateVPS();
	}
	else
		done = true;
}