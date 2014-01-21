#include "Buttom.h"

sf::Color myYellow(255, 247, 0, 255);
sf::Color myRed(189, 13, 13 , 255);

Buttom::Buttom(){}

Buttom::Buttom( int x , int y , std::string filename , std::string objective) :objective ( objective )
{
	font.loadFromFile( "Heavy.otf" );
	text.setFont( font );
	text.setString( objective );
	text.setColor( sf::Color::Yellow );
	text.setStyle( sf::Text::Bold );
	text.setPosition( x + Globals::resolution->xres / 65.0 , y + Globals::resolution->yres / 50.0);
	text.setCharacterSize( 30 );

	clicked = false;
	MouseOver = false;

	tex.loadFromFile( filename );
	sprite.setTexture( tex );
	sprite.setPosition( x , y );
	sprite.setColor( sf::Color( 255, 255, 255, 200 ) );
	sprite.setScale(0.6, 0.2);
}

void Buttom::isUsed( float x , float y)
{
	if (MouseOver)
		text.setColor(myRed);
	else
		text.setColor(myYellow);


  if( sprite.getGlobalBounds().contains( x , y ) )
  {
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

