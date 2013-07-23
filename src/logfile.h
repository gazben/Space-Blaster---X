#ifndef logfile_h__
#define logfile_h__

#include <iostream>
#include <fstream>
#include <set>

class LOGFILE{

private:

	
	std::ofstream data;

public:

	LOGFILE();

	~LOGFILE();

	void log(std::string);

	
};
#endif // logfile_h__