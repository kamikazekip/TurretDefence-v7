#pragma once
#include "TurretBehaviour.h"
#include <map>

class TurretBehaviourFactory
{
private:
	Turret* turret;
	std::map<TurretConditions, TurretBehaviour*> behaviourMap;
public:
	TurretBehaviourFactory( Turret* turret );
	~TurretBehaviourFactory();
	TurretBehaviour* createBehaviour( TurretConditions condition );
};