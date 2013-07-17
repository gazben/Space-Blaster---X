#include "bullet.h"
#include "GameObject.h"

Bullet::Bullet( mm::vec2 invector, mm::vec2 inpos ):movevec(invector)
{
	//Starting position
	pos.x = inpos.x;
	pos.y = inpos.y;

	
	//Sprite data
	tex.loadFromFile("bullet1.png");
	sprite.setTexture(tex);
}

void Bullet::update()
{
	pos.x += movevec.x;
	pos.y += movevec.y;
	
	sprite.setPosition(pos.x, pos.y);		//update the sprite position
}
