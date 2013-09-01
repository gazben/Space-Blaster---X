#include "Text.h"

renderText::renderText( float x, float y, std::string instr,  int inSize)
{
	font.loadFromFile( "MISTRAL.TTF" );

	text.setFont( font );
	text.setString( instr );
		str = instr;

	text.setColor( sf::Color::Black );
	text.setStyle( sf::Text::Regular );
	text.setCharacterSize( inSize );
	text.setPosition( x , y );

}

renderText::~renderText()
{

}

void renderText::setColor( sf::Color color)
{
	text.setColor( color );
}

void renderText::setSize( int inSize )
{
	text.setCharacterSize( inSize );
}

void renderText::setPosition( float x, float y)
{
	text.setPosition( x , y );
}

void renderText::setText( std::string inStr)
{
	str = inStr;
	text.setString( inStr );
}

sf::Text& renderText::getText()
{
	return text;
}


