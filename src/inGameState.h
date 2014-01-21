#ifndef inGameState_h__
#define inGameState_h__

#include <vector>

#include "gameState.h"
#include "Zombi.h"
#include "game.h"
#include "bullet.h"
#include "player.h"
#include "Level.h"

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
	std::vector <Zombi*> Zombies;

	//the level itself
	Level map;


	//Other things:
	bool firekeypress;

	/////////
	//private functions:
		void colldet();
		void DrawZombies();
		void DrawBullets();
		void DrawTiles();  //for testing the camera and the tile system

protected:

	Game *game;		//to reach the window class

public:

	InGameState(Game *game);

	~InGameState();

	//updates positions 
	void Update();

	//do stuff with the existing objects! (for ex.: collision) 
	void Logic();

	//render the scene
	void Draw();

	friend class network;
	friend class MenuState;
};

#endif // inGameState_h__
