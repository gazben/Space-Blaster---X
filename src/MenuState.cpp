#include "MenuState.h"


MenuState::MenuState( Game *game )
{
	/////
	//string draw settings
	if ( !normaltext.loadFromFile( "MISTRAL.TTF" ) )
		Globals::log->log( "Problem with the font!" );

	//TODO: own text class

	ipadress.setString( Globals::ip->getLocalAddress().toString() );
	ipadress.setFont( normaltext );
	ipadress.setColor( sf::Color::Black );
	ipadress.setStyle( sf::Text::Regular );
	ipadress.setCharacterSize( 30 );
	ipadress.setPosition( Globals::resolution->xres * ( 10.0 / 12.0 ) , Globals::resolution->yres * ( 3.0 / 12.0 ) );

	version.setString( *Globals::version );
 	version.setStyle( sf::Text::Regular );
 	version.setFont( normaltext );
	version.setColor( sf::Color::Black );
 	version.setPosition( Globals::resolution->xres * ( 10.0 / 12.0 ) , Globals::resolution->yres * ( 11.0 / 12.0 ) );
	version.setCharacterSize( 20 );

	playernameText.setString( playername );
	playernameText.setStyle( sf::Text::Regular );
	playernameText.setFont( normaltext );
	playernameText.setColor( sf::Color::Black );
	playernameText.setPosition( Globals::resolution->xres * ( 8.0 / 12.0 ) , Globals::resolution->yres * ( 4.0 / 12.0 ) );
	playernameText.setCharacterSize( 15 );

	ipText.setString( ipconnect );
	ipText.setStyle( sf::Text::Regular );
	ipText.setFont( normaltext );
	ipText.setColor( sf::Color::Black );
	ipText.setPosition( Globals::resolution->xres * ( 8.0 / 12.0 ) , Globals::resolution->yres * ( 4.0 / 12.0 ) );
	ipText.setCharacterSize( 15 );

	tex.loadFromFile( "menu.png" );
	sprite.setTexture( tex );

	this->game = game;
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
				if( fnc == "join" ){ coop = true; join = true; }
				if( fnc == "host" ){ coop = true; host = true; }
			//TODO
		}


	}

	//we need to tell if he wants a server 
	//we need IP && playername
	if (join == true && nameIN == false){
		keyboardInput( playernameText , playername , nameIN ); 
	}
	if ( nameIN == true ){
		keyboardInput( ipText , ipconnect , ipIN );
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
		//default situation
		if ( Buttons[i] ->getObjective() != "host"  && Buttons[i] ->getObjective() != "join" )
		{

			Globals::log->log( Buttons[i] ->getObjective() );

			game->window.Draw( Buttons[i] ->getSprite() );
			game->window.Getwindow().draw( Buttons[i] -> getText() );

		}else
		{//if the coop buttom has benn pressed we need two additional buttons
			if (coop == true)
			{
				game->window.Draw( Buttons[i] ->getSprite() );
				game->window.Getwindow().draw( Buttons[i] -> getText() );

				game -> window.Getwindow().draw( ipadress );
				//player wants to join so we need to print the ip and the name
				if ( join == true )
				{

					//the name has not been entered jet
					if ( nameIN == false ){
						game->window.Getwindow().draw( playernameText ); }
					//the name has been entered we the ip adress
					else{
						game->window.Getwindow().draw( ipText );
					}

				}

				//we want to host a server we need the playername
				if ( host == true ){
					game->window.Getwindow().draw( playernameText );
				}
			}

		}
			
	}

	//texts
	game -> window.Getwindow().draw( version );

}

void MenuState::keyboardInput( sf::Text& text , std::string& str, bool& done)
{
	//user pressed one of the buttons
	if( done == false ){

		//delete a character
		if ( str.size() > 0 && sf::Keyboard::isKeyPressed( sf::Keyboard::BackSpace ) )
			str.pop_back();

		//hit enter and end the typing
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Return ) ){
			done = true;
		}

		//save the keyboard input
		if( game->event.type == sf::Event::TextEntered ){

			if ( game->event.text.unicode < 128 )
			{
				str.push_back( static_cast<char>( game -> event.text.unicode ) );
			}

		}

	text.setString( str );
	}

}
