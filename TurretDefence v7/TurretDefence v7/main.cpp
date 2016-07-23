#include <iostream>
#include <SDL.h>
#include "SDL_ttf.h"
#include "Game.h"
#include "Version.h"
#include <string>

int main(int, char**){
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	if( TTF_Init() != 0 )
	{
		std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
	}
	
	std::cout << Version::getInstance()->getVersion() << std::endl;

	Game* game = Game::getInstance();

	Game_Quit();
	Version_Quit();
	SDL_Quit();
	return 0;
}