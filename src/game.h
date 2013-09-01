#ifndef game_h
#define game_h

#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

#include "gameState.h"
#include "MenuState.h"
#include "inGameState.h"
#include "MovieState.h"
#include "Window.h"
#include "Network.h"



class MenuState;
class InGameState;
class network;

enum GState
{

#ifndef _DEBUG

	MOVIE, MENU, INGAME

#else

	MENU, INGAME

#endif // !RELEASE

};

class Game
{
private:
	sf::Event event;

	//Pointer to the gamestates
 	InGameState* ingamestate;
 	MenuState* menustate;
	network* coopnetwork;

public:
	
	Game();

	~Game();

	//the render window
	MainWindow window;

	//gamestates
	std::vector<GameState*> gamestates;

	//index of the current gamestate
	GState currentState;		//you have to switch it to run another gamestate

	//is the game running?
	bool running;

	// MAIN LOOP 
	void Run();

	//friends:
	friend class MenuState;
	friend class InGameState;
	friend class network;
};

#endif