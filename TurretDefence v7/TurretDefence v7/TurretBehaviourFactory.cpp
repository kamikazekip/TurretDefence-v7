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

}

TurretBehaviour* TurretBehaviourFactory::createBehaviour( TurretConditions condition )
{
	return behaviourMap.at( condition )->clone();
}
