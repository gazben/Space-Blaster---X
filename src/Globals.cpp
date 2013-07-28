#include "Globals.h"
#include <fstream>
#include <iostream>


LOGFILE* Globals::log = new LOGFILE();

Random* Globals::random = new Random();

res* Globals::resolution = new res;

void Globals::freeGlobals()
{
	delete Globals::log;

	delete Globals::random;

	delete resolution;
}

void Globals::INIT()
{
	FILE* settings;


	settings = fopen("settings.cfg", "rt");

	//if the file does not exist the default setting will remain
	if ( settings != NULL )
	{
		//read the setting from the file
		fscanf(settings, "ResolutionX %d \n", &Globals::resolution->xres);
		fscanf(settings, "ResolutionY %d \n", &Globals::resolution->yres);


		//close the file
		fclose( settings );

		log->log( " INIT SUCCESS" );
	}
	else
	{
		log->log( " INIT FAIL " );
	}

}
