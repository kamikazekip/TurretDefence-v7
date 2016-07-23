#pragma once
#include "GameObject.h"
#include "Assets.h"
#include <map>

enum TurretImages;

class TurretBarrel : public GameObject
{
private:
	SDL_Renderer* renderTarget;
	SDL_Texture* image_calm;
	SDL_Texture* image_angry;
	SDL_Texture* image_current;
	std::map<TurretImages, SDL_Texture*> imageMap;
	SDL_Point rotationCenter;

	double rotation;
public:
	TurretBarrel(ImageAsset calm, ImageAsset angry, double rotation, double x, double y, float scale);
	~TurretBarrel();

	void setImage( TurretImages turretImage );
	void updateRotation( double rotation );
	void draw( Camera* camera );
	double getDistanceToMuzzle();
};

