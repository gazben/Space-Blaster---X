#ifndef _BULLET_H_
#define _BULLET_H_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <mymath/mymath.h>
#include "GameObject.h"

class Bullet{

private:
	//position
	mm::vec2 pos;
	mm::vec2 movevec;

	//SPRITE DATA:
	sf::Texture tex;
	sf::Sprite sprite;


public:

	Bullet(mm::vec2 invector, mm::vec2 inpos);

	sf::Sprite& GetSprite();

	void update();
};
#endif