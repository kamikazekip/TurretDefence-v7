#include "Input.h"
static Input* instance;

Input::Input()
{
	keyMap.insert( std::make_pair( SDLK_ESCAPE, &LoopHandler::onEscapeKeyDown ) );
}

/* Singleton */
Input* Input::getInstance()
{
	if( !instance )
		instance = new Input();
	return instance;
}

Input::~Input()
{

}

void Input::update()
{
	while( SDL_PollEvent( &event ) )
	{
		mouseX = event.motion.x;
		mouseY = event.motion.y;
		keyPressed = event.key.keysym.sym;

		switch( event.type )
		{
			case(SDL_QUIT) :
				loopHandler->onQuit();
				break;

			case(SDL_MOUSEBUTTONDOWN) :
				loopHandler->onMouseButtonDown( mouseX, mouseY );
				break;

			case(SDL_MOUSEBUTTONUP) :
				loopHandler->onMouseButtonUp( mouseX, mouseY );
				break;

			case(SDL_MOUSEMOTION) :
				loopHandler->onMouseMotion( mouseX, mouseY );
				break;

			case(SDL_KEYDOWN) :
				loopHandler->onKeyDown( keyPressed );
				handleKeys( );
				break;

			case(SDL_KEYUP) :
				loopHandler->onKeyUp( keyPressed );
				break;
		}
	}
}

void Input::handleKeys()
{
	std::map<SDL_Keycode, key_handling_function>::iterator result = keyMap.find( keyPressed );
	if( result != keyMap.end() )
	{
		( loopHandler->*( keyMap.at( keyPressed ) ) )( );
	}
}

void Input::setLoopHandler(LoopHandler* loopHandler)
{
	this->loopHandler = loopHandler;
}

extern __declspec(dllexport) void Input_Quit()
{
	delete instance; instance = nullptr;
}
