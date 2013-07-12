#ifndef _ASTEROID_H_
#define _ASTEROID_H_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <mymath/mymath.h>
#include "GameObject.h"

class Asteroid :GameObject{

private:

	int hp;

public:

	Asteroid();

	~Asteroid();

	void explode();

};
#endif