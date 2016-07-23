#pragma once
#include "Camera.h"
class GameObject
{
protected:
	SDL_Renderer* renderTarget;
public:
	double x, y, w, h;
	GameObject();
	GameObject( double w, double h );
	GameObject( double x, double y, double w, double h );
	~GameObject();
	
	virtual void update( float deltaTime );
	virtual void animate( float deltaTime );
	virtual void draw( Camera* camera );
	virtual void drawDebug();
	virtual bool isTouching( double objectX, double objectY );
	virtual bool overlaps( double objectX, double objectY, double objectW, double objectH );

	virtual SDL_Rect getDrawingRect( Camera* camera );
	virtual double getOriginX();
	virtual double getOriginY();
};

