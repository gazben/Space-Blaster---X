#include "Zombi.h"
#include "Globals.h"

Zombi::Zombi():hp(100)
{
	//starting position for the asteroid
	//pos.x = Globals::random -> getnumber() % Globals::resolution -> xres;
	//pos.y = 0;

	//initial speed for the asteroid
	movevec.x = 0;
	movevec.y = 10;

	sprite.setPosition( pos.x, pos.y );

	//Sprite data
	if(Globals::random->getnumber() % 3 == 1)
		tex.loadFromFile("asteroid1.png");
	
	if(Globals::random->getnumber() % 3 == 2)
		tex.loadFromFile("asteroid2.png");

	if(Globals::random->getnumber() % 3 == 0)
		tex.loadFromFile("asteroid3.png");
	
	sprite.setTexture(tex);
}

sf::Sprite& Zombi::GetSprite()
{
	return sprite;
}

void Zombi::update()
{
	pos.x += movevec.x;
	pos.y += movevec.y;

	sprite.setPosition( pos.x , pos.y );		//update the sprite position
}

double Zombi::Gethp()
{
	return hp;
}

void Zombi::Sethp(double inhp)
{
	hp = inhp;
}

void Zombi::hit(double inhp)
{
	hp -= inhp;
}

