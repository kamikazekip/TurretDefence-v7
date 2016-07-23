#pragma once
#include "Turret.h"
#include <map>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

class TurretFactory;

typedef Turret* ( TurretFactory::*turret_fetch_function )( double x, double y );

struct TurretData
{
	std::string type;
	double range;
	float attackSpeed;
	float scale;
};

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
	std::map<std::string, TurretData> turretDataMap;
public:
	TurretFactory();
	~TurretFactory();

	Turret* createTurret( TurretType turretType, double x, double y );
	void link( TurretType turretType, turret_fetch_function fetchingFunction );
	Turret* makeSoldierTurret( double x, double y );
	Turret* makeSniperTurret( double x, double y );
};

