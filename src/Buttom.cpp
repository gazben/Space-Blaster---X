#include "Buttom.h"

Buttom::Buttom(){}

Buttom::Buttom( int x , int y , std::string filename , std::string objective) :objective ( objective )
{
	clicked = false;

	tex.loadFromFile( filename );
	sprite.setTexture( tex );
	sprite.setPosition( x , y );
}

void Buttom::isUsed( float x , float y)
{

  if( sprite.getGlobalBounds().contains( x , y ) )
  {
	  //animate the sprite ( TODO!!! )

	  if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) ){
		clicked = true;
		  throw objective;
	  }
  }

}

sf::Sprite& Buttom::getSprite()
{
	return sprite;
}

