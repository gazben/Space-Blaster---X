#include "MenuState.h"


MenuState::MenuState( Game *game )
	:ipText( Globals::resolution->xres * ( 10.0 / 12.0 ) , Globals::resolution->yres * ( 3.0 / 12.0 ) , Globals::ip->getLocalAddress().toString() , 30 ),
	version( Globals::resolution->xres * ( 10.0 / 12.0 ) , Globals::resolution->yres * ( 11.0 / 12.0 ) , *Globals::version , 20  ),
	playernameText( Globals::resolution->xres * ( 8.0 / 12.0 ) , Globals::resolution->yres * ( 4.0 / 12.0 )  )
{

	tex.loadFromFile( "menu.png" );
	sprite.setTexture( tex );


	this->game = game;

	game -> menustate = this;
	
	coop = false;
	host = false;
	join = false;
	nameIN = false;
	ipIN = false;

	//Creating the buttons
	Buttons.push_back( new Buttom( Globals::resolution -> xres / 4 , Globals::resolution -> yres / 4 , "button.png" , "1 player" ) );
	Buttons.push_back( new Buttom( Globals::resolution -> xres / 4 , Globals::resolution -> yres / 2 , "button.png" , "quit" ) );
	Buttons.push_back( new Buttom( Globals::resolution -> xres / 2 , Globals::resolution -> yres / 4 , "button.png" , "2 players" ) );
	Buttons.push_back( new Buttom( Globals::resolution -> xres * ( 3.0 / 4.0 ) , Globals::resolution -> yres  * (2.0 /6.0) , "button.png" , "host" ) );
	Buttons.push_back( new Buttom( Globals::resolution -> xres * ( 3.0 / 4.0 ) , Globals::resolution -> yres  * (3.0 /6.0), "button.png" , "join" ) );

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

			//the menu buttom handling itself
				//I know that switch should be used....
				if( fnc ==  "1 player"){ game->currentState = INGAME; }
				if( fnc == "quit" ){ game->running = false; }
				if( fnc == "2 players" ){ coop = true; }
				if( fnc == "join" ){ coop = true; join = true; game->coopnetwork->setServer( false ); game->coopnetwork->setLobby(true); }
				if( fnc == "host" ){ coop = true; host = true; game->coopnetwork->setServer( true ); game->coopnetwork->setLobby(true);}
			//TODO
		}


	}

	//we need to tell if he wants a server 
	//we need IP && playername

	if ( ( join == true || host == true ) && nameIN == false ){
		keyboardInput( playernameText , playername , nameIN );
		game->ingamestate->player.setName( playername );
		
	}
	if ( nameIN == true && join == true ){
		keyboardInput( ipText , ipconnect , ipIN );
		game ->coopnetwork->setIP( ipconnect );
		Globals::log->log("connecting to ip:");
		Globals::log->log( ipconnect );
	}	
	
	if( join == true && ipIN == true && nameIN == true ){
		
		if( game->coopnetwork->connected() ){
			Globals::log->log( "Connection stable :)" );
		}

	}

	game->coopnetwork->update();


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
		//default situation
		if ( Buttons[i] ->getObjective() != "host"  && Buttons[i] ->getObjective() != "join" )
		{

			game->window.Draw( Buttons[i] ->getSprite() );
			game->window.Getwindow().draw( Buttons[i] -> getText() );

		}else
		{//if the coop buttom has benn pressed we need two additional buttons
			if (coop == true)
			{
				game->window.Draw( Buttons[i] ->getSprite() );
				game->window.Getwindow().draw( Buttons[i] -> getText() );

				game -> window.Getwindow().draw( ipText.getText() );
				//player wants to join so we need to print the ip and the name
				if ( join == true )
				{

					//the name has not been entered jet
					if ( nameIN == false ){
						game->window.Getwindow().draw( playernameText.getText() ); }
					//the name has been entered we the ip adress
					else{
						game->window.Getwindow().draw( ipText.getText() );
					}

				}

				//we want to host a server we need the playername
				if ( host == true ){
					game->window.Getwindow().draw( playernameText.getText() );
				}
			}

		}
			
	}
	
	//draw th version number
	game -> window.Getwindow().draw( version.getText() );

}

void MenuState::keyboardInput( renderText& text , std::string& str, bool& done)
{
	//user pressed one of the buttons
	if( done == false ){

		//delete a character
		if ( str.size() > 0 && sf::Keyboard::isKeyPressed( sf::Keyboard::BackSpace ) ){
			str.pop_back();
		}else
		//hit enter and end the typing
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Return ) ){
			done = true;
		}else
		//save the keyboard input
		if( game->event.type == sf::Event::TextEntered ){

			if ( game->event.text.unicode < 128 )
			{
				str.push_back( static_cast<char>( game -> event.text.unicode ) );
			}

		}

	text.setText( str );
	}

}
