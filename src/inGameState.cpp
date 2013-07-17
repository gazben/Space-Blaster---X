#include "inGameState.h"
#include "game.h"
#include <vector>



void InGameState::Update( )
{
	player.update();
	
}


void InGameState::Draw()
{
	game->window.Draw(player.GetSprite());
}

InGameState::InGameState(Game *game):player(&game->window)
{
	this->game = game;
}

InGameState::~InGameState()
{
	
}
