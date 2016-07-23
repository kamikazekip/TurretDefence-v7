#include "ProjectileFactory.h"
#include "global.h"

static ProjectileFactory* instance;

ProjectileFactory::ProjectileFactory()
{
	projectilesFile = assetBasePath + "Projectiles/projectiles.xml";
	rapidxml::file<> xmlFile( projectilesFile.c_str() );
	rapidxml::xml_document<> doc;
	doc.parse<0>( xmlFile.data() );

	rapidxml::xml_node<> *projectiles = doc.first_node();
	for( rapidxml::xml_node<> *projectile = projectiles->first_node( "projectile" );
	projectile; projectile = projectile->next_sibling( "projectile" ) )
	{
		std::string type = projectile->first_node( "type" )->value();
		int width = std::stoi( projectile->first_node( "width" )->value() );
		int height = std::stoi( projectile->first_node( "height" )->value() );
		int speed = std::stoi( projectile->first_node( "speed" )->value() );
		int damage = std::stoi( projectile->first_node( "damage" )->value() );
		std::string image = projectile->first_node( "image" )->value();
		projectileMap.insert( std::make_pair( type, new Projectile( width, height, speed, damage, Assets::getInstance()->getImageAsset( image ) ) ) );
	}
}

ProjectileFactory::~ProjectileFactory()
{

}

Projectile* ProjectileFactory::getProjectilePrototype( std::string type )
{
	return projectileMap.at( type );
}

/* Singleton */
ProjectileFactory* ProjectileFactory::getInstance()
{
	if( !instance )
		instance = new ProjectileFactory();
	return instance;
}
