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

	//update the asteroids
	for (int i = 0; i < Asteroids.size(); i++)
	{
		Asteroids[i] -> update();
	}

	Logic();
}


void InGameState::DrawAsteroids()
{
	for (int i = 0; i < Asteroids.size(); i++)
	{

		if( Asteroids[i] -> GetSprite().getPosition().x < 0 || Asteroids[i] -> GetSprite().getPosition().x > Globals::resolution -> xres || Asteroids[i] -> GetSprite().getPosition().y < 0 || Asteroids[i] -> GetSprite().getPosition().y > Globals::resolution -> yres || Asteroids[i] -> Gethp() <= 0 )
		{
			delete Asteroids[i]; 
			Asteroids.erase( Asteroids.begin() + i );		//Delete the bullet that is outside the window
		}
		else{	game -> window.Draw( Asteroids[i] -> GetSprite() );	//if its inside the window render it!
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

	DrawAsteroids();

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
		
	for (int i = 0; i < Asteroids.size(); i++)
	{
		delete Asteroids[i];
		Asteroids.erase( Asteroids.begin() + i );	
	}
}

void InGameState::colldet()
{

	for (int i = 0; i < Bullets.size(); i++)
	{

		for (int index = 0; index < Asteroids.size(); index++)
		{

			if( Collision::BoundingBoxTest( Bullets[i] -> GetSprite(), Asteroids[index] -> GetSprite() ) == 1 )
			{
				//hit the asteroid 
				Asteroids[index] -> hit( 50 );

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


	//asteriod generation
	if( Globals::random->getnumber() % 100 ==  25 || 50 )
	{
		Asteroids.push_back( new Zombi() );
	}

}


