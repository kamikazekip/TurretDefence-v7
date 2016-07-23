#include "TurretBarrel.h"
#include "Turret.h"
#include "WindowController.h"


TurretBarrel::TurretBarrel(ImageAsset calm, ImageAsset angry, double rotation, double x, double y, float scale)
{
	this->renderTarget		= WindowController::getInstance()->getRenderTarget();
	image_calm				= Assets::getInstance()->getImageAsset( calm );
	image_angry				= Assets::getInstance()->getImageAsset( angry );

	imageMap.insert( std::make_pair( TurretImage_Calm, image_calm ) );
	imageMap.insert( std::make_pair( TurretImage_Angry, image_angry ) );

	this->rotation			= rotation;
	this->x					= x;
	this->y					= y;

	int imageWidth;
	int imageHeight;
	SDL_QueryTexture( image_calm, NULL, NULL, &imageWidth, &imageHeight );
	this->w					= imageWidth * scale;
	this->h					= imageHeight * scale;
	this->y					-= h;
	this->x					-= ( w / 2 );
	this->rotationCenter = { w / 2, h };
}


TurretBarrel::~TurretBarrel()
{

}

void TurretBarrel::setImage( TurretImages turretImage )
{
	image_current = imageMap.at( turretImage );
}

void TurretBarrel::updateRotation( double rotation )
{
	this->rotation = rotation;
}

void TurretBarrel::draw( Camera* camera )
{
	SDL_Rect drawingRect = getDrawingRect(camera);
	SDL_RenderCopyEx( renderTarget, image_current, NULL, &drawingRect, rotation, &rotationCenter, SDL_FLIP_NONE );
}

double TurretBarrel::getDistanceToMuzzle()
{
	return this->h + 5;
}