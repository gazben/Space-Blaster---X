#ifndef Asteroid_h__
#define Asteroid_h__

#include "Asteroid.h"

Asteroid::Asteroid():hp(100)
{

	//Sprite data
	tex.loadFromFile("asteroid1.png");
	sprite.setTexture(tex);
}

sf::Sprite& Asteroid::GetSprite()
{
	return sprite;
}

void Asteroid::update()
{
	pos.x += movevec.x;
	pos.y += movevec.y;

	sprite.setPosition(pos.x, pos.y);		//update the sprite position
}

#endif // Asteroid_h__
