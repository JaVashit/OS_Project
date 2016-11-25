#include "char_select.hpp"
#include "game.hpp"

Char_Select::Char_Select(sf::RenderWindow *window) :_windows(window)
{
	pos1P_x = 270;   pos1P_y = 85;
	pos2P_x = 455;   pos2P_y = 85;
	background = sf::RectangleShape(sf::Vector2f(800.f, 500.f));
	if (!backgroundTexture.loadFromFile("./images/other/character_select.png")) std::cout << "Error loading charactor_select image" << std::endl;
	if (!p1Pointer.loadFromFile("./images/other/p1.png")) std::cout << "Error loading Player1_Pointer image" << std::endl;
	if (!p2Pointer.loadFromFile("./images/other/p2.png")) std::cout << "Error loading Player2_Pointer image" << std::endl;
	p1 = sf::RectangleShape(sf::Vector2f(80.f, 50.f));
	p2 = sf::RectangleShape(sf::Vector2f(80.f, 50.f));
}
// 캐릭터 선택을 위한 flag형식으로 만든 함수
// y좌표을 리턴받아서 화살표들이 움직임
int Char_Select::newCharactor(int flag)   
{
	selectedChar = 0;
	int newChar = 1;
	int posChar1 = 85, posChar2 = 175, posChar3 = 260, posChar4 = 350, posRand = 435;
	int char1 = 1, char2 = 2, char3 = 3, char4 = 4, char5 = 5;
	switch (flag)
	{
	case 1: newChar = posChar1; selectedChar = char1; break;
	case 2: newChar = posChar2; selectedChar = char2; break;
	case 3: newChar = posChar3; selectedChar = char3; break;
	case 4: newChar = posChar4; selectedChar = char4; break;
	case 5: newChar = posRand; selectedChar = (rand()%5)+1; break;
	default:
		break;
	}
	return newChar;
}
int Char_Select::selectRun()
{
	int tmpArr[2] = { 0 };
	background.setTexture(&backgroundTexture);

	p1.setTexture(&p1Pointer);
	p1.setPosition(pos1P_x, pos1P_y);

	p2.setTexture(&p2Pointer);
	p2.setPosition(pos2P_x, pos2P_y);
	int p1Pos = 1, p2Pos = 1;
	while (_windows->isOpen())
	{
		sf::Event event;
		while (_windows->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				_windows->close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			return -1;
		}
		//Player 1 movement

		if (GetAsyncKeyState('S') & 0x0001)      // if "S" key is pressed   : Go Down
		{
			p1Pos += 1;
			if (p1Pos > 5) p1Pos = 1;
			p1.setPosition(sf::Vector2f(p1.getPosition().x, newCharactor(p1Pos)));
		}
		if (GetAsyncKeyState('W') & 0x0001)      // if "W" key is pressed   : Go UP
		{
			p1Pos -= 1;
			if (p1Pos < 1) p1Pos = 5;
			p1.setPosition(sf::Vector2f(p1.getPosition().x, newCharactor(p1Pos)));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {   // Q는 캐릭터 선택
			selectedP1 = selectedChar;
			tmpArr[0] = selectedP1;
		}

		//Player 2 movement

		if (GetAsyncKeyState(VK_DOWN) & 0x0001)      // if "DOWN" key is pressed   : Go Down
		{
			p2Pos += 1;
			if (p2Pos > 5) p2Pos = 1;
			p2.setPosition(sf::Vector2f(p2.getPosition().x, newCharactor(p2Pos)));
		}
		if (GetAsyncKeyState(VK_UP) & 0x0001)      // if "UP" key is pressed   : Go UP
		{
			p2Pos -= 1;
			if (p2Pos < 1) p2Pos = 5;
			p2.setPosition(sf::Vector2f(p2.getPosition().x, newCharactor(p2Pos)));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) {   //Num8을 누르면 캐릭터 선택
			selectedP2 = selectedChar;
			tmpArr[1] = selectedP2;
		}
		if ((tmpArr[0]) && (tmpArr[1]))
		{
			printf("1: %d   2:%d\n", tmpArr[0], tmpArr[1]);
			Game game(_windows, tmpArr[0],  tmpArr[1]);
			int gameRun = game.Run();
			//tmpArr[2] = {0};

		}
		_windows->draw(background);
		_windows->draw(p1);
		_windows->draw(p2);
		_windows->display();
	}
	return 0;
}