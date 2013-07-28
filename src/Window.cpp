#include "Window.h"
#include <SFML/Graphics.hpp>

sf::Color white(255,255,255,255);

MainWindow::MainWindow(int xres, int yres){

	xres = Globals::resolution -> xres,
	yres = Globals::resolution -> yres;


	mainwindow = new sf::RenderWindow(sf::VideoMode(xres, yres), "Space Blaster");

}

MainWindow::~MainWindow(){}

sf::RenderWindow& MainWindow::Getwindow() {

	return *mainwindow;
}

void MainWindow::Draw(sf::Sprite& sprite){

	mainwindow->draw(sprite);
}
