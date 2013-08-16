#ifndef _BULLET_H_
#define _BULLET_H_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "mymath/mymath.h"
#include "GameObject.h"


class Bullet{

private:
	//position
	mm::vec2 pos;
	mm::vec2 movevec;
	float alfa;

	//SPRITE DATA:
	sf::Texture tex;
	sf::Sprite sprite;


public:

	Bullet(mm::vec2 invector, mm::vec2 inpos, float inrotation);

	sf::Sprite& GetSprite();

	void update();
};
#endif