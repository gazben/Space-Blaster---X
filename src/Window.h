#ifndef Window_h__
#define Window_h__

#include <SFML/Graphics.hpp>
#include <string>

class MainWindow{

private:

	//Window
	sf::RenderWindow *mainwindow;

public:

	MainWindow(int xres = 1280, int yres = 720){
	
	 mainwindow = new sf::RenderWindow(sf::VideoMode(xres, yres), "Space Blaster");
	}

	~MainWindow(){

		delete mainwindow;
	}

	sf::RenderWindow& Getwindow() {

		return *mainwindow;
	}

	void Draw(sf::Sprite& sprite){
	
		mainwindow->draw(sprite);
	}

	void update(){
 
		mainwindow->clear();						
		mainwindow->display();
	}

};

#endif // Window_h__
