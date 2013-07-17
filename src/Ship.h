#ifndef _SHIP_H_
#define _SHIP_H_

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string.h>
#include <mymath/mymath.h>
#include "GameObject.h"

class Ship :public GameObject{

private:

	//stats
	int shield;
	int hp;

	//POSITION:
	float alfa;  //rotation 

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