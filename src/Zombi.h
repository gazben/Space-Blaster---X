#ifndef _ZOMBI_H_
#define _ZOMBI_H_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <mymath/mymath.h>

class Zombi{

private:
	//position
	mm::vec2 pos;
	mm::vec2 movevec;

	//SPRITE DATA:
	sf::Texture tex;
	sf::Sprite sprite;

	//Stats
	double hp;

public:

	Zombi();

	double Gethp();

	void Sethp(double);

	void hit(double);

	sf::Sprite& GetSprite();

	void update();
};
#endif