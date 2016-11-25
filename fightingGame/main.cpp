#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "menu.hpp"
#include "Opening.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 500), "game 100");
	//Opening opening(&window);
	Menu menu(&window);
	
	/**********************************************/
	/*Main의 코드는 menu클래스로 전환하였습니다.*/
	/*********************************************/
	
    return -1;
}