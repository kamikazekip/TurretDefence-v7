#include "Menu.h"
#include "Version.h"
#include "WindowController.h"
#include "Game.h"

Menu::Menu( )
	: LoopHandler( )
{
	game = Game::getInstance();
	renderTarget = WindowController::getInstance()->getRenderTarget();
	windowWidth = WindowController::getInstance()->width;
	windowHeight = WindowController::getInstance()->height;
	menuItems = new std::vector<MenuItem*>();

	this->assets = Assets::getInstance();
	version = new Sprite( FontAsset_VersionFont, Version::getInstance()->getYorkVersion(), menuFontColor );
	version->positionRect.x = 20;
	version->positionRect.y = windowHeight - version->positionRect.h - 10;
}


Menu::~Menu()
{
	for( size_t c = 0; c < menuItems->size(); c++ )
	{
		delete menuItems->at( c );		menuItems->at( c ) = nullptr;
	}
	delete menuItems;					menuItems = nullptr;
	delete version;						version = nullptr;
}

void Menu::draw()
{
	
}

void Menu::tick()
{

}

void Menu::addMenuItem( std::string text )
{
	menuItems->push_back( new MenuItem( FontAsset_MenuItemFont, text, menuFontColor, menuFontColorSelected ) );
}

void Menu::centerMenuItems()
{
	int combinedHeight = 0;
	int margin = 70;
	for( std::vector<int>::size_type i = menuItems->size() - 1; i != (std::vector<int>::size_type) - 1; i-- )
	{
		combinedHeight += menuItems->at( i )->getHeight();
		int xPosition = (windowWidth / 2) - (menuItems->at( i )->getWidth() / 2);
		menuItems->at( i )->setXPosition( xPosition );
	}

	int marginHeight = ((menuItems->size() - 1) * margin);
	combinedHeight += marginHeight;

	for( std::vector<int>::size_type j = menuItems->size() - 1; j != (std::vector<int>::size_type) - 1; j-- )
	{
		int previousHeight = 50;
		for( size_t h = 0; h < j; h++ )
			previousHeight += menuItems->at( h )->getHeight();
		int yPosition = (windowHeight / 2) - (combinedHeight / 2) + (j * margin) + previousHeight;
		menuItems->at( j )->setYPosition( yPosition );
	}
}

void Menu::drawMenuItems()
{
	for( size_t c = 0; c < menuItems->size(); c++ )
	{
		menuItems->at( c )->draw();
	}
}

void Menu::checkHover( int mouseX, int mouseY )
{
	for( size_t c = 0; c < menuItems->size(); c++ )
	{
		menuItems->at( c )->checkHover( mouseX, mouseY );
	}
}