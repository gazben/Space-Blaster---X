#ifndef Window_h__
#define Window_h__

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/View.hpp>
#include <string>


#include "Globals.h"
#include "Camera.h"

class MainWindow{

private:

	//Window
	sf::RenderWindow *mainwindow;
	Camera* camera;

public:

	MainWindow(int = 1280 , int = 720);

	~MainWindow();

	sf::RenderWindow& Getwindow();

	Camera& getCamera();

	void Draw(sf::Drawable& sprite);


};

#endif // Window_h__
