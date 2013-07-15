#ifndef Window_h__
#define Window_h__

#include <SFML/Graphics.hpp>
#include <string>

class MainWindow{

private:

	//Window
	sf::RenderWindow *mainwindow;

public:

	MainWindow(int xres = 1280, int yres = 720);

	~MainWindow();

	sf::RenderWindow& Getwindow();

	void Draw(sf::Sprite& sprite);


};

#endif // Window_h__
