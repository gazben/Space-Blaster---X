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

// #ifdef _DEBUG
// 
// 	bool found = false;
// 
// 	for (int i = 0; i < tempdata.size(); i++)
// 	{
// 		if( tempdata[i].compare(str) == 1){
// 			found = true;
// 			break;
// 		}
// 	}
// 
// 	if( found == false){
	data << str.c_str() << "\n";
// 		tempdata.push_back( str );
// 	}
// 
// #endif
}

void LOGFILE::log( std::string str, double value )
{
	data << str.c_str() << " ";
	data << value << "\n";
}



