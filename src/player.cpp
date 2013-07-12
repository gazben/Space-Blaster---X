#include "player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <mymath/mymath.h>
#include <math.h>
#include "Globals.h"

sf::Sprite& Player::GetSprite()
{
	return sprite;
}

void Player::Draw() 
{
	Globals::window->Draw(sprite);
}

Player::Player()
{
	alfa = 0;
	//Sprite data
	tex.loadFromFile("playertexture.png");

	sprite.setTexture(tex);

}

//TODO
void Player::rotate(){
	
	int angle = 0;

	sprite.setOrigin(tex.getSize().x/2.0, 0);

	angle = 1 /  tan (mm::radians(  (float) sf::Mouse::getPosition().x - pos.x  / (float) sf::Mouse::getPosition().y - pos.y));

	//Degree handle
	if(alfa + angle > 360 )
		alfa = 0;
	if(alfa + angle < 0)
		alfa = 360;

	alfa += angle;
	
	sprite.setRotation(360- alfa);
	
}

//input handle
void Player::update (){


	rotate();
	
	if( sf::Keyboard::isKeyPressed(sf::Keyboard::W) ){

		pos.y += -5;

	}

	if( sf::Keyboard::isKeyPressed(sf::Keyboard::A )){

		pos.x += -5;
	}

	if( sf::Keyboard::isKeyPressed(sf::Keyboard::S) ){

		pos.y += 5;
	}

	if( sf::Keyboard::isKeyPressed(sf::Keyboard::D )){

		pos.x += 5;
	}


	sprite.setPosition(pos.x + 1280/2.0, pos.y + 720/2.0);		//update the sprite position
}