#ifndef MenuState_h__
#define MenuState_h__

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>


#include "gameState.h"
#include "bullet.h"
#include "Buttom.h"


class Game;

class MenuState : public GameState
{
private:


	Game *game;


	//buttons on the screen
	std::vector <Buttom*> Buttons;

	//backgroung sprite
	sf::Texture tex;
	sf::Sprite sprite;

public:

	MenuState(Game *game);

	~MenuState();

	void Update();

	void Draw();

	friend Buttom;
};


#endif // MenuState_h__
