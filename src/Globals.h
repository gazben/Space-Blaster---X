#ifndef Globals_h__
#define Globals_h__

#include <iostream>
#include "Window.h"
#include "logfile.h"
#include "Random.h"

namespace Globals{

	void freeGlobals();

	extern LOGFILE* log;	//Degug log
	
	extern Random* random;	//create random numbers

};


#endif // Globals_h__
