#include "Champion.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#ifndef GAME_H
#define GAME_H

class Game
{
public:
    Game(sf::RenderWindow* window, int p1Number, int p2Number);
    int Run();

	sf::Music music;

	sf::Texture characterTexture;		// ĳ���� �ؽ���
	sf::Texture characterTexture2;

	sf::Texture backgroundTexture;		// ��� �ؽ���
	sf::RectangleShape background;

	sf::Texture roundPanelTexture[4];   // round �ǳ� �ؽ���
	sf::RectangleShape roundPanel[4];

	sf::Texture winPanelTexture[5];   // �¸� �ǳ� �ؽ���
	sf::RectangleShape winPanel[5];
	sf::Texture winPanelTextTexture[5];
	sf::RectangleShape winPanelText[5];

	sf::Sprite player1_spr;
	sf::Sprite player2_spr;

	sf::RectangleShape HpBar[2];

	sf::CircleShape p1_WS[2], p2_WS[2]; 
	sf::CircleShape bp1_WS[2], bp2_WS[2]; 

	sf::RectangleShape p1_SImage[4];
	sf::RectangleShape p2_SImage[4];


	void loadCharacterImage(int pNumber, sf::Texture& texture);
	void drawWindow();
	void drawRound();
	void resetGame(Champion &player1, Champion &player2, int &time, float &frameCount, float &frameCount2);
	void setObject();
	void setRoundPanel();
	void setWinPanel();
	void setGameOver(class Champion& winChamp);
	void moveCharacter(class Champion &c, sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key jump, sf::Keyboard::Key barrier);
    void attackCharacter(class Champion &c,  sf::Keyboard::Key normal,  sf::Keyboard::Key skill1,  sf::Keyboard::Key skill2,  sf::Keyboard::Key skill3, float &frameCount);
	void operationSkill(class Champion &c, int skillNumber, float &frameCount);
	void setChampionsFacing(class Champion &p1, class Champion &p2); 
	void setChampionSprite(class Champion &c, sf::Sprite &s);
	void updateHpBar(class Champion p1, class Champion p2);
	void checkDeath(class Champion &p1, class Champion &p2, int &time, float &frameCount, float &frameCount2);
	void detectCollision_Champions(class Champion &p1, class Champion &p2, float &frameCount, float &frameCount2);
	void drawAttackObject(class Champion &p1, class Champion &p2);

private:
	int w_width;
	int w_height;
	int roundCount;

	int player1Number;
	int player2Number;

	float roundPanelPosX;
	float roundPanelPosY;
	float panelSpeed;
	float panel_ax;

	float winPanelPosX;
	float winPanelPosY;
	float winPanelSpeed;
	float winPanel_ax;
	int gameOverCount;

	bool fight_start;
	bool round_start;
	bool gameOver;
	bool isEnd;
	int winChampionNumber;

    sf::RenderWindow * _myWindow;
};
#endif

