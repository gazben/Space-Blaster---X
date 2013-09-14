#ifndef Globals_h__
#define Globals_h__

#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Graphics/Text.hpp>

#include "mymath/mymath.h"
#include "Window.h"
#include "logfile.h"
#include "Random.h"

struct res
{
	float xres;
	float yres;
};

namespace Globals{

	//FUNCTIONS

	void freeGlobals();

	void INIT();



	//extern pointers 
	//DELETE THEM IN freeGlobals()!!!

	extern LOGFILE* log;	//Degug log
	
	extern Random* random;	//create random numbers

	extern res* resolution;

	extern mm::vec2* unitvec;

	extern sf::IpAddress* ip;

	extern std::string* version;

};


#endif // Globals_h__
