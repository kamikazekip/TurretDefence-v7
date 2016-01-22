#pragma once
#include <vector>
#include "Turret.h"
#include "TurretFactory.h"

class TurretContainer
{
private:
	SDL_Renderer* renderTarget;
	Camera* camera;
	std::vector<Turret*> turrets;
	TurretFactory* turretFactory;
public:
	TurretContainer( SDL_Renderer* renderTarget, Camera* camera );
	~TurretContainer();

	void update( float deltaTime );
	void animate( float deltaTime );
	void draw();
	void addTurret( TurretType turretType, double x, double y );
	void onMouseButtonDown( int mouseX, int mouseY );
};

