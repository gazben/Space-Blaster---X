#include <SFML/Graphics.hpp>

#include "MovieState.h"
#include "game.h"



//DO NOT USE
MovieState::MovieState(){}

MovieState::MovieState( Game *game )
{

	this -> game = game;

#ifndef _DEBUG

		intro = new sfe::Movie;

	if( intro->openFromFile( "introkszk.ogv" ) )
		Globals::log->log( " movie load SUCCESS " );

	else{
		game->currentState = MENU;
		Globals::log->log( "movie load fail" );
	}

	game->window.Getwindow().setVerticalSyncEnabled( true );

	intro->resizeToFrame( 0 , 0 , Globals::resolution->xres , Globals::resolution->yres  );

	intro->play();

#endif // !RELEASE

}

MovieState::~MovieState(){

#ifndef _DEBUG

	intro->stop();
	delete intro;

#endif

}


void MovieState::Update()
{

#ifndef _DEBUG


	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) || sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) )
	{
		intro->stop();
		game->currentState = MENU;
	}

	if( intro->getStatus() == sfe::Movie::Status::Stopped )
	{
		//intro->stop();
		game->currentState = MENU;
	}

#endif // !_DEBUG

}

void MovieState::Draw()
{

#ifndef _DEBUG

	game -> window.Getwindow().draw( *intro );

#endif // !_DEBUG
}
