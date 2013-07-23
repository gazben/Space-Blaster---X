#ifndef inGameState_h__
#define inGameState_h__

#include "gameState.h"
#include "bullet.h"
#include <vector>

class Game;

class InGameState : public GameState
{
private:
	
	

	// The Players:
	Player player;
	//Player player2;		//Possible feature

	// Bullets
	std::vector <Bullet*> Bullets;

	// Asteroids
	//std::vector <Asteroid> Asteroids;

	// Enemy Ships
	//std::vector <EnemyShip> EnemyShips; 

	// Ally Ships
	//std::vector <AllyShip> AllyShips;

protected:

	Game *game;		//to reach the window class

public:

	InGameState(Game *game);

	~InGameState();

	void Update();

	void Logic();

	void Draw();
};


#endif // inGameState_h__
