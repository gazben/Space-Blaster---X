#ifndef inGameState_h__
#define inGameState_h__

#include "gameState.h"
#include "bullet.h"
#include "Asteroid.h"
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
	std::vector <Asteroid*> Asteroids;

	// Enemy Ships
	//std::vector <EnemyShip> EnemyShips; 

	// Ally Ships
	//std::vector <AllyShip> AllyShips;

	/////////
	//private functions:
	////////

		//collision detection
		void colldet();

		void DrawAsteroids();

		void DrawBullets();

protected:

	Game *game;		//to reach the window class

public:

	InGameState(Game *game);

	~InGameState();

	//updates positions 
	void Update();

	//do stuff with the exiswting objects! (for ex.: collision) 
	void Logic();

	//render the scene
	void Draw();
};


#endif // inGameState_h__
