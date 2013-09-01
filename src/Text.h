#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Globals.h"

class renderText
{
private:

	sf::Text text;
	sf::Font font;
	std::string str;

public:

	renderText( float , float , std::string = "", int = 30 );

	~renderText();

	void setColor( sf::Color );

	void setSize( int );

	void setPosition(float , float);

	void setText( std::string );

	sf::Text& getText();

};
