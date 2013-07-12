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
	Globals::window = new MainWindow();

	Game newgame;
	newgame.Run();	

	delete Globals::window;

	return 0;
}