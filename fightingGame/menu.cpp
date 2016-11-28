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
	
	// 첫번째 버튼의 시작점 좌표
	butPos_x = 250;
	butPos_y = 100;
	butSize_x = 300;
	butSize_y = 85;

	// menu를 창을 띄우기 위한 이미지를 불러옴(배경, 버튼, 활성화 버튼)
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

	sf::RectangleShape background(sf::Vector2f(800.f, 500.f));	// 창의 크기는 800X500
	background.setTexture(&backgroundTexture);

	// 버튼의 크기는 300X85
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
	button4.setTexture(&button4NH);										// 추가 버튼 이미지 넣어용
	button4.setPosition(butPos_x, butPos_y * 4);


	// 배경 음악과 버튼 선택 시 효과음 불러옴
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
	sf::Vector2u getWindowSize;		// 프로그램의 윈도우 값을 받아옴
	int occupyButX, occupyButY;	// 버튼의 가로축, 세로축 비율 계산
	int culPos_x, culPos_y;		// 현재 버튼들의 위치 좌표(창 비율 대비)

	while (_windows->isOpen()) {		// 게임이 실행 중

		sf::Event event;
		sf::Vector2i mousepos = sf::Mouse::getPosition(*_windows);	// 현재 마우스 좌표

		// 창의 크기에 상관없이 버튼 이미지가 있는 곳에서 마우스 이벤트가 실행될 수 있도록 계산
		getWindowSize = _windows->getSize();
		culPos_x = (butPos_x*getWindowSize.x) / 800;	// 현재 버튼들의 위치 좌표X(창 비율 대비)
		culPos_y = (butPos_y*getWindowSize.y) / 500;	// 현재 버튼들의 위치 좌표Y(창 비율 대비)
		occupyButX = (getWindowSize.x - culPos_x * 2);			// 버튼의 가로축이 화면을 차지하는 범위
		occupyButY = (butSize_y * getWindowSize.y) / 500;		// 버튼의 세로축이 화면을 차지하는 범위

		// 버튼이 활성화(마우스가 버튼 위에 올라왔을 경우)에 관련된 이미지 및 사운드 출력
		if ((mousepos.x > culPos_x) && (mousepos.x < culPos_x + occupyButX)) {	// 버튼의 가로축 내의 범위
			if (mousepos.y >= culPos_y && mousepos.y <= (culPos_y + occupyButY)) {	// 첫번째 버튼의 세로축 내의 범위
				button1.setTexture(&button1H);		// 게임 시작 버튼 이미지 활성화
				if (!fxtime) {
					if(soundOn) buttonSound.play();
					fxtime = true;
				}
			}
			else if ((mousepos.y >= culPos_y * 2) && (mousepos.y <= (culPos_y * 2 + occupyButY))) { // 두번째 버튼의 세로축 내의 범위
				button2.setTexture(&button2H);		// 캐릭터 정보 버튼 이미지 활성화
				if (!fxtime) {
					if(soundOn) buttonSound.play();
					fxtime = true;
				}
			}
			else if ((mousepos.y >= culPos_y * 3) && (mousepos.y <= (culPos_y * 3 + occupyButY))) { // 세번째 버튼의 세로축 내의 범위
				button3.setTexture(&button3H);		// // 추가 버튼 이미지 활성화
				if (!fxtime) {
					if(soundOn) buttonSound.play();
					fxtime = true;
				}
			}
			else if ((mousepos.y >= culPos_y * 4) && (mousepos.y <= (culPos_y * 4 + occupyButY))) { // 네번째 버튼의 세로축 내의 범위
				button4.setTexture(&button4H);		// EXIT 버튼 이미지 활성화
				if (!fxtime) {
					if(soundOn) buttonSound.play();
					fxtime = true;
				}
			}
			else {								// 아무런 선택이 없을 경우(마우스가 버튼 위에 안 올라와 있을 경우)
				button1.setTexture(&button1NH);
				button2.setTexture(&button2NH);
				button3.setTexture(&button3NH);
				button4.setTexture(&button4NH);
				fxtime = false;
			}
		}
		else {									// 아무런 선택이 없을 경우(마우스가 버튼 위에 안 올라와 있을 경우)
			button1.setTexture(&button1NH);
			button2.setTexture(&button2NH);
			button3.setTexture(&button3NH);
			button4.setTexture(&button4NH);
			fxtime = false;
		}

		while (_windows->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)	// 콘솔창을 종료 시켰을 경우
				_windows->close();
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if ( (mousepos.x > culPos_x) && (mousepos.x < (culPos_x + occupyButX)) ) {
						if ( (mousepos.y >= culPos_y) && (mousepos.y <= (culPos_y + occupyButY)) ) {
							music.stop();
							select.selectRun(soundOn);		// 캐릭터 선택 뷰 실행
							if(soundOn){
								music.play();
							}
						}
						else if ( (mousepos.y >= culPos_y * 2) && (mousepos.y <= (culPos_y * 2 + occupyButY)) ) {
							about.run();							// 캐릭터 정보 실행
						}
						else if ((mousepos.y >= culPos_y * 3) && (mousepos.y <= (culPos_y * 3 + occupyButY)) ) {
							soundOn = preferences.run(soundOn, music);									// 옵션
							if(soundOn == false) music.stop();
						}
						else if ( (mousepos.y >= culPos_y * 4) && (mousepos.y <= (culPos_y * 4+ occupyButY)) ) {
							_windows->close();					// 콘솔창 종료
						}
					}
				}
			}
		}

		// 불러온 이미지를 그리기 위한 메소드들
		_windows->clear();
		_windows->draw(background);
		_windows->draw(button1);
		_windows->draw(button2);
		_windows->draw(button3);
		_windows->draw(button4);
		_windows->display();

	}
}