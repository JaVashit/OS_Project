#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "preferences.hpp"

Preferences::Preferences(sf::RenderWindow *tywindow):_tywindows(tywindow)
{

	_width = tywindow->getSize().x;
	_height = tywindow->getSize().y;
	keyPos_x = 50;
	keyPos_y = 50;
}
bool Preferences:: keyboard(bool on)
{
	sf::Texture option_img;
	if (!option_img.loadFromFile("./images/option/option_bg.png")) std::cout << "Error loading keyboard" << std::endl;
	sf::Texture sound_on;
	if (!sound_on.loadFromFile("./images/option/soundon.png")) std::cout << "Error loading keyboard" << std::endl;
	sf::Texture sound_off;
	if (!sound_off.loadFromFile("./images/option/soundoff.png")) std::cout << "Error loading keyboard" << std::endl;
	sf::Texture exit_Button;
	if (!exit_Button.loadFromFile("./images/option/ExitButton.png")) std::cout << "Error loading keyboard" << std::endl;
	sf::Texture exit_ButtonH;
	if (!exit_ButtonH.loadFromFile("./images/option/ExitButtonHover.png")) std::cout << "Error loading keyboard" << std::endl;

	sf::RectangleShape option(sf::Vector2f(800.f, 500.f));
	option.setTexture(&option_img);

	sf::RectangleShape sound(sf::Vector2f(120.f, 58.f));
	sound.setTexture(&sound_on);
	sound.setPosition(340, 110);
	sf::RectangleShape exit(sf::Vector2f(150.f, 40.f));
	exit.setTexture(&exit_Button);
	exit.setPosition(625, 440);


	bool soundOn = true;
	bool fxtime = false;
	sf::Vector2u getWindowSize;
	int culPos_x ;
	int culPos_y ;
	int culPos_yy;
	while (_tywindows->isOpen()) {
		sf::Event event;
		getWindowSize = _tywindows->getSize();
		sf::Vector2i mousepos = sf::Mouse::getPosition(*_tywindows);
		culPos_x = (150*getWindowSize.x) / 800;
		culPos_y = (40*getWindowSize.y) / 500;
		culPos_yy = (85 * getWindowSize.y) / 500;

		if (mousepos.x > 625 && mousepos.x <= 775 && mousepos.y > 440 && mousepos.y < 480 )  //exit ��ġ�� ���콺�� �÷����� ��ư ȿ��
			exit.setTexture(&exit_ButtonH);
		else
			exit.setTexture(&exit_Button);				//�ƴϸ� ���� ��ư 

		while (_tywindows->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				_tywindows->close();
			if (event.type == sf::Event::MouseButtonPressed) {				//���ʹ�ư ��������
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (mousepos.x >= 400 && mousepos.x <= 460 ) {			//����Ŀ on x_�ڸ�

						if (mousepos.y >=110 && mousepos.y <= 168)			//����Ŀ on y_�ڸ�
						{
							sound.setTexture(&sound_off);
							soundOn = false;
						}
					}
					else{
						sound.setTexture(&sound_on);
						soundOn = true;
					}

					if(mousepos.x > 625 && mousepos.x <= 775 && mousepos.y > 440 && mousepos.y < 480)		//����Ŀ off x_�ڸ�
					{
						if(soundOn == true)
							return true;
						else
							return false;
					}
				}
			}
		}




		_tywindows->clear();
		_tywindows->draw(option);
		_tywindows->draw(sound);
		_tywindows->draw(exit);
		_tywindows->display();

	}
}



