#ifndef MenuState_h__
#define MenuState_h__

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Color.hpp>

#include "Globals.h"
#include "game.h"
#include "gameState.h"
#include "bullet.h"
#include "Buttom.h"
#include "Text.h"

class Game;

class MenuState : public GameState
{
private:
	
	//Texts:
	renderText version;
	renderText ipText;
	renderText playernameText;

	//Network options
	bool coop;
	bool host;
	bool join;

	std::string playername;
		bool nameIN;
	std::string ipconnect;
		bool ipIN;

	//to reach the window and the draw function
	Game *game;

	//buttons on the screen
	std::vector <Buttom*> Buttons;

	//backgroung sprite
	sf::Texture tex;
	sf::Sprite sprite;

	//Private functions:
	void keyboardInput( renderText& , std::string& , bool& );

public:

	MenuState(Game *game);

	~MenuState();

	void Update();
		

	void Draw();

	friend Buttom;
};
#endif // MenuState_h__
