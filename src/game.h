#ifndef game_h
#define game_h

#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include "gameState.h"
#include "inGameState.h"

enum GState
{
	//MENU,
	INGAME
};

class Game
{
public:


	bool running;

	std::vector<GameState*> gamestates;

	GState currentState;

	Game();
	~Game();
	
	// MAIN LOOP 
	void Run();
};

#endif