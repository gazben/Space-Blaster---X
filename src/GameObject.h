#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <mymath/mymath.h>
#include "Window.h"

class GameObject{

private:
	
	//position
	mm::vec2 pos;

	//SPRITE DATA:
	sf::Texture tex;
	sf::Sprite sprite;

public:

	GameObject(mm::vec2 , std::string);

	sf::Sprite& GetSprite();

	virtual void update(); 

	bool collusion(sf::Sprite&);

	void Draw();

};
#endif