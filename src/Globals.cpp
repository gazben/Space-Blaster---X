#include "Globals.h"
#include <fstream>
#include <iostream>

LOGFILE* Globals::log = new LOGFILE();

Random* Globals::random = new Random();

res* Globals::resolution = new res;

mm::vec2* Globals::unitvec = new mm::vec2(1,0);

sf::IpAddress* Globals::ip = new sf::IpAddress();

std::string* Globals::version = new std::string( "Version: 0.1 - pre-Alfa" );


void Globals::freeGlobals()
{
	delete Globals::log;
	delete Globals::random;
	delete resolution;
	delete unitvec;
	delete ip;
	delete version;
}

void Globals::INIT()
{

	FILE* settings;
	settings = fopen("settings.cfg", "rt");
	
	//if the file does not exist the default setting will remain
	if ( settings != NULL ){
		
		//read the setting from the file
		fscanf(settings, "ResolutionX %f \n", &Globals::resolution->xres);
		fscanf(settings, "ResolutionY %f \n", &Globals::resolution->yres);
				
		//close the file
		fclose( settings );
			
		log->log( "Globals: INIT SUCCESS" );
	}
	else
	{
		log->log( "Globals: INIT FAIL" );
	}

}
