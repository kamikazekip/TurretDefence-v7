#pragma once
#include <SDL.h>
#include <vector>
#include "GameObject.h"

class QuadTree
{
private:
	SDL_Renderer* renderTarget;
	int max_objects = 10;
	int max_levels = 5;

	int level;
	std::vector<GameObject*>* objects;
	double x, y, w, h;
	QuadTree* nodes[4];

	int getIndex( GameObject* object );
	int getIndex( double x, double y, double w, double h );
public:
	QuadTree( int level, double x, double y, double w, double h );
	~QuadTree();
	void clear();
	void split();
	void insert( GameObject* object );
	std::vector<GameObject*> retrieve( double x, double y, double w, double h );
	void draw();
};