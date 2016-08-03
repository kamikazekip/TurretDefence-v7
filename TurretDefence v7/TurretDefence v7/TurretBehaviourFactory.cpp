#include "TurretBehaviourFactory.h"
#include "TurretCalmBehaviour.h"
#include "TurretAngryBehaviour.h"

TurretBehaviourFactory::TurretBehaviourFactory(Turret* turret)
{
	this->turret = turret;
	behaviourMap.insert( std::make_pair( TurretCondition_Enemy_Out_Of_Range, new TurretCalmBehaviour(turret) ) );
	behaviourMap.insert( std::make_pair( TurretCondition_Enemy_In_Range, new TurretAngryBehaviour( turret ) ) );
}


TurretBehaviourFactory::~TurretBehaviourFactory()
{
	for( std::map<TurretConditions, TurretBehaviour*>::iterator iterator = behaviourMap.begin(); iterator != behaviourMap.end(); iterator++ )
		delete iterator->second;
}

TurretBehaviour* TurretBehaviourFactory::createBehaviour( TurretConditions condition )
{
	return behaviourMap.at( condition )->clone();
}
