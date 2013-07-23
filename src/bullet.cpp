#include "bullet.h"
#include "GameObject.h"
#include "Globals.h"

Bullet::Bullet( mm::vec2 invector, mm::vec2 inpos ):movevec(invector), pos(inpos)
{

	movevec.x = movevec.x / 100.0;
	movevec.y = movevec.y / 100.0;

	//Sprite data
	tex.loadFromFile("bullet1.jpg");
	sprite.setTexture(tex);
}

sf::Sprite& Bullet::GetSprite()
{
	Globals::log -> log( " getsprite " );

	return sprite;
}

void Bullet::update()
{
	pos.x += movevec.x;
	pos.y += movevec.y;
	
	sprite.setPosition(pos.x, pos.y);		//update the sprite position
}
