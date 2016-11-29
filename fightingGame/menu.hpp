#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Menu
{
public:
	Menu(sf::RenderWindow* window);
	sf::Texture titleTexture;
	sf::RectangleShape title;

private:
	int butPos_x, butPos_y;
	int butSize_x, butSize_y;
	bool soundOn;
	sf::RenderWindow *_windows;

};