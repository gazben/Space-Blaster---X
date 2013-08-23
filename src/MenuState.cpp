#include "MenuState.h"

sf::Color color( 100 , 100 , 100 , 255 );

MenuState::MenuState( Game *game )
{
	/////
	//string draw settings
	if ( !normaltext.loadFromFile( "MISTRAL.TTF" ) )
		Globals::log->log( "Problem with the font!" );

	ipadress.setString( Globals::ip->getLocalAddress().toString() );
	ipadress.setFont( normaltext );
	ipadress.setColor( sf::Color::Black );

	version.setString( *Globals::version );
 	version.setStyle( sf::Text::Regular );
 	version.setFont( normaltext );
	version.setColor( color );
 	version.setPosition( 100 , 100 );

	tex.loadFromFile( "menu.png" );
	sprite.setTexture( tex );

	this->game = game;

	//Creating the buttons
	Buttons.push_back( new Buttom( Globals::resolution -> xres / 4 , Globals::resolution -> yres / 4 , "singleplayer.png" , "new game" ) );
	Buttons.push_back( new Buttom( Globals::resolution -> xres / 4 , Globals::resolution -> yres / 2 , "quit.png" , "quit" ) );
	Buttons.push_back( new Buttom( Globals::resolution -> xres / 2 , Globals::resolution -> yres / 4 , "coop.png" , "coop" ) );
}

MenuState::~MenuState()
{
	for (int i = 0; i < Buttons.size(); i++)
	{
		delete Buttons[i];
	}
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
				//I know that switch should be used....
				if( fnc ==  "new game"){

					game->currentState = INGAME;

				}

				if( fnc == "quit" ){

					game->running = false;
				}

				if( fnc == "coop" ){


					//give ip adress!

				}
			//TODO

		}

	}


}

void MenuState::Draw()
{
	////
	//DO NOT draw behind this!
	game -> window.Draw( sprite );
	////

	//Buttons
	for (int i = 0; i < Buttons.size(); i++)
	{
		game->window.Draw( Buttons[i] ->getSprite() );
	}

	//texts
	game -> window.Getwindow().draw( version );
}

