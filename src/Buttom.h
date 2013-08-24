#ifndef Buttom_h__
#define Buttom_h__

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>

#include "mymath/mymath.h"
#include "Globals.h"

class Buttom{


private:

	bool clicked;
	bool MouseOver;

	sf::Texture tex;
	sf::Sprite sprite;

	sf::Font font;
	sf::Text text;

	std::string objective;

public:

	//DO NOT USE
	Buttom();

	Buttom( int x, int y, std::string filename, std::string objective);

	void isUsed(float , float);

	bool isClicked();

	bool isMouseOver();

	sf::Text& getText();

	std::string getObjective();

	sf::Sprite& getSprite();
};

#endif // Buttom_h__