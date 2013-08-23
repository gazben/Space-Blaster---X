#include "player.h"



//#include "game.h"

sf::Sprite& Player::GetSprite()
{
	return sprite;
}

//DO NOT USE
Player::Player(){}

Player::Player(MainWindow* inwindow , std::string inPlayername):window(inwindow), playername(inPlayername)
{

	magazinesize = 100;
	magazinecurrent = magazinesize;

	pos.x =  Globals::resolution -> xres / 2.0;
	pos.y =  Globals::resolution -> yres / 2.0;

	alfa = 0;

	//Sprite data
	tex.loadFromFile("playertexture.png");
	sprite.setPosition( pos.x , pos.y );
	sprite.setTexture(tex);

}

//DO NOT TOUCH! math is doing its thing in here!
void Player::rotate(){

	sprite.setOrigin( tex.getSize().x / 2.0 , tex.getSize().y / 2.0 );

	movevec.x = sf::Mouse::getPosition( window->Getwindow() ).x - sprite.getPosition().x;
	movevec.y = sf::Mouse::getPosition( window->Getwindow() ).y - sprite.getPosition().y;	

	alfa = mm::degrees ( asin (  (float) (  movevec.x * Globals::unitvec->x + movevec.y * Globals::unitvec->y) / ( (float) (mm::length(movevec) * mm::length( *Globals::unitvec ) ) ) ) );


	if( sf::Mouse::getPosition( window->Getwindow() ).y <= sprite.getPosition().y )
		sprite.setRotation(alfa);
	else
		sprite.setRotation( 360 - alfa + 180);

}

//input handle for the player - NOT FINAL
void Player::update (){

	rotate();
	
	if( sf::Keyboard::isKeyPressed(sf::Keyboard::W) ){

		
			pos.y -= 5;
//  		pos.x +=  (float) movevec.x / ( 20.0);
//  		pos.y +=  (float) movevec.y / ( 20.0);
	}

	if( sf::Keyboard::isKeyPressed(sf::Keyboard::A )){

		pos.x -= 5;
// 		pos.x -= (float) movevec.x / ( 20 * ( (float) movevec.length() ) );
// 		pos.y += (float) movevec.y / ( 20 * ( (float) movevec.length() ) );
	}

	if( sf::Keyboard::isKeyPressed(sf::Keyboard::S) ){

		pos.y += 5;
// 		pos.x -= (float) movevec.x / ( 20 * ( 2 * (float) movevec.length() ) );
// 		pos.y -= (float) movevec.y / ( 20 * ( 2 * (float) movevec.length() ) );
	}

	if( sf::Keyboard::isKeyPressed(sf::Keyboard::D )){

		pos.x += 5;
// 		pos.x += (float) movevec.x / ( 20 * ( (float) movevec.length() ) );
// 		pos.y -= (float) movevec.y / ( 20 * ( (float) movevec.length() ) );
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

float Player::Getrotation()
{
	return alfa;
}

void Player::fire()
{

   magazinecurrent--;
}

int Player::Getmagazinesize()
{
	return magazinesize;
}

int Player::Getmagazinecurrent()
{
	return magazinecurrent;
}

