#include "Window.h"
#include <SFML/Graphics.hpp>

MainWindow::MainWindow(int xres, int yres){

	mainwindow = new sf::RenderWindow(sf::VideoMode(xres, yres), "Space Blaster");

}

MainWindow::~MainWindow(){}

sf::RenderWindow& MainWindow::Getwindow() {

	return *mainwindow;
}

void MainWindow::Draw(sf::Sprite& sprite){

	mainwindow->draw(sprite);
}

void MainWindow::update(){

	mainwindow->clear();						
	mainwindow->display();
}