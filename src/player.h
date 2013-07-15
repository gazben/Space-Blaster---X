#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string.h>
#include <mymath/mymath.h>
#include "Window.h"

class Player{

private:

	MainWindow *window;

	//POSITION:
	mm::vec2 movevec;
	mm::vec2 pos;
	float alfa;  //rotation 


	//Sprite data:
	sf::Texture tex;
	sf::Sprite sprite;

public:

	Player();

	Player(MainWindow*);	//CTOR

	sf::Sprite& GetSprite();

	void rotate();						//mouse action handle
	void update();						//input handling

	void fire();

	void Draw();	//render function 


};

#endif