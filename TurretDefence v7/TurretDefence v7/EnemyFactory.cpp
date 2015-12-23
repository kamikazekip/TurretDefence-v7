#include "EnemyFactory.h"
#include "global.h"

EnemyFactory::EnemyFactory( SDL_Renderer* renderTarget, std::vector<SDL_Point> path )
{
	this->path = path;
	enemiesFile = assetBasePath + "Enemy/enemies.xml";
	rapidxml::file<> xmlFile( enemiesFile.c_str() );
	rapidxml::xml_document<> doc;
	doc.parse<0>( xmlFile.data() );

	rapidxml::xml_node<> *enemies = doc.first_node();
	for( rapidxml::xml_node<> *enemy = enemies->first_node( "enemy" );
			enemy; enemy = enemy->next_sibling( "enemy" ) )
	{
		std::string type = enemy->first_node( "type" )->value();
		int health = std::stoi( enemy->first_node( "health" )->value() );
		int speed = std::stoi( enemy->first_node( "speed" )->value() );
		int width = std::stoi( enemy->first_node( "width" )->value() );
		int height = std::stoi( enemy->first_node( "height" )->value() );
		insertEntry( type, new Enemy( renderTarget, Assets::getInstance()->getAsset( type ), health, speed, width, height, path, 0.00f ) );
	}
}

EnemyFactory::~EnemyFactory()
{

}

void EnemyFactory::insertEntry( std::string key, Enemy* enemy )
{
	enemyMap.insert( std::pair<std::string, Enemy*>(key, enemy) );
}

Enemy* EnemyFactory::createEnemy( std::string type, float spawnTime )
{
	return enemyMap.at( type )->clone( spawnTime );
}
