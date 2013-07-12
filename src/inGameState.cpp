#include "inGameState.h"
#include "game.h"
#include "Globals.h"
#include <vector>



void InGameState::Update( )
{
	player.update();
	
}


void InGameState::Draw()
{
	Globals::window->Draw(player.GetSprite());

}

InGameState::InGameState(Game *game){
	
	this->game = game;
}

InGameState::~InGameState()
{
	
}
