#pragma once
#include "Turret.h"
#include <map>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

class TurretFactory;

typedef Turret* ( TurretFactory::*turret_fetch_function )( );

enum TurretType
{
	TurretType_Soldier,
	TurretType_Sniper
};

class TurretFactory
{
private:
	std::string turretsFile;
	std::map<TurretType, turret_fetch_function> turretMap;
public:
	TurretFactory( SDL_Renderer* renderTarget );
	~TurretFactory();

	Turret* createTurret( TurretType turretType, double x, double y );
	void link( TurretType turretType, turret_fetch_function fetchingFunction );
	Turret* makeSoldierTurret();
	Turret* makeSniperTurret();
};
