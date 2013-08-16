#include "bullet.h"
#include "GameObject.h"
#include "Globals.h"

Bullet::Bullet( mm::vec2 invector, mm::vec2 inpos, float inrotation ):movevec(invector), pos(inpos), alfa(inrotation)
{

	movevec.x = 5 * cos( mm::radians( alfa ) ) - 0 * sin( mm::radians( alfa ) ) ;
	movevec.y = 5 * sin( mm::radians( alfa ) ) + 0 * cos( mm::radians( alfa ) ) ;

	//Sprite data
	tex.loadFromFile("bullet1.jpg");
	sprite.setTexture(tex);

	//Same rotation as the ship
	sprite.setOrigin( tex.getSize().x / 2.0 , tex.getSize().y / 2.0 );
	sprite.setRotation( alfa + 90 );
}

sf::Sprite& Bullet::GetSprite()
{
	return sprite;
}

void Bullet::update()
{
	pos.x += movevec.x;
	pos.y += movevec.y;
	
	sprite.setPosition(pos.x, pos.y);		//update the sprite position
}
