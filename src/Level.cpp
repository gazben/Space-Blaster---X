#include "Level.h"
#include "Globals.h"

//returns the center point of the requested tile
mm::vec2& getCoordinates( int x, int y){

	int xTemp = 15;
	int yTemp = 15;

	for (int xCoordTemp = 0; xTemp < x ;  xTemp += tileSIZE ){ }

	for (int yCoordTemp = 0; yTemp < x ;  yTemp += tileSIZE ){ }

	return mm::vec2( xTemp , yTemp );

}

//returns the tile-coordinates of the pixels
mm::vec2& getTileCoordinates( float x , float y ){

	int xCoordTemp = 0;
	int yCoordTemp = 0;

	for (int xTemp = 0; xTemp < x ; ++xCoordTemp , xTemp += tileSIZE ){  }

	for (int yTemp = 0; yTemp < x ; ++yCoordTemp , yTemp += tileSIZE){  }

	return mm::vec2( xCoordTemp , yCoordTemp );
}

Level::Level()
{

	//we index from 0
	float centertempX = 15;
	float centertempY = 15;

	level.resize( tileAMMOUNT );

	for (int widht = 0; widht < tileAMMOUNT; widht++)
	{

		//we index from 0
		centertempY = 15;  //back to original 
		centertempX += 31;

		level[ widht ].resize( tileAMMOUNT );
		
		for (int height = 0; height < level.size(); height++)
		{
			
			//TODO: obsticles to the grid!

			//here comes the read of the map
			level[ widht ] [ height ] = new Tile( false , centertempX , centertempY , tileSIZE);

			centertempY += 31;		//  0!
		}

	}

	
}

Level::~Level()
{

}

bool Level::isObstacle( int widht , int height )
{
	return level[ widht ][ height ] ->isObstacle();
}

Tile& Level::getTile( int widht , int height )
{
	return *level[ widht ][ height ];
}
