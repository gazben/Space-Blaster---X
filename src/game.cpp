#include <SFML/Graphics.hpp>
#include <vector>
#include "game.h"
#include <stdio.h>
#include "Globals.h"



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

			sf::Event event;

			while( Globals::window->Getwindow().pollEvent(event) )
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


			// Update the current gamestate
			gamestates[currentState]->Update();
			// Render current gamestate
			gamestates[currentState]->Draw();



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

	gamestates.push_back(new InGameState(this));

	currentState = INGAME;
	running = true;

}
