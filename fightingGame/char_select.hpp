#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>

class Char_Select
{
public:
	Char_Select(sf::RenderWindow*window);

	sf::Music sChar;

	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Texture p1Pointer;
	sf::Texture p2Pointer;
	sf::RectangleShape p1;
	sf::RectangleShape p2;

	sf::Texture character[5];
	sf::RectangleShape player1_Rect;
	sf::RectangleShape player2_Rect;

	sf::RectangleShape player1_Select_Rect;
	sf::RectangleShape player2_Select_Rect;

	int selectRun();
	int newCharactor(int flag, int &selectedChar);

	void setPlayerRect();
	void setPlayerSelect(sf::RectangleShape &p_rect, int number);
	void setObject();
	void updatePlayerFrameCount();

private:
	int pos1P_x, pos1P_y, pos2P_x, pos2P_y;
	int selectedP1, selectedP2;
	int selectedChar[2];

	bool isPlayer1Selected;
	bool isPlayer2Selected;
	float player1FrameCount;
	float player2FrameCount;

	sf::RenderWindow *_windows;



};