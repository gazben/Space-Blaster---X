#include "Buttom.h"

Buttom::Buttom(){}

Buttom::Buttom( int x , int y , std::string filename , std::string objective) :objective ( objective )
{
	font.loadFromFile( "Heavy.otf" );
	text.setFont( font );
	text.setString( objective );
	text.setColor( sf::Color::Black );
	text.setStyle( sf::Text::Bold );
	text.setPosition( x + Globals::resolution->xres / 45.0 , y + Globals::resolution->yres / 30.0);
	text.setCharacterSize( 60 );

	clicked = false;
	MouseOver = false;

	tex.loadFromFile( filename );
	sprite.setTexture( tex );
	sprite.setPosition( x , y );
}

void Buttom::isUsed( float x , float y)
{

  if( sprite.getGlobalBounds().contains( x , y ) )
  {
	  //animate the sprite ( TODO!!! )
	  MouseOver = true;

	  if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) ){
		clicked = true;
		  throw objective;
	  }
  }else{
	  MouseOver = false;
	  clicked = false;
  }

}

sf::Sprite& Buttom::getSprite()
{
	return sprite;
}

bool Buttom::isClicked()
{
	return clicked;
}

bool Buttom::isMouseOver()
{
	return MouseOver;
}

sf::Text& Buttom::getText()
{
	return text;
}

std::string Buttom::getObjective()
{
	return objective;
}

