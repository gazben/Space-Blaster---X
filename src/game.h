#ifndef game_h
#define game_h

#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

#include "gameState.h"
#include "MenuState.h"
#include "inGameState.h"
#include "MovieState.h"
#include "Window.h"



class MenuState;

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

	friend class MenuState;

};

#endif