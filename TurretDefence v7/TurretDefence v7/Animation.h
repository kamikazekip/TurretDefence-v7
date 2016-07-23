#pragma once
#include <vector>
#include <iostream>
using namespace std;

enum AnimationState { AnimationState_Idle_Waiting, AnimationState_Normal, AnimationState_Reversed };
enum AnimationSpeed { AnimationSpeed_Fixed_Speed, AnimationSpeed_DeltaTime_Speed };

class Animation
{
private:
	vector<pair<float, double>> steps;
	pair<float, double> currentStep;
	pair<float, double> nextStep;
	double value;
	float pastTime;
	float triggerTime;
	double currentVPS;
	bool done;
	AnimationState currentState;
	AnimationSpeed animationSpeed;
	void calculateVPS();
	void calculateNextStep();
	bool reversed;
public:
	Animation( vector<pair<float, double>> steps, AnimationSpeed animationSpeed );
	~Animation();
	void animate( float deltaTime );
	void reset();

	/* Getters and setters */
	double getValue();
	bool isDone();
	void setState( AnimationState newState );
	AnimationState getState();
};