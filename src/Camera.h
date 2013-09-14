#ifndef Camera_h__
#define Camera_h__

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Rect.hpp>

class Camera
{
private:

	sf::View* camera;

public:

	Camera(  sf::FloatRect );    

	void setCenter( float , float );  //set the center of the camera

	sf::View& getView(  );  //returns the current camera

	void move( float , float );  //moves the camera relatively to the current position

	void reset();		//resets the camera
};
#endif // Camera_h__