#include "TurretFactory.h"
#include "global.h"
#include "SoldierTurret.h"
#include "SniperTurret.h"

TurretFactory::TurretFactory()
{
	link( TurretType_Soldier, &TurretFactory::makeSoldierTurret );
	link( TurretType_Sniper, &TurretFactory::makeSniperTurret );

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
		float scale			= std::stof( turret->first_node( "scale" )->value() );
		TurretData turretData = { type, range, attackSpeed, scale };
		turretDataMap.insert( make_pair( type, turretData ));
	}
}


TurretFactory::~TurretFactory()
{

}

Turret* TurretFactory::createTurret( TurretType turretType, double x, double y )
{
	return ( this->*( turretMap.at(turretType ) ) )( x, y );
}

void TurretFactory::link(TurretType turretType, turret_fetch_function fetchingFunction )
{
	turretMap.insert( std::make_pair( turretType, fetchingFunction ) );
}

Turret* TurretFactory::makeSoldierTurret(double x, double y)
{
	TurretData soldierData = turretDataMap.at( "soldier" );
	return new SoldierTurret( x, y, soldierData.range, soldierData.attackSpeed, soldierData.scale );
}

Turret* TurretFactory::makeSniperTurret( double x, double y )
{
	TurretData sniperData = turretDataMap.at( "sniper" );
	return new SniperTurret( x, y, sniperData.range, sniperData.attackSpeed, sniperData.scale );
}