#include "EnemyBehaviourFactory.h"
#include "EnemyMovingBehaviour.h"
#include "EnemyDeadBehaviour.h"
#include "Enemy.h"

EnemyBehaviourFactory::EnemyBehaviourFactory(Enemy* enemy)
{
	this->enemy = enemy;
	linkCondition( EnemyCondition_Spawned, new EnemyMovingBehaviour( enemy ) );
	linkCondition( EnemyCondition_Health_Depleted, new EnemyDeadBehaviour( enemy ) ); // <--- Maak deze behaviour
}

EnemyBehaviourFactory::~EnemyBehaviourFactory()
{
	for( std::map<EnemyConditions, EnemyBehaviour*>::iterator it = behaviourMap.begin(); it != behaviourMap.end(); ++it )
		delete it->second;
}

void EnemyBehaviourFactory::linkCondition( EnemyConditions condition, EnemyBehaviour* enemyBehaviour )
{
	behaviourMap.insert( std::pair<EnemyConditions, EnemyBehaviour*>( condition, enemyBehaviour ) );
}

EnemyBehaviour* EnemyBehaviourFactory::createBehaviour( EnemyConditions condition )
{
	return behaviourMap.at( condition )->clone();
}