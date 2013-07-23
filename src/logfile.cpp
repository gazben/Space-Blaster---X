#include "logfile.h"
#include <iostream>
#include <fstream>

LOGFILE::LOGFILE()
{
	data.open("Debuglog.txt");
}

LOGFILE::~LOGFILE()
{
	data.close();
}

void LOGFILE::log( std::string str)
{
	data << str.c_str() << "\n";
}

