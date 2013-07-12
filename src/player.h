#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string.h>
#include <mymath/mymath.h>


using namespace sf;
using std::string;

class Player{

private:

	//POSITION:
	
	mm::vec2 pos;
	float alfa;  //rotation 


	//Sprite data:
	Texture tex;
	Sprite sprite;

public:
	
	Player();	//CTOR

	sf::Sprite& GetSprite();

	void rotate();						//mouse action handle
	void update();						//input handling

	void fire();

	void Draw();	//render function 


};

#endif