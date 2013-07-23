#include "Random.h"

Random::Random()
{
	srand( time( NULL ) );
}

Random::~Random()
{

}

int Random::getnumber()
{
	return rand() % 100;
}