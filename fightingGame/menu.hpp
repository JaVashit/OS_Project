#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Menu
{
public:
	Menu(sf::RenderWindow *window);


private:
	int butPos_x, butPos_y;
	sf::RenderWindow *_windows;

};