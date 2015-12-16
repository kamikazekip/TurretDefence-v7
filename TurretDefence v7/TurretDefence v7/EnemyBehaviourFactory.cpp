#include "EnemyBehaviourFactory.h"
#include "EnemyMovingBehaviour.h"
#include "Enemy.h"

EnemyBehaviourFactory::EnemyBehaviourFactory(Enemy* enemy)
{
	this->enemy = enemy;
	linkCondition( EnemyCondition_Spawned, new EnemyMovingBehaviour( enemy ) );
}

EnemyBehaviourFactory::~EnemyBehaviourFactory()
{

}

void EnemyBehaviourFactory::linkCondition( EnemyConditions condition, EnemyBehaviour* enemyBehaviour )
{
	behaviourMap.insert( std::pair<EnemyConditions, EnemyBehaviour*>( condition, enemyBehaviour ) );
}

EnemyBehaviour* EnemyBehaviourFactory::createBehaviour( EnemyConditions condition )
{
	return behaviourMap.at( condition )->clone();
}