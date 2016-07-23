#include "Input.h"
static Input* instance;

Input::Input()
{
	link( SDLK_ESCAPE, &LoopHandler::onEscapeKeyDown );
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

void Input::link( SDL_Keycode key, key_handling_function func )
{
	keyMap.insert( make_pair( key, func ) );
	keyPressedMap.insert( make_pair( key, false ) );
}

void Input::linkMultiplePress( SDL_Keycode key, key_handling_function func )
{
	keyMap.insert( make_pair( key, func ) );
	multiplePressExceptions.push_back( key );
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
				handleDownKeys( );
				break;
			
			case(SDL_KEYUP) :
				loopHandler->onKeyUp( keyPressed );
				handleUpKeys( );
				break;
		}
	}
}

void Input::handleDownKeys()
{
	map<SDL_Keycode, key_handling_function>::iterator result = keyMap.find( keyPressed );
	map<SDL_Keycode, bool>::iterator isPressedResult = keyPressedMap.find( keyPressed );
	vector<SDL_Keycode>::iterator multiplePressResult = find( multiplePressExceptions.begin(), multiplePressExceptions.end(), keyPressed );


	bool keyExists = result != keyMap.end();
	bool isException = multiplePressResult != multiplePressExceptions.end();
	bool isNotPressed = isPressedResult != keyPressedMap.end() && keyPressedMap.at( keyPressed ) == false;

	if( keyExists && ( isException || isNotPressed ) )
	{
		if( isNotPressed )
			keyPressedMap.at( keyPressed ) = true;
		( loopHandler->*( keyMap.at( keyPressed ) ) )( );
	}
}

void Input::handleUpKeys()
{
	map<SDL_Keycode, bool>::iterator result = keyPressedMap.find( keyPressed );
	if( result != keyPressedMap.end() )
	{
		result->second = false;
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
