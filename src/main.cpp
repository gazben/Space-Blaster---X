// ******************************************************************************
// *	Space blaster 2.0 minigame --- main.cpp
// *	Copyright (c) 2013 KSZK Game-Dev/ Gazben (see LICENSE.md for full license)
// *
// *	Entry point for the game, initializes SFML and subsystems.
// *
// ******************************************************************************

#include "game.h"
#include "Globals.h"

int main(char** argc, int argv)
{
	Globals::INIT();

	Game newgame;
	newgame.Run();	

	Globals::freeGlobals();

	return 0;
}