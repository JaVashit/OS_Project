#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "menu.hpp"
#include "game.hpp"
#include "char_select.hpp"
#include "AboutChampion.hpp"
#include "Preferences.hpp"

Menu::Menu(sf::RenderWindow *window):_windows(window)
{
	soundOn = true;

	Char_Select select(_windows);
	AboutChampion about(_windows);
	Preferences preferences(_windows);
	
	// ù��° ��ư�� ������ ��ǥ
	butPos_x = 250;
	butPos_y = 100;
	butSize_x = 300;
	butSize_y = 85;

	// menu�� â�� ���� ���� �̹����� �ҷ���(���, ��ư, Ȱ��ȭ ��ư)
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
	if (!button3H.loadFromFile("./images/MainScreen/MenuButton2Hover.png")) std::cout << "Error loading b3h" << std::endl;
	sf::Texture button3NH;
	if (!button3NH.loadFromFile("./images/MainScreen/MenuButton2.png")) std::cout << "Error loading b3" << std::endl;
	sf::Texture button4H;
	if (!button4H.loadFromFile("./images/MainScreen/MenuButton3Hover.png")) std::cout << "Error loading b3h" << std::endl;
	sf::Texture button4NH;
	if (!button4H.loadFromFile("./images/MainScreen/MenuButton3.png")) std::cout << "Error loading b3" << std::endl;

	sf::RectangleShape background(sf::Vector2f(800.f, 500.f));	// â�� ũ��� 800X500
	background.setTexture(&backgroundTexture);

	// ��ư�� ũ��� 300X85
	sf::RectangleShape button1(sf::Vector2f(butSize_x, butSize_y));
	button1.setTexture(&button1NH);
	button1.setPosition(butPos_x, butPos_y);
	sf::RectangleShape button2(sf::Vector2f(butSize_x, butSize_y));
	button2.setTexture(&button2NH);
	button2.setPosition(butPos_x, butPos_y * 2);
	sf::RectangleShape button3(sf::Vector2f(butSize_x, butSize_y));
	button3.setTexture(&button3NH);
	button3.setPosition(butPos_x, butPos_y * 3);
	sf::RectangleShape button4(sf::Vector2f(butSize_x, butSize_y));		
	button4.setTexture(&button4NH);										// �߰� ��ư �̹��� �־��
	button4.setPosition(butPos_x, butPos_y * 4);


	// ��� ���ǰ� ��ư ���� �� ȿ���� �ҷ���
	sf::Music music;
	if (!music.openFromFile("./music/MenuMusic.ogg")) std::cout << "Error loading music" << std::endl;
	if(soundOn){
		music.play();
	}

	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("./music/ButtonFX.ogg")) std::cout << "Error loading fx" << std::endl;
	sf::Sound buttonSound;
	buttonSound.setBuffer(buffer);

	bool fxtime = false;
	sf::Vector2u getWindowSize;		// ���α׷��� ������ ���� �޾ƿ�
	int occupyButX, occupyButY;	// ��ư�� ������, ������ ���� ���
	int culPos_x, culPos_y;		// ���� ��ư���� ��ġ ��ǥ(â ���� ���)

	while (_windows->isOpen()) {		// ������ ���� ��

		sf::Event event;
		sf::Vector2i mousepos = sf::Mouse::getPosition(*_windows);	// ���� ���콺 ��ǥ

		// â�� ũ�⿡ ������� ��ư �̹����� �ִ� ������ ���콺 �̺�Ʈ�� ����� �� �ֵ��� ���
		getWindowSize = _windows->getSize();
		culPos_x = (butPos_x*getWindowSize.x) / 800;	// ���� ��ư���� ��ġ ��ǥX(â ���� ���)
		culPos_y = (butPos_y*getWindowSize.y) / 500;	// ���� ��ư���� ��ġ ��ǥY(â ���� ���)
		occupyButX = (getWindowSize.x - culPos_x * 2);			// ��ư�� �������� ȭ���� �����ϴ� ����
		occupyButY = (butSize_y * getWindowSize.y) / 500;		// ��ư�� �������� ȭ���� �����ϴ� ����

		// ��ư�� Ȱ��ȭ(���콺�� ��ư ���� �ö���� ���)�� ���õ� �̹��� �� ���� ���
		if ((mousepos.x > culPos_x) && (mousepos.x < culPos_x + occupyButX)) {	// ��ư�� ������ ���� ����
			if (mousepos.y >= culPos_y && mousepos.y <= (culPos_y + occupyButY)) {	// ù��° ��ư�� ������ ���� ����
				button1.setTexture(&button1H);		// ���� ���� ��ư �̹��� Ȱ��ȭ
				if (!fxtime) {
					if(soundOn) buttonSound.play();
					fxtime = true;
				}
			}
			else if ((mousepos.y >= culPos_y * 2) && (mousepos.y <= (culPos_y * 2 + occupyButY))) { // �ι�° ��ư�� ������ ���� ����
				button2.setTexture(&button2H);		// ĳ���� ���� ��ư �̹��� Ȱ��ȭ
				if (!fxtime) {
					if(soundOn) buttonSound.play();
					fxtime = true;
				}
			}
			else if ((mousepos.y >= culPos_y * 3) && (mousepos.y <= (culPos_y * 3 + occupyButY))) { // ����° ��ư�� ������ ���� ����
				button3.setTexture(&button3H);		// // �߰� ��ư �̹��� Ȱ��ȭ
				if (!fxtime) {
					if(soundOn) buttonSound.play();
					fxtime = true;
				}
			}
			else if ((mousepos.y >= culPos_y * 4) && (mousepos.y <= (culPos_y * 4 + occupyButY))) { // �׹�° ��ư�� ������ ���� ����
				button4.setTexture(&button4H);		// EXIT ��ư �̹��� Ȱ��ȭ
				if (!fxtime) {
					if(soundOn) buttonSound.play();
					fxtime = true;
				}
			}
			else {								// �ƹ��� ������ ���� ���(���콺�� ��ư ���� �� �ö�� ���� ���)
				button1.setTexture(&button1NH);
				button2.setTexture(&button2NH);
				button3.setTexture(&button3NH);
				button4.setTexture(&button4NH);
				fxtime = false;
			}
		}
		else {									// �ƹ��� ������ ���� ���(���콺�� ��ư ���� �� �ö�� ���� ���)
			button1.setTexture(&button1NH);
			button2.setTexture(&button2NH);
			button3.setTexture(&button3NH);
			button4.setTexture(&button4NH);
			fxtime = false;
		}

		while (_windows->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)	// �ܼ�â�� ���� ������ ���
				_windows->close();
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if ( (mousepos.x > culPos_x) && (mousepos.x < (culPos_x + occupyButX)) ) {
						if ( (mousepos.y >= culPos_y) && (mousepos.y <= (culPos_y + occupyButY)) ) {
							music.stop();
							select.selectRun(soundOn);		// ĳ���� ���� �� ����
							if(soundOn){
								music.play();
							}
						}
						else if ( (mousepos.y >= culPos_y * 2) && (mousepos.y <= (culPos_y * 2 + occupyButY)) ) {
							about.run();							// ĳ���� ���� ����
						}
						else if ((mousepos.y >= culPos_y * 3) && (mousepos.y <= (culPos_y * 3 + occupyButY)) ) {
							soundOn = preferences.run(soundOn, music);									// �ɼ�
							if(soundOn == false) music.stop();
						}
						else if ( (mousepos.y >= culPos_y * 4) && (mousepos.y <= (culPos_y * 4+ occupyButY)) ) {
							_windows->close();					// �ܼ�â ����
						}
					}
				}
			}
		}

		// �ҷ��� �̹����� �׸��� ���� �޼ҵ��
		_windows->clear();
		_windows->draw(background);
		_windows->draw(button1);
		_windows->draw(button2);
		_windows->draw(button3);
		_windows->draw(button4);
		_windows->display();

	}
}