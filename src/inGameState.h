#ifndef inGameState_h__
#define inGameState_h__

#include "gameState.h"
#include "bullet.h"
#include <vector>

class Game;

class InGameState : public GameState
{
private:
	
	Game *game;

	// The Players:
	Player player;
	//Player player2;		//Possible feature

	// Bullets
	std::vector <Bullet> Bullets;

	// Asteroids
	//std::vector <Asteroid> Asteroids;

	// Enemy Ships
	//std::vector <EnemyShip> EnemyShips; 

	// Ally Ships
	//std::vector <AllyShip> AllyShips;

public:
	InGameState(Game *game);
	~InGameState();

	void Update();

	void Draw();
};


#endif // inGameState_h__
