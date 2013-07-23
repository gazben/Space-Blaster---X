#include "GameObject.h"
//#include "Globals.h"
#include <mymath/mymath.h>
#include "Collision.h"

GameObject::GameObject( mm::vec2 position) :pos(position)
{

}

GameObject::GameObject()
{

}

sf::Sprite& GameObject::GetSprite()
{
	return sprite;
}

void GameObject::update()
{
	
}

bool GameObject::collusion( sf::Sprite& insprite)
{
	if( Collision::BoundingBoxTest(this->sprite, insprite) == 1)
		return true;
	else
		return false;
}


