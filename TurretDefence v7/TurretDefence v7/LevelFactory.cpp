#include "LevelFactory.h"
#include "BaseLevelState.h"
#include "Wood.h"
#include "Camera.h"
#include "global.h"
#include "Game.h"

LevelFactory::LevelFactory()
{
	this->camera = Game::getInstance()->getCamera();

	insertMapEntry( Level_Wood, new Wood(), "wood" );
}

LevelFactory::~LevelFactory()
{

}

void LevelFactory::insertMapEntry( Levels levelEnum, BaseLevelState* level, std::string waypointsFile )
{
	std::vector<SDL_Point> path;
	//std::string file = assetBasePath + "Paths/" + waypointsFile + "/waypoints_" + std::to_string(camera->w) + "_" + std::to_string(camera->h) + ".xml";
	std::string file = assetBasePath + "Paths/" + waypointsFile + "/waypoints.xml";
	rapidxml::file<> xmlFile( file.c_str() );
	rapidxml::xml_document<> doc;
	doc.parse<0>( xmlFile.data() );
	rapidxml::xml_node<> *waypoints = doc.first_node();
	for( rapidxml::xml_node<> *waypoint = waypoints->first_node( "waypoint" );
		 waypoint; waypoint = waypoint->next_sibling( "waypoint" ) )
	{
		float xMultiplier = std::stof( waypoint->first_node( "x" )->value() );
		float yMultiplier = std::stof( waypoint->first_node( "y" )->value() );
		int x = camera->windowWidth * xMultiplier;
		int y = camera->windowHeight * yMultiplier;
		path.push_back( SDL_Point { x, y } );
	}
	level->setPath( path );
	levelMap.insert( std::pair<Levels, BaseLevelState*>( levelEnum, level ) );
}

BaseLevelState* LevelFactory::getStartLevel()
{
	return levelMap.at( Level_Wood );
}