#pragma once
#include <vector>

using namespace std;

class Animation
{
private:
	vector<pair<float, double>> steps;
	pair<float, double> currentStep;
	double value;
	float pastTime;
	float triggerTime;
	double currentVPS;
	bool done;
	bool reversed;
public:
	Animation( vector<pair<float, double>> steps );
	~Animation();
	void animate( float deltaTime );
	void reset();
	void reverse();

	/* Getters */
	double getValue();
	bool isDone();
	bool isReversed();
};