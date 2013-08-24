#include <SFML/Graphics.hpp>
#include <vector>
#include "game.h"

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

Game::~Game()
{
	running = false;

	for (int i=0; i < gamestates.size(); i++)
		delete gamestates[i];

}

//INIT
Game::Game()
{
	Globals::log->log( "GAME INIT SUCCESS" );
	
#ifndef _DEBUG
	gamestates.push_back( new MovieState( this ) );
#endif

	gamestates.push_back( new MenuState( this ) );
	gamestates.push_back( new InGameState( this ) );

#ifndef _DEBUG
	currentState = MOVIE;
#else
	currentState = MENU;
#endif
	
	running = true;

}
