#pragma once
#include <vector>
#include "Turret.h"
#include "TurretFactory.h"
#include "BaseLevelState.h"

class TurretContainer
{
private:
	SDL_Renderer* renderTarget;
	BaseLevelState* level;
	Camera* camera;
	std::vector<Turret*> turrets;
	TurretFactory* turretFactory;
public:
	TurretContainer( BaseLevelState* level, Camera* camera);
	~TurretContainer();

	void update( float deltaTime );
	void animate( float deltaTime );
	void draw();
	void addTurret( TurretType turretType, double x, double y );
	void onMouseButtonDown( int mouseX, int mouseY );
};

