#ifndef game_h
#define game_h

#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include "gameState.h"
#include "inGameState.h"
#include "Window.h"

enum GState
{
	//MENU,
	INGAME
};

class Game
{
public:
	
	Game();

	~Game();

	MainWindow window;

	std::vector<GameState*> gamestates;

	//index of the current gamestate
	GState currentState;

	bool running;

	// MAIN LOOP 
	void Run();

};

#endif