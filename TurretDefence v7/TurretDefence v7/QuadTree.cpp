#include "QuadTree.h"
#include "WindowController.h"
#include <iostream>

QuadTree::QuadTree( int level, double x, double y, double w, double h )
{
	this->renderTarget = WindowController::getInstance()->getRenderTarget();
	this->level = level;
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	level = level;
	objects = new std::vector<GameObject*>();
	for( size_t c = 0; c < 4; c++ )
		nodes[c] = nullptr;
}


QuadTree::~QuadTree()
{
	delete objects;		objects = nullptr;
	for( size_t c = 0; c < 4; c++ )
	{
		delete nodes[c]; nodes[c] = nullptr;
	}
}

void QuadTree::clear()
{
	for( size_t c = 0; c < objects->size(); c++ )
		objects->at( c ) = nullptr;
	objects->clear();
	for( size_t x = 0; x < 4; x++ )
	{
		if( nodes[x] != NULL )
		{
			delete nodes[x]; nodes[x] = nullptr;
		}
	}
}

void QuadTree::split()
{
	int subWidth = w / 2;
	int subHeight = h / 2;

	nodes[0] = new QuadTree( level + 1, x + subWidth, y, subWidth, subHeight );
	nodes[1] = new QuadTree( level + 1, x, y, subWidth, subHeight );
	nodes[2] = new QuadTree( level + 1, x, y + subHeight, subWidth, subHeight );
	nodes[3] = new QuadTree( level + 1, x + subWidth, y + subHeight, subWidth, subHeight );
}

int QuadTree::getIndex( GameObject* object )
{
	return getIndex( object->x, object->y, object->w, object->h );
}

int QuadTree::getIndex( double objectX, double objectY, double objectW, double objectH)
{
	int index = -1;
	double verticalMidpoint = x + ( w / 2 );
	double horizontalMidpoint = y + ( h / 2 );

	// Object can completely fit within the top quadrants
	bool topQuadrant = ( objectY < horizontalMidpoint && objectY + objectH < horizontalMidpoint );
	// Object can completely fit within the bottom quadrants
	bool bottomQuadrant = ( objectY > horizontalMidpoint );

	// Object can completely fit within the left quadrants
	if( objectX < verticalMidpoint && objectX + objectW < verticalMidpoint )
	{
		if( topQuadrant )
			index = 1;
		else if( bottomQuadrant )
			index = 2;
	}
	// Object can completely fit within the right quadrants
	else if( objectX > verticalMidpoint )
	{
		if( topQuadrant )
			index = 0;
		else if( bottomQuadrant )
			index = 3;
	}
	return index;
}

void QuadTree::insert( GameObject* object )
{
	if( nodes[0] != nullptr )
	{
		int index = getIndex( object );
		if( index != -1 )
		{
			nodes[index]->insert( object );
			return;
		}
	}

	objects->push_back( object );

	if( objects->size() > max_objects && level < max_levels )
	{
		if( nodes[0] == nullptr )
			split();
		int i = 0;
		while( i < objects->size() )
		{
			int index = getIndex( objects->at( i ) );
			if( index != -1 )
			{
				GameObject* objectToRelocate = objects->at( i );
				nodes[index]->insert( objectToRelocate );
				objects->at( i ) = nullptr;
				objects->erase( objects->begin() + i );
			}
			else
				i++;
		}
	}
}

std::vector<GameObject*> QuadTree::retrieve( double objectX, double objectY, double objectW, double objectH )
{
	std::vector<GameObject*> objectsToReturn;
	int index = getIndex( objectX, objectY, objectW, objectH );
	if( index != -1 && nodes[0] != nullptr )
		objectsToReturn = nodes[index]->retrieve( objectX, objectY, objectW, objectH );
	else if( index == -1 && nodes[0] != nullptr )
		for( QuadTree* node : nodes )
			for( GameObject* object : node->retrieve( objectX, objectY, objectW, objectH ) )
				objectsToReturn.push_back( object );
	for( size_t c = 0; c < objects->size(); c++ )
		objectsToReturn.push_back( objects->at( c ) );
	return objectsToReturn;
}

void QuadTree::draw()
{
	SDL_Rect rectToDraw = { x, y, w, h };
	SDL_SetRenderDrawColor( renderTarget, 255, 0, 0, 255 );
	SDL_RenderDrawRect( renderTarget, &rectToDraw );
	for( size_t c = 0; c < 4; c++ )
	{
		if( nodes[c] != nullptr )
			nodes[c]->draw();
	}
}