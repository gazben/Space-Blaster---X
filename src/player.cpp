#include "player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <mymath/mymath.h>
#include <math.h>
#include "Window.h"

sf::Sprite& Player::GetSprite()
{
	return sprite;
}

void Player::Draw() 
{
	
}

//DO NOT USE
Player::Player()
{

}

Player::Player(MainWindow* inwindow):window(inwindow)
{

	alfa = 0;
	//Sprite data
	tex.loadFromFile("playertexture.png");

	sprite.setTexture(tex);

}

//DO NOT TOUCH! math is doing its thing in here!
void Player::rotate(){

	sprite.setOrigin( tex.getSize().x / 2.0 , tex.getSize().y / 2.0 );

	movevec.x = sf::Mouse::getPosition( window->Getwindow() ).x - sprite.getPosition().x;
	movevec.y = sf::Mouse::getPosition( window->Getwindow() ).y - sprite.getPosition().y;	

	mm::vec2 unitvec(1,0);

	alfa = mm::degrees ( asin (  (float) (  movevec.x * unitvec.x + movevec.y * unitvec.y) / ( (float) (mm::length(movevec) * mm::length(unitvec)) ) ) );

	if( sf::Mouse::getPosition( window->Getwindow() ).y <= sprite.getPosition().y )
		sprite.setRotation(alfa);
	else
		sprite.setRotation( 360 - alfa + 180);

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