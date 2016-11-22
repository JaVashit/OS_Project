#include "Champion.hpp"

#ifndef GAME_H
#define GAME_H

class Game
{
public:
    Game(sf::RenderWindow* window);
    int Run();
    
    int setScore(bool,int);
    int getScore(bool);
	void resetGame(Champion &player1, Champion &player2);

	void setObject();

	sf::Texture characterTexture;		// 캐릭터 텍스쳐
	sf::Texture characterTexture2;

	sf::Texture backgroundTexture;		// 배경 텍스쳐
	sf::RectangleShape background;
	sf::Sprite player1_spr;
	sf::Sprite player2_spr;

	sf::RectangleShape HpBar1, HpBar2;
	sf::RectangleShape MpBar1, MpBar2;

	sf::CircleShape p1_WS1, p1_WS2, p2_WS1, p2_WS2; 
	sf::CircleShape bp1_WS1, bp1_WS2, bp2_WS1, bp2_WS2; 

	sf::Music music;
    
private:
    int score1;
    int score2;
	int w_width;
	int w_height;
   
    sf::RenderWindow * _myWindow;
};
#endif

