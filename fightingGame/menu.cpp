#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "menu.hpp"
#include "game.hpp"
#include "char_select.hpp"
#include "AboutChampion.hpp"


Menu::Menu(sf::RenderWindow *window):_windows(window)
{
	Char_Select select(_windows);
	AboutChampion aboutChampion(_windows);
	butPos_x = 250;
	butPos_y = 135;

	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("./images/MainScreen/startimage.png")) std::cout << "Error loading citybg" << std::endl;
	sf::Texture button1H;
	if (!button1H.loadFromFile("./images/MainScreen/MenuButton1Hover.png")) std::cout << "Error loading b1h" << std::endl;
	sf::Texture button1NH;
	if (!button1NH.loadFromFile("./images/MainScreen/MenuButton1.png")) std::cout << "Error loading b1" << std::endl;
	sf::Texture button2H;
	if (!button2H.loadFromFile("./images/MainScreen/MenuButton2Hover.png")) std::cout << "Error loading b2h" << std::endl;
	sf::Texture button2NH;
	if (!button2NH.loadFromFile("./images/MainScreen/MenuButton2.png")) std::cout << "Error loading b2" << std::endl;
	sf::Texture button3H;
	if (!button3H.loadFromFile("./images/MainScreen/MenuButton3Hover.png")) std::cout << "Error loading b3h" << std::endl;
	sf::Texture button3NH;
	if (!button3NH.loadFromFile("./images/MainScreen/MenuButton3.png")) std::cout << "Error loading b3" << std::endl;

	sf::RectangleShape background(sf::Vector2f(800.f, 500.f));
	background.setTexture(&backgroundTexture);

	sf::RectangleShape button1(sf::Vector2f(300.f, 85.f));
	button1.setTexture(&button1NH);
	button1.setPosition(butPos_x, butPos_y);
	sf::RectangleShape button2(sf::Vector2f(300.f, 85.f));
	button2.setTexture(&button2NH);
	button2.setPosition(butPos_x, butPos_y * 2);
	sf::RectangleShape button3(sf::Vector2f(300.f, 85.f));
	button3.setTexture(&button3NH);
	button3.setPosition(butPos_x, butPos_y * 3);


	sf::Font font;
	if (!font.loadFromFile("./images/OCR_A_Std.ttf")) std::cout << "Error loading font" << std::endl;

	sf::Text score1;
	score1.setFont(font);
	score1.setPosition(25, 25);
	score1.setCharacterSize(50);
	score1.setColor(sf::Color::Black);

	sf::Text score2;
	score2.setFont(font);
	score2.setPosition(725, 25);
	score2.setCharacterSize(50);
	score2.setColor(sf::Color::Black);


	sf::Music music;
	if (!music.openFromFile("./music/MenuMusic.ogg")) std::cout << "Error loading music" << std::endl;
	music.play();

	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("./music/ButtonFX.ogg")) std::cout << "Error loading fx" << std::endl;
	sf::Sound buttonSound;
	buttonSound.setBuffer(buffer);

	bool fxtime = false;
	sf::Vector2u getWindowSize;
	unsigned int a, b, c, d;	// 변수 이름 변경필요
	int culPos_x, culPos_y, culPos_yy;
	while (_windows->isOpen()) {
		sf::Event event;
		getWindowSize = _windows->getSize();
		culPos_x = (butPos_x*getWindowSize.x) / 800;
		culPos_y = (butPos_y*getWindowSize.y) / 500;
		culPos_yy = (65 * getWindowSize.y) / 500;
		sf::Vector2i mousepos = sf::Mouse::getPosition(*_windows);
		c = (getWindowSize.x - culPos_x * 2);
		d = (getWindowSize.y - culPos_y * 2);
		if (mousepos.x > culPos_x && mousepos.x < culPos_x + c) {
			if (mousepos.y >= culPos_y && mousepos.y <= (culPos_y + culPos_yy)) {
				button1.setTexture(&button1H);
				if (!fxtime) {
					buttonSound.play();
					fxtime = true;
				}
			}
			else if (mousepos.y >= culPos_y * 2 && mousepos.y <= (culPos_y * 2 + culPos_yy)) {
				button2.setTexture(&button2H);
				if (!fxtime) {
					buttonSound.play();
					fxtime = true;
				}
			}
			else if (mousepos.y >= culPos_y * 3 && mousepos.y <= (culPos_y * 3 + culPos_yy)) {
				button3.setTexture(&button3H);
				if (!fxtime) {
					buttonSound.play();
					fxtime = true;
				}
			}
			else {
				button1.setTexture(&button1NH);
				button2.setTexture(&button2NH);
				button3.setTexture(&button3NH);
				fxtime = false;
			}
		}
		else {
			button1.setTexture(&button1NH);
			button2.setTexture(&button2NH);
			button3.setTexture(&button3NH);
			fxtime = false;
		}

		while (_windows->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				_windows->close();
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (mousepos.x > culPos_x && mousepos.x < culPos_x + c) {
						if (mousepos.y >= culPos_y  && mousepos.y <= (culPos_y + culPos_yy)) {
							music.stop();
							int run = select.selectRun();
							music.play();
						}
						else if (mousepos.y >= culPos_y * 2 && mousepos.y <= (culPos_y * 2 + culPos_yy)) {
							/* Option */
							aboutChampion.run();
						}
						else if (mousepos.y >= culPos_y * 3 && mousepos.y <= (culPos_y * 3 + culPos_yy)) {
							_windows->close();
						}
					}
				}
			}
		}

		_windows->clear();

		_windows->draw(background);
		_windows->draw(button1);
		_windows->draw(button2);
		_windows->draw(button3);

		_windows->display();

	}
}