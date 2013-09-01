#include <SFML/Graphics.hpp>
#include <vector>
#include <time.h>

#include "game.h"

//INIT
Game::Game()
{
	//Display time in log!
	time_t rawtime;
	struct tm * timeinfo;

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );

	Globals::log->log( asctime(timeinfo) );
	Globals::log->log( "" );

#ifndef _DEBUG
	Globals::log->log( "Zombisch pre-Alfa version - Release version" );
	gamestates.push_back( new MovieState( this ) );
#endif
	Globals::log->log( "Zombisch pre-Alfa version - Debug version" );
	gamestates.push_back( new MenuState( this ) );
	gamestates.push_back( new InGameState( this ) );

#ifndef _DEBUG
	currentState = MOVIE;
#else
	currentState = MENU;
#endif

	running = true;
	coopnetwork = new network();

}

Game::~Game()
{
	running = false;

	for (int i=0; i < gamestates.size(); i++)
		delete gamestates[i];

}


void Game::Run()
{

	//Clock stuff
	sf::Clock clock;
	sf::Int64 sum_time = 0;

	/////////
	///MAIN LOOP
	////////
	while( running )
	{
		// get passed time
		sum_time += clock.restart().asMicroseconds();
		
		// FIX 50Hz
		while( sum_time >= 20000 )
		{
			sum_time -= 20000;
			
			while( window.Getwindow().pollEvent(event) )
			{
				switch( event.type )
				{
					
				case sf::Event::Closed :
					{
						running = false;
						break;
					}

					
				case sf::Event::Resized :
					{
						break;
					}

				}
			}

			window.Getwindow().clear();
			

			// Update the current gamestate 
			gamestates[currentState]->Update();		//input handle

			//render
			gamestates[currentState]->Draw();

			window.Getwindow().display();		

		}  //end of while (sum time)

	}		//end of while(running)

}	//end of func.


