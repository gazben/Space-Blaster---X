#include <vector>

#include "inGameState.h"
#include "game.h"
#include "bullet.h"
#include "Globals.h"
#include "Random.h"
#include "Collision.h"


void InGameState::Update( )
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

void InGameState::Draw()
{
	game->window.Draw( player.GetSprite() );

	DrawBullets();

	DrawZombies();

}

InGameState::InGameState(Game *game):player(&game->window)
{

	firekeypress = false;

	//to reach the screen
	this->game = game;
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
// 	if( Globals::random->getnumber() % 100 ==  25 || 50 )
// 	{
// 		Zombies.push_back( new Zombi() );
// 	}

}


