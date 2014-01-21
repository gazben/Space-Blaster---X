#ifndef Tile_h__
#define Tile_h__

#include <SFML/Graphics.hpp>

#include "mymath/mymath.h"

class Tile{

private:

	mm::vec2 center;
	//int lengh;  //weight of the edge
	bool obstacle;

	sf::Texture tex;
	sf::Sprite spr;

public:

	Tile(bool, float, float, float);
	~Tile();

	bool isObstacle();
	sf::FloatRect corners();
	sf::Sprite& getSprite();

};

#endif // Tile_h__