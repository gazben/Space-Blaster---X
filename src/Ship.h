#ifndef _SHIP_H_
#define _SHIP_H_

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string.h>
#include <mymath/mymath.h>

class Ship{

private:

	//stats
	int shield;
	int hp;

	//POSITION:
	mm::vec2 pos;
	float alfa;  //rotation 

	//Sprite data:
	sf::Texture tex;
	sf::Sprite sprite;

	//private functions
	void rotate();						//mouse action handle
	void fire();

public:

	Ship( mm::vec2 pos,  std::string texturefile);	//CTOR

	sf::Sprite& GetSprite();

	//Render FNC
	void Draw();	//render function 

	void update();						//MAIN UPDATE FUNC

};

#endif