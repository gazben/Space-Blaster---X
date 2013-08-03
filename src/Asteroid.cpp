#ifndef Asteroid_h__
#define Asteroid_h__

#include "Asteroid.h"
#include "Globals.h"

Asteroid::Asteroid():hp(100)
{
	//starting position for the asteroid
	pos.x = Globals::random -> getnumber() % Globals::resolution -> xres;
	pos.y = 0;

	//initial speed for the asteroid
	movevec.x = 0;
	movevec.y = 10;

	sprite.setPosition( pos.x, pos.y );

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

	sprite.setPosition( pos.x , pos.y );		//update the sprite position
}

double Asteroid::Gethp()
{
	return hp;
}

void Asteroid::Sethp(double inhp)
{
	hp = inhp;
}

void Asteroid::hit(double inhp)
{
	hp -= inhp;
}

#endif // Asteroid_h__
