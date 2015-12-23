#include "WaveFactory.h"
#include "Wave.h"
#include "global.h"
#include <iostream>
#include "EnemyFactory.h"

WaveFactory::WaveFactory( SDL_Renderer* renderTarget, std::vector<SDL_Point> path )
{
	this->renderTarget = renderTarget;
	this->path = path;
	enemyFactory = new EnemyFactory( renderTarget, path );
	wavesFile = assetBasePath + "Enemy/waves.xml";
	rapidxml::file<> xmlFile( wavesFile.c_str() );
	rapidxml::xml_document<> doc;
	doc.parse<0>( xmlFile.data() );

	rapidxml::xml_node<> *wavesXML = doc.first_node();
	for( rapidxml::xml_node<> *wave = wavesXML->first_node( "wave" );
		 wave; wave = wave->next_sibling( "wave" ) )
	{
		std::vector<Enemy*>* enemies = new std::vector<Enemy*>();
		for( rapidxml::xml_node<> *enemy = wave->first_node( "enemy" ); enemy; enemy = enemy->next_sibling( "enemy" ) )
		{
			float spawnTime = stof( enemy->first_node( "spawntime" )->value() );
			int quantity = stoi(enemy->first_node( "quantity" )->value());
			std::string type = enemy->first_node( "type" )->value();
			for( int x = 0; x < quantity; x++ )
			{
				Enemy* newEnemy = enemyFactory->createEnemy( type, spawnTime );
				enemies->push_back( newEnemy );
			}
		}
		waves.push_back( new Wave( enemies ) );
	}
}


WaveFactory::~WaveFactory()
{
}

Wave* WaveFactory::createWave( int wave )
{
	int waveToReturn = wave - 1;
	if( waveToReturn > waves.size() - 1 )
	{
		throw new exception( "Index out of bounds bij wave ophalen!" );
	}
	else
	{
		return waves.at( waveToReturn );
	}
}