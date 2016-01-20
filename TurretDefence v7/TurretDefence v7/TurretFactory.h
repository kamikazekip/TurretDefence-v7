#pragma once
#include "Turret.h"
#include <map>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

enum TurretType
{
	TurretType_Soldier,
	TurretType_Sniper
};

class TurretFactory
{
private:
	std::string turretsFile;
	std::map<std::string, Turret*> turretMap;
	std::map<TurretType, std::string> stringMap;
	void insertEntry( TurretType turretType, std::string, Turret* turret );
public:
	TurretFactory( SDL_Renderer* renderTarget );
	~TurretFactory();

	Turret* createTurret( TurretType turretType, double x, double y );
};

