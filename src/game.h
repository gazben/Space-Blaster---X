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
	
	
	MainWindow window;

	bool running;

	std::vector<GameState*> gamestates;

	//index of the current gamestate
	GState currentState;

	Game();

	~Game();
	
	// MAIN LOOP 
	void Run();

};

#endif