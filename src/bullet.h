#ifndef _BULLET_H_
#define _BULLET_H_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <mymath/mymath.h>
#include "GameObject.h"

class Bullet :public GameObject{

private:

	mm::vec2 movevec;

public:

	Bullet(mm::vec2 invector, mm::vec2 inpos);

	void update();
};
#endif