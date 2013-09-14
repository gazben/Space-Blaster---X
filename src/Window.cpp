#include "Window.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>


MainWindow::MainWindow(int xres, int yres){

	xres = Globals::resolution -> xres,
	yres = Globals::resolution -> yres;

	sf::FloatRect cameraView( 0 , 0 , Globals::resolution->xres , Globals::resolution->yres ); 

	mainwindow = new sf::RenderWindow(sf::VideoMode(xres, yres), "Space Blaster");

	camera = new Camera( cameraView );

	mainwindow->setView( camera->getView() );

}

MainWindow::~MainWindow(){

	delete mainwindow;
	delete camera;
}

sf::RenderWindow& MainWindow::Getwindow() {

	return *mainwindow;
}

void MainWindow::Draw(sf::Drawable& sprite){

	mainwindow->draw(sprite);
}

Camera& MainWindow::getCamera(){
	return *camera;
}
