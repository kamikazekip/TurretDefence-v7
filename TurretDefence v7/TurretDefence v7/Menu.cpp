#include "Menu.h"
#include "Version.h"

Menu::Menu(SDL_Renderer* renderTarget, Game* game, Camera* camera)
	: LoopHandler( camera )
{
	menuItems = new std::vector<MenuItem*>();

	menuFontColor			= { 253, 122, 6, 255 }; /* orange */
	menuFontColorSelected	= { 253, 80, 6, 255 };	/* light orange*/
	this->renderTarget = renderTarget;
	this->game = game;

	std::string fontPath = assetBasePath + "Fonts/action_jackson.ttf";
	std::string fontPath2 = assetBasePath + "Fonts/yorkwhiteletter.ttf";
	
	menuItemFont = TTF_OpenFont( fontPath.c_str(), 70 );
	versionFont = TTF_OpenFont( fontPath2.c_str(), 45 );
	version = new Sprite( renderTarget, versionFont, Version::getInstance()->getYorkVersion(), menuFontColor );
	version->positionRect.x = 20;
	version->positionRect.y = game->getWindowHeight() - version->positionRect.h - 10;
}


Menu::~Menu()
{
	for( size_t c = 0; c < menuItems->size(); c++ )
	{
		delete menuItems->at( c );		menuItems->at( c ) = nullptr;
	}
	delete menuItems;					menuItems = nullptr;
	TTF_CloseFont( versionFont );		versionFont = nullptr;
	delete version;						version = nullptr;
}

void Menu::draw()
{
	version->draw();
}

void Menu::tick()
{

}

void Menu::addMenuItem( std::string text )
{
	menuItems->push_back( new MenuItem( renderTarget, menuItemFont, text, menuFontColor, menuFontColorSelected ) );
}

void Menu::centerMenuItems()
{
	int combinedHeight = 0;
	int margin = 70;
	for( std::vector<int>::size_type i = menuItems->size() - 1; i != (std::vector<int>::size_type) - 1; i-- )
	{
		combinedHeight += menuItems->at( i )->getHeight();
		int xPosition = (game->getWindowWidth() / 2) - (menuItems->at( i )->getWidth() / 2);
		menuItems->at( i )->setXPosition( xPosition );
	}

	int marginHeight = ((menuItems->size() - 1) * margin);
	combinedHeight += marginHeight;

	for( std::vector<int>::size_type j = menuItems->size() - 1; j != (std::vector<int>::size_type) - 1; j-- )
	{
		int previousHeight = 50;
		for( size_t h = 0; h < j; h++ )
			previousHeight += menuItems->at( h )->getHeight();
		int yPosition = (game->getWindowHeight() / 2) - (combinedHeight / 2) + (j * margin) + previousHeight;
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

void Menu::checkHover(int mouseX, int mouseY)
{
	for( size_t c = 0; c < menuItems->size(); c++ )
	{
		menuItems->at( c )->checkHover(mouseX, mouseY);
	}
}