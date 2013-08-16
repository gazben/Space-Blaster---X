#ifndef MovieState_h__
#define MovieState_h__

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>

#ifndef _DEBUG
#include "sfe/include/sfeMovie/Movie.hpp"
#endif // !_DEBUG

#include "gameState.h"
#include "Globals.h"

class Game;

class MovieState :public GameState{

private:

	//pointer to the game (for the render)
	Game *game;

#ifndef _DEBUG

	sfe::Movie intro;

#endif 

public:

	MovieState();

	MovieState(Game*);

	~MovieState();

	void Update();

	void Draw();

};

#endif // MovieState_h__