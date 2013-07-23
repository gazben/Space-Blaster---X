#include "inGameState.h"
#include "game.h"
#include <vector>
#include "bullet.h"
#include "Globals.h"

void InGameState::Update( )
{
	//update the player
	player.update();
	
	//update the bullets
	for (int i = 0; i < Bullets.size(); i++)
	{
		Bullets[i] -> update();
	}

	Logic();
}


void InGameState::Draw()
{
	game->window.Draw(player.GetSprite());

	//draw the bullets
	for (int i = 0; i < Bullets.size(); i++)
	{
		game -> window.Draw( Bullets[i] -> GetSprite() ); 

	}
}

InGameState::InGameState(Game *game):player(&game->window)
{
	//to reach the screen
	this->game = game;
}

InGameState::~InGameState()
{
	
}

void InGameState::Logic()
{
	//fire
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) ==  1 )
	{
		Bullets.push_back( new Bullet( player.Getmovevec() , player.Getpos() ) );

	}
}
