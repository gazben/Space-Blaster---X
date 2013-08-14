#include "MenuState.h"
#include "Globals.h"
#include "game.h"

MenuState::MenuState( Game *game )
{

	tex.loadFromFile( "menu.png" );
	sprite.setTexture( tex );

	this->game = game;

	//Creating the buttons
	Buttons.push_back( new Buttom( Globals::resolution -> xres / 2 , Globals::resolution -> yres / 4 , "singleplayer.png" , "new game" ) );
}

MenuState::~MenuState()
{

}

void MenuState::Update()
{

	for (int i = 0; i < Buttons.size(); i++)
	{

		try{
		Buttons[i] -> isUsed( sf::Mouse::getPosition( game->window.Getwindow() ).x , sf::Mouse::getPosition( game->window.Getwindow() ).y );
		}catch( std::string fnc){


			////
			//the menu buttom handling itself
			////
			if( fnc ==  "new game"){

				game->currentState = INGAME;

			}

			if( fnc == "quit" ){

				game->running = false;
			}


			//TODO

		}

	}


}

void MenuState::Draw()
{
	game -> window.Draw( sprite );

	for (int i = 0; i < Buttons.size(); i++)
	{
		game->window.Draw( Buttons[i] ->getSprite() );
	}
}

