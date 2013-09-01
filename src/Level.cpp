#include "Level.h"

Tile::Tile( bool inObstacle , float centerX, float centerY, float size)
	:obstacle(inObstacle), center( centerX , centerY )
{
}

Tile::~Tile()
{

}

bool Tile::isObstacle(  )
{
	return obstacle;
}

sf::FloatRect Tile::corners()
{
	sf::FloatRect temp( center.x - 16 , center.y - 16 , 32 , 32 );
	return temp;
}



Level::Level()
{
	float centertempX = 16;
	float centertempY = 16;

	level.resize( tileAMMOUNT );

	for (int widht = 0; widht < tileAMMOUNT; widht++)
	{
		centertempY = 16;  //back to original 
		centertempX += 32;

		level[ widht ].resize( tileAMMOUNT );
		
		for (int height = 0; height < level.size(); height++)
		{

			//TODO: obsticles to the grid!

			level[ widht ][ height ] = new Tile( false , centertempX , centertempY , tileSIZE);

			centertempY += 32;
		}

	}

	
}

Level::~Level()
{

}

bool Level::isObstacle( int height , int widht )
{
	return level[ height ][ widht ] ->isObstacle();
}
