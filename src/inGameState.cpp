#include "inGameState.h"
#include "game.h"
#include <vector>
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

		if( Asteroids[i] -> GetSprite().getPosition().x < 0 || Asteroids[i] -> GetSprite().getPosition().x > 1280 || Asteroids[i] -> GetSprite().getPosition().y < 0 || Asteroids[i] -> GetSprite().getPosition().y > 720 ){
			Asteroids.erase( Asteroids.begin() + i );		//Delete the bullet that is outside the window
		}
		else{
			game -> window.Draw( Asteroids[i] -> GetSprite() );	//if its inside the window render it!
		}

	}
}

void InGameState::DrawBullets()
{
	//draw the bullets
	for (int i = 0; i < Bullets.size(); i++)
	{

		if( Bullets[i] -> GetSprite().getPosition().x < 0 || Bullets[i] -> GetSprite().getPosition().x > 1280 || Bullets[i] -> GetSprite().getPosition().y < 0 || Bullets[i] -> GetSprite().getPosition().y > 720 ){
			Bullets.erase( Bullets.begin() + i );		//Delete the bullet that is outside the window
		}
		else{
			game -> window.Draw( Bullets[i] -> GetSprite() );	//if its inside the window render it!
		}

	}
}

void InGameState::Draw()
{
	game->window.Draw(player.GetSprite());

	DrawBullets();

	DrawAsteroids();

}

InGameState::InGameState(Game *game):player(&game->window)
{
	//to reach the screen
	this->game = game;
}

InGameState::~InGameState()
{
	
}

void InGameState::colldet()
{

	for (int i = 0; i < Bullets.size(); i++)
	{

		for (int index = 0; index < Asteroids.size(); index++)
		{

			if( Collision::BoundingBoxTest( Bullets[i] -> GetSprite(), Asteroids[index] -> GetSprite() ) == 1 )
			{
				//collision 
				Asteroids[index] -> hit( 50 );
			}
		}


	}

}

void InGameState::Logic()
{

	colldet();

	//fire
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) ==  1 )
	{
		Bullets.push_back( new Bullet( player.Getmovevec() , player.Getpos() , player.Getrotation() ) );

	}

	if( Globals::random->getnumber() % 100 == 25 )
	{
		Asteroids.push_back( new Asteroid() );
	}

	for (int i = 0; i < Asteroids.size(); i++)
	{
		if( Asteroids[i] -> Gethp() <= 0 ){

			Asteroids.erase( Asteroids.begin() + i );
		}
	}

}


