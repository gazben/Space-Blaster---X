#include "Globals.h"


LOGFILE* Globals::log = new LOGFILE();

Random* Globals::random = new Random();

void Globals::freeGlobals()
{
	delete Globals::log;

	delete Globals::random;
}
