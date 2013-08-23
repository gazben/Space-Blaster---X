#ifndef Buttom_h__
#define Buttom_h__

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "mymath/mymath.h"

class Buttom{


private:

	bool clicked;

	sf::Texture tex;
	sf::Sprite sprite;


	std::string objective;

public:

	//DO NOT USE
	Buttom();

	Buttom( int x, int y, std::string filename, std::string objective);

	void isUsed(float , float);

	sf::Sprite& getSprite();
};

#endif // Buttom_h__