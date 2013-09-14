#include "Camera.h"
#include "Globals.h"

Camera::Camera( sf::FloatRect rect)
{
	camera = new sf::View( rect );

	camera->setViewport( sf::FloatRect(0.f, 0.f, 1.f, 1.f) );

}

void Camera::setCenter( float x, float y)
{
	camera->setCenter( x , y );
}

sf::View& Camera::getView()
{
	return *camera;
}

void Camera::move( float x, float y){

	camera->move( x , y );
}

void Camera::reset(){

	camera->setCenter( Globals::resolution->xres / 2.0 , Globals::resolution->yres / 2.0 );
}

