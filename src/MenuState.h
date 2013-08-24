#ifndef MenuState_h__
#define MenuState_h__

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Globals.h"
#include "game.h"
#include "gameState.h"
#include "bullet.h"
#include "Buttom.h"

class Game;

class MenuState : public GameState
{
private:
	
	//FONTS
	sf::Font normaltext;

	sf::Text version;
	
	//Network options
	sf::Text ipadress;
	bool coop;
	bool host;
	bool join;

	sf::Text playernameText;
	std::string playername;
		bool nameIN;
	sf::Text ipText;
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
	void keyboardInput( sf::Text& , std::string& , bool& );

public:

	MenuState(Game *game);

	~MenuState();

	void Update();
		

	void Draw();

	friend Buttom;
};
#endif // MenuState_h__
