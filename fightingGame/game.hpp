#include "Champion.hpp"
#include <iostream>
#include <sstream>
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

	sf::Texture characterTexture;		// 캐릭터 텍스쳐
	sf::Texture characterTexture2;

	sf::Texture backgroundTexture;		// 배경 텍스쳐
	sf::RectangleShape background;

	sf::Texture roundPanelTexture[4];   // round 판넬 텍스쳐
	sf::RectangleShape roundPanel[4];

	sf::Texture winPanelTexture[5];   // 승리 판넬 텍스쳐
	sf::RectangleShape winPanel[5];
	sf::Texture winPanelTextTexture[5];
	sf::RectangleShape winPanelText[5];

	sf::Sprite player1_spr;
	sf::Sprite player2_spr;

	sf::RectangleShape hpBarBackground;
	sf::Texture hpBarBackgroundTexture;
	sf::RectangleShape HpBar[2];

	sf::CircleShape p1_WS[2], p2_WS[2]; 
	sf::CircleShape bp1_WS[2], bp2_WS[2]; 

	sf::Texture p1_sIcon[3];
	sf::Texture p2_sIcon[3];
	sf::RectangleShape p1_SImage[3];
	sf::RectangleShape p2_SImage[3];
	sf::RectangleShape p1_SImageBackground[3];
	sf::RectangleShape p2_SImageBackground[3];

	std::string p1_skillCountstr[3];
	std::string p2_skillCountstr[3];

	sf::Font font;
	sf::Text p1_skillCount[3];
	sf::Text p2_skillCount[3];
	sf::RectangleShape p1_skillCountBackground[3];
	sf::RectangleShape p2_skillCountBackground[3];

	void loadCharacterImage(int pNumber, sf::Texture& texture);
	void setSkillIcon(int pNumber, sf::Texture *sIcon, sf::RectangleShape *p_sIcon, sf::RectangleShape *p_sIconB, 
		sf::Text *p_skillCount, sf::RectangleShape *p_skillCountBackground, std::string* p_skillCountstr, Champion & c, bool player1);
	void updateSkillCount(Champion &player, std::string* p_skillCountstr, sf::Text *p_skillCount);
	void drawWindow();
	void drawRound();
	void resetGame(Champion &player1, Champion &player2, int &time, float &frameCount, float &frameCount2);
	void setObject();
	void setRoundPanel();
	void setWinPanel();
	void setGameOver(class Champion& winChamp);
	void moveCharacter(class Champion &c, sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key jump, sf::Keyboard::Key barrier);
    void attackCharacter(class Champion &c,  sf::Keyboard::Key normal,  sf::Keyboard::Key skill1,  sf::Keyboard::Key skill2,  sf::Keyboard::Key skill3, float &frameCount, std::string* p_skillCountstr, sf::Text *p_skillCount);
	void operationSkill(class Champion &c, int skillNumber, float &frameCount, std::string* p_skillCountstr, sf::Text *p_skillCount);
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

