#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include<Windows.h>

class Char_Select
{
public:
	Char_Select(sf::RenderWindow*window);
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Texture p1Pointer;
	sf::Texture p2Pointer;
	sf::RectangleShape p1;
	sf::RectangleShape p2;
	int selectRun();
	int newCharactor(int flag);

private:
	int pos1P_x, pos1P_y, pos2P_x, pos2P_y;
	int selectedP1, selectedP2;
	int selectedChar;
	sf::RenderWindow *_windows;



};