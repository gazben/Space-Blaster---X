#ifndef Level_h__
#define Level_h__

#define tileSIZE 32 //size of one of the tiles
#define tileAMMOUNT 100  // how many tiles we want (ammount of tiles = tileAMMOUNT*tileAMMOUNT)

#include <vector>

#include "mymath/mymath.h"
#include "Globals.h"
#include "Tile.h"

//one tile of the map

mm::vec2& getCoordinates( int , int );		//converts the tile numbers into pixels 

mm::vec2& getTileCoordinates( float , float ); //converts the tile coordinates into tilecoordinates

//the whole level
class Level{

private:

	std::vector < std::vector< Tile* > > level;

public:

	Level();
	~Level();

	Tile& getTile ( int  , int );

	bool isObstacle( int , int );

	friend mm::vec2& getCoordinates( int x, int y);

};


#endif // Level_h__