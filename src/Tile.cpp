
#include "Tile.h"
#include "Globals.h"

Tile::Tile(bool inObstacle, float centerX, float centerY, float size)
:obstacle(inObstacle), center(centerX, centerY)
{
	tex.loadFromFile("res/grass.gif");
	spr.setTexture(tex);

	spr.setPosition(centerX, centerY);
}

Tile::~Tile()
{

}

bool Tile::isObstacle()
{
	return obstacle;
}

sf::FloatRect Tile::corners()
{
	sf::FloatRect temp(center.x - 16, center.y - 16, 32, 32);
	return temp;
}

sf::Sprite& Tile::getSprite()
{
	return spr;
}
