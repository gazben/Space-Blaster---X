#ifndef Globals_h__
#define Globals_h__

#include <iostream>
#include <map>

#include "Window.h"
#include "logfile.h"
#include "Random.h"

struct res
{
	int xres;
	int yres;
};

namespace Globals{

	//FUNCTIONS

	void freeGlobals();

	void INIT();


	//extern pointers 
	//DELETE THEM IN freeGlobals()!!!

	extern LOGFILE* log;	//Degug log
	
	extern Random* random;	//create random numbers

	extern  res* resolution;



};


#endif // Globals_h__
