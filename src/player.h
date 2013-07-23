#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string.h>
#include <mymath/mymath.h>
#include "Window.h"


class Player{

private:

	//SPRITE DATA:
	sf::Texture tex;
	sf::Sprite sprite;

	//stats
	int shield;
	int hp;

	//window pointer for movement
	MainWindow *window;

	//POSITION:
	float alfa;  //rotation in degrees
	mm::vec2 pos;
	mm::vec2 movevec;

	//private functions
	void rotate();						//mouse action handle


public:

	Player();

	Player(MainWindow*);	//CTOR

	mm::vec2 Getpos();

	mm::vec2 Getmovevec();

	float Getrotation();

	sf::Sprite& GetSprite();

	void update();						//input handling

};

#endif