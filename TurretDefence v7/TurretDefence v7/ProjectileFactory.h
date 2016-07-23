#pragma once
#include "Projectile.h"
#include "Assets.h"
#include <string>
#include <map>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "Vector.h"

class ProjectileFactory
{
private:
	std::string projectilesFile;
	std::map<std::string, Projectile*> projectileMap;
	/* Singleton */
	ProjectileFactory();
	ProjectileFactory( ProjectileFactory const& );
	~ProjectileFactory();
public:
	/* Singleton */
	static ProjectileFactory* getInstance();

	Projectile* getProjectilePrototype( std::string type );
};

