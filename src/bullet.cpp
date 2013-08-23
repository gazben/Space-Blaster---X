#include "bullet.h"
#include "GameObject.h"

Bullet::Bullet( mm::vec2 invector, mm::vec2 inpos, float inrotation ):movevec(invector), pos(inpos), alfa(inrotation)
{
	//the power of the mighty brute force
	alfa = mm::degrees ( asin (  (float) (  movevec.x * Globals::unitvec->x + movevec.y * Globals::unitvec->y) / ( (float) (mm::length(movevec) * mm::length( *Globals::unitvec ) ) ) ) );
// 
// 	if(alfa < 0)
// 		alfa = alfa + 360;
// 
// 	int alfatemp = alfa;
// 	alfatemp = alfatemp % 360;
// 	alfa = alfatemp;

// 	if ( alfa > 180 && alfa < 360 )
// 	{
// 		alfa = 360 - alfa;
// 	}
	//brute force end

		movevec.x = 5 * cos( mm::radians( alfa ) ) - 0 * sin( mm::radians( alfa ) ) ;
		movevec.y = 5 * sin( mm::radians( alfa ) ) + 0 * cos( mm::radians( alfa ) ) ;

	//Sprite data
	tex.loadFromFile("bullet1.jpg");
	sprite.setTexture(tex);

	//Same rotation as the ship
	sprite.setOrigin( tex.getSize().x / 2.0 , tex.getSize().y / 2.0 );
	sprite.setRotation( alfa + 90 );

	Globals::log->log( "rotation:", alfa );
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

mm::vec2 Bullet::getPos()
{
	return pos;
}

void Bullet::setPos( int x, int y )
{
	pos.x = x;

	pos.y = y;
}

mm::vec2 Bullet::getMovevec()
{
	return movevec;
}

void Bullet::setMovevec( int x, int y )
{

	movevec.x = x;
	movevec.y = y;
}