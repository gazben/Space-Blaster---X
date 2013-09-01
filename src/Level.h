#ifndef Level_h__
#define Level_h__

#define tileSIZE 32 //size of one of the tiles
#define tileAMMOUNT 100  // how many tiles we want (ammount of tiles = tileAMMOUNT*tileAMMOUNT)

#include <vector>

#include "mymath/mymath.h"
#include "Globals.h"

//one tile of the map
class Tile{

private:

	mm::vec2 center;
	//int lengh;  //weight of the edge
	bool obstacle;

public:

	Tile( bool , float , float, float);
	~Tile(  );

	bool isObstacle(  );
	sf::FloatRect corners(  );

};


//the whole level
class Level{

private:

	std::vector < std::vector< Tile* > > level;

public:

	Level();
	~Level();

	bool isObstacle( int , int );

};


#endif // Level_h__