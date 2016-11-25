#include "char_select.hpp"
#include "game.hpp"

const int MAX_P1_FC = 359;
const int MAX_P2_FC = 361;

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

	setPlayerRect();
}
// 캐릭터 선택을 위한 flag형식으로 만든 함수
// y좌표을 리턴받아서 화살표들이 움직임
int Char_Select::newCharactor(int flag, int &selectChar)   
{
	selectChar = 0;
	int newChar = 1;
	int posChar1 = 85, posChar2 = 175, posChar3 = 260, posChar4 = 350, posRand = 435;
	int char1 = 1, char2 = 2, char3 = 3, char4 = 4, char5 = 5;
	switch (flag)
	{
	case 1: newChar = posChar1; selectChar = char1; break;
	case 2: newChar = posChar2; selectChar = char2; break;
	case 3: newChar = posChar3; selectChar = char3; break;
	case 4: newChar = posChar4; selectChar = char4; break;
	case 5: newChar = posRand; selectChar = char5/*(rand()%5)+1*/; break;
	default:
		break;
	}
	return newChar;
}
int Char_Select::selectRun()
{
	int tmpArr[2] = {1};
	setObject();
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
		if(!isPlayer1Selected){
			if (GetAsyncKeyState('S') & 0x0001)      // if "S" key is pressed   : Go Down
			{
				p1Pos += 1;
				if (p1Pos > 5) p1Pos = 1;
				p1.setPosition(sf::Vector2f(p1.getPosition().x, newCharactor(p1Pos, selectedChar[0])));
			}
			if (GetAsyncKeyState('W') & 0x0001)      // if "W" key is pressed   : Go UP
			{
				p1Pos -= 1;
				if (p1Pos < 1) p1Pos = 5;
				p1.setPosition(sf::Vector2f(p1.getPosition().x, newCharactor(p1Pos, selectedChar[0])));
			}
		}
		if (GetAsyncKeyState('Q') & 0x0001) {   // Q는 캐릭터 선택
			isPlayer1Selected = !isPlayer1Selected;
			selectedP1 = selectedChar[0];
			setPlayerSelect(player1_Rect, selectedP1);
			tmpArr[0] = selectedP1;
		}

		//Player 2 movement
		if(!isPlayer2Selected){
			if (GetAsyncKeyState(VK_DOWN) & 0x0001)      // if "DOWN" key is pressed   : Go Down
			{
				p2Pos += 1;
				if (p2Pos > 5) p2Pos = 1;
				p2.setPosition(sf::Vector2f(p2.getPosition().x, newCharactor(p2Pos, selectedChar[1])));
			}
			if (GetAsyncKeyState(VK_UP) & 0x0001)      // if "UP" key is pressed   : Go UP
			{
				p2Pos -= 1;
				if (p2Pos < 1) p2Pos = 5;
				p2.setPosition(sf::Vector2f(p2.getPosition().x, newCharactor(p2Pos, selectedChar[1])));
			}
		}
		if (GetAsyncKeyState('8') & 0x0001) {   //Num8을 누르면 캐릭터 선택
			isPlayer2Selected = !isPlayer2Selected;
			selectedP2 = selectedChar[1];
			setPlayerSelect(player2_Rect, selectedP2);
			tmpArr[1] = selectedP2;
		}
		if (isPlayer1Selected && isPlayer2Selected && player1FrameCount > MAX_P1_FC-1 && player2FrameCount > MAX_P2_FC-1)
		{
			Game game(_windows, tmpArr[0],  tmpArr[1]);
			int gameRun = game.Run();
			selectedP1 = 0;
			selectedP2 = 0;
			return 0;
			//tmpArr[2] = {0};

		}
		_windows->draw(background);
		updatePlayerFrameCount();
		_windows->draw(player1_Rect);
		_windows->draw(player2_Rect);
		_windows->draw(p1);
		_windows->draw(p2);
		_windows->display();
	}
	return 0;
}

void Char_Select::setPlayerSelect(sf::RectangleShape &p_rect, int number){
	p_rect.setTexture(&character[number-1]);
}

void Char_Select::setPlayerRect(){

	character[0].loadFromFile("./images/character_win/gpl_win_bigimage.png");
	character[1].loadFromFile("./images/character_win/lgpl_win_bigimage.png");
	character[2].loadFromFile("./images/character_win/apache_win_bigimage.png");
	character[3].loadFromFile("./images/character_win/bsd_win_bigimage.png");
	character[4].loadFromFile("./images/character_win/jang_win_bigimage.png");

	player1_Rect = sf::RectangleShape(sf::Vector2f(MAX_P1_FC, 420));
	player1_Rect.setTexture(&character[0]);
	player1_Rect.setTextureRect(sf::IntRect(0, 0, 800, 500));
	player1_Rect.setScale(-1.f, 1);
	player1_Rect.setPosition(player1FrameCount,80);

	player2_Rect = sf::RectangleShape(sf::Vector2f(MAX_P2_FC, 420));
	player2_Rect.setTexture(&character[0]);
	player2_Rect.setTextureRect(sf::IntRect(0, 0, 800, 500));
	player2_Rect.setPosition(800-player2FrameCount,80);
}

void Char_Select::updatePlayerFrameCount(){

	if(isPlayer1Selected){
		player1FrameCount += 1;
		if(player1FrameCount > MAX_P1_FC) 
			player1FrameCount = MAX_P1_FC;
	}
	else{
		player1FrameCount -= 1;
		if(player1FrameCount < 0) 
			player1FrameCount = 0;
	}
	if(isPlayer2Selected){
		player2FrameCount += 1;
		if(player2FrameCount > MAX_P2_FC) 
			player2FrameCount = MAX_P2_FC;
	}
	else{
		player2FrameCount -= 1;
		if(player2FrameCount < 0) 
			player2FrameCount = 0;
	}
	player1_Rect.setPosition(player1FrameCount,80);
	player2_Rect.setPosition(800-player2FrameCount,80);
}

void Char_Select::setObject(){
	selectedChar[0] = 1;
	selectedChar[1] = 1;
	selectedP1 = 1;
	selectedP2 = 1;
	isPlayer1Selected = false;
	isPlayer2Selected = false;
	player1FrameCount = 0;
	player2FrameCount = 0;
}

