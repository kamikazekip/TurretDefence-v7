#include "TurretFactory.h"
#include "global.h"
#include "SoldierTurret.h"
#include "SniperTurret.h"

TurretFactory::TurretFactory( SDL_Renderer* renderTarget )
{
	insertEntry( TurretType_Soldier, "soldier", new SoldierTurret() );
	insertEntry( TurretType_Sniper, "sniper", new SniperTurret() );

	turretsFile = assetBasePath + "Turrets/turrets.xml";
	rapidxml::file<> xmlFile( turretsFile.c_str() );
	rapidxml::xml_document<> doc;
	doc.parse<0>( xmlFile.data() );

	rapidxml::xml_node<> *turrets = doc.first_node();
	for( rapidxml::xml_node<> *turret = turrets->first_node( "turret" );
		 turret; turret = turret->next_sibling( "turret" ) )
	{
		std::string type	= turret->first_node( "type" )->value();
		double range		= std::stod( turret->first_node( "range" )->value() );
		float attackSpeed	= std::stof( turret->first_node( "attackSpeed" )->value() );
		int width			= std::stoi( turret->first_node( "width" )->value() );
		int height			= std::stoi( turret->first_node( "height" )->value() );
		turretMap.at( type )->setProperties( renderTarget, attackSpeed, range, width, height );
	}
}


TurretFactory::~TurretFactory()
{

}

void TurretFactory::insertEntry( TurretType turretType, std::string type, Turret* turret)
{
	stringMap.insert( std::pair<TurretType, std::string>( turretType, type ) );
	turretMap.insert( std::pair<std::string, Turret*>( type, turret ) );
}

Turret* TurretFactory::createTurret( TurretType turretType, double x, double y )
{
	return turretMap.at( stringMap.at( turretType ) )->clone( x, y );
}