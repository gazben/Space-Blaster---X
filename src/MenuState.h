#ifndef MenuState_h__
#define MenuState_h__

#include "gameState.h"
#include "bullet.h"
#include <vector>

class Game;

class MenuState : public GameState
{
private:

	Game *game;

	

public:
	MenuState(Game *game);
	~MenuState();

	void Update();

	void Draw();
};


#endif // MenuState_h__
