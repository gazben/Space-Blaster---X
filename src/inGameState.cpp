#include <vector>

#include "inGameState.h"
#include "Globals.h"
#include "Collision.h"
#include "Level.h"

InGameState::InGameState(Game *game):player(&game->window)
{
	//Globals::Network = new network( this );

	firekeypress = false;

	//to reach the screen
	this -> game = game;

	game -> ingamestate = this;

	//coopnetwork = new network();
}

InGameState::~InGameState()
{

	for (int i = 0; i < Bullets.size(); i++)
	{
		delete Bullets[i];
		Bullets.erase( Bullets.begin() + i );	
	}

	for (int i = 0; i < Zombies.size(); i++)
	{
		delete Zombies[i];
		Zombies.erase( Zombies.begin() + i );	
	}
}

void InGameState::Update()
{
	//update the player
	player.update();
	
	//update the bullets
	for (int i = 0; i < Bullets.size(); i++)
	{
		Bullets[i] -> update();
	}

	//update the Zombies
	for (int i = 0; i < Zombies.size(); i++)
	{
		Zombies[i] -> update();
	}

	Logic();
}


void InGameState::DrawZombies()
{
	for (int i = 0; i < Zombies.size(); i++)
	{

		if( Zombies[i] -> GetSprite().getPosition().x < 0 || Zombies[i] -> GetSprite().getPosition().x > Globals::resolution -> xres || Zombies[i] -> GetSprite().getPosition().y < 0 || Zombies[i] -> GetSprite().getPosition().y > Globals::resolution -> yres || Zombies[i] -> Gethp() <= 0 )
		{
			delete Zombies[i]; 
			Zombies.erase( Zombies.begin() + i );		//Delete the bullet that is outside the window
		}
		else{	game -> window.Draw( Zombies[i] -> GetSprite() );	//if its inside the window render it!
		}


	}
}

void InGameState::DrawBullets()
{
	//draw the bullets
	for (int i = 0; i < Bullets.size(); i++)
	{

		if( Bullets[i] -> GetSprite().getPosition().x < 0 || Bullets[i] -> GetSprite().getPosition().x > Globals::resolution -> xres || Bullets[i] -> GetSprite().getPosition().y < 0 || Bullets[i] -> GetSprite().getPosition().y > Globals::resolution -> yres ){
			
			delete Bullets[i];
			Bullets.erase( Bullets.begin() + i );		//Delete the bullet that is outside the window
		}
		else{
			game -> window.Draw( Bullets[i] -> GetSprite() );	//if its inside the window render it!
		}

	}
}

//DEBUG stuff - test the tile system!
void InGameState::DrawTiles()
{
	int number = 1;
	

// 	sf::Font font;
// 	font.loadFromFile("MISTRAL.TTF");
// 	sf::Text renderNumber(std::to_string(number), font, 13);

//	renderNumber.setPosition(0, 0);

	for(unsigned int x = 0; x < map.getMap().size(); ++x ){
	
		for (unsigned int y = 0; y < map.getMap()[x].size(); ++y){

// 			renderNumber.setPosition(map.getMap()[x][y]->corners().left, map.getMap()[x][y]->corners().top);
// 
// 			game->window.Getwindow().draw(renderNumber);
// 			number++;
// 			renderNumber.setString( std::to_string(number) );

			game->window.Draw(map.getMap()[x][y]->getSprite());
		}
	
	}
}

void InGameState::Draw()
{
	DrawTiles();

	game->window.getCamera().setCenter(player.Getpos().x, player.Getpos().y);

	game->window.Getwindow().setView(game->window.getCamera().getView());

	game->window.Draw( player.GetSprite() );

	DrawBullets();

	DrawZombies();

	//for debugging
	

}

void InGameState::colldet()
{

	for (int i = 0; i < Bullets.size(); i++)
	{

		for (int index = 0; index < Zombies.size(); index++)
		{

			if( Collision::BoundingBoxTest( Bullets[i] -> GetSprite(), Zombies[index] -> GetSprite() ) == 1 )
			{
				//hit the asteroid 
				Zombies[index] -> hit( 50 );

				//delete the bullet
				Bullets.erase( Bullets.begin() + i );
				break;
			}

		}

		
	}

}

void InGameState::Logic()
{
	//collision detection
	colldet();
 

	//fire
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) || sf::Mouse::isButtonPressed(  sf::Mouse::Left ) ) 
	{

		if( firekeypress == false ){

			if ( player.Getmagazinecurrent() > 0 ){

				player.fire();
				Bullets.push_back( new Bullet( player.Getmovevec() , player.Getpos() , player.Getrotation() ) );
			}

		}

		//to disable keyrepeat
		firekeypress = true;
	}
	else{ firekeypress = false; }


	//Zombie generation
 	if( ( Globals::random->getnumber() % 100 ==  25 || 50 ) && Zombies.size() < 10 )
 	{
 		Zombies.push_back( new Zombi() );
 	}

}