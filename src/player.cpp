#include "player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <mymath/mymath.h>
#include <math.h>
#include "Window.h"
#include "game.h"

sf::Sprite& Player::GetSprite()
{
	return sprite;
}

//DO NOT USE
Player::Player(){}

Player::Player(MainWindow* inwindow):window(inwindow)
{
	pos.x =  1280/2.0;
	pos.y =  720/2.0;

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

//input handle for the player - NOT FINAL
void Player::update (){


	rotate();
	
	if( sf::Keyboard::isKeyPressed(sf::Keyboard::W) ){

		pos.x +=  (float) movevec.x / ( 20 * (float) movevec.length() );
		pos.y +=  (float) movevec.y / ( 20 * (float) movevec.length() );
	}

	if( sf::Keyboard::isKeyPressed(sf::Keyboard::A )){

		pos.x -= (float) movevec.x / ( 20 * ( (float) movevec.length() ) );
		pos.y += (float) movevec.y / ( 20 * ( (float) movevec.length() ) );
	}

	if( sf::Keyboard::isKeyPressed(sf::Keyboard::S) ){

		pos.x -= (float) movevec.x / ( 20 * ( 2 * (float) movevec.length() ) );
		pos.y -= (float) movevec.y / ( 20 * ( 2 * (float) movevec.length() ) );
	}

	if( sf::Keyboard::isKeyPressed(sf::Keyboard::D )){

		pos.x += (float) movevec.x / ( 20 * ( (float) movevec.length() ) );
		pos.y -= (float) movevec.y / ( 20 * ( (float) movevec.length() ) );
	}


	sprite.setPosition(pos.x, pos.y);		//update the sprite position
}

mm::vec2 Player::Getpos()
{
	return pos;
}

mm::vec2 Player::Getmovevec()
{
	return movevec;
}
