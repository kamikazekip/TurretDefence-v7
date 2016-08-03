#pragma once
#include "Camera.h"

class GameObject
{
private:
	void commonInit();
protected:
	SDL_Renderer* renderTarget;
public:
	double x, y, w, h;
	bool trash;
	GameObject();
	GameObject( double w, double h );
	GameObject( double x, double y, double w, double h );
	~GameObject();
	
	/* Model */
	virtual void update( float deltaTime );
	virtual void collide();
	virtual bool isTouching( double objectX, double objectY );
	virtual bool overlaps( GameObject* gameObject );
	virtual bool overlaps( double objectX, double objectY, double objectW, double objectH );
	virtual double getOriginX();
	virtual double getOriginY();
	virtual bool canCollide();

	/* View */
	virtual void animate( float deltaTime );
	virtual void draw( Camera* camera );
	virtual void drawDebug();
	virtual SDL_Rect getDrawingRect( Camera* camera );
	
	/* Input */
	virtual void onMouseButtonDown( int mouseX, int mouseY );
};

