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
    Game(sf::RenderWindow* window, int p1Number, int p2Number);  // window, player's select model number
    void Run(bool sound);											// game running

	sf::Music music;

	sf::Texture characterTexture;						// character texture
	sf::Texture characterTexture2;

	sf::Texture backgroundTexture;						// background texture & rect
	sf::RectangleShape background;

	sf::Texture roundPanelTexture[4];					// round panel texture & rect
	sf::RectangleShape roundPanel[4];

	sf::Texture winPanelTexture[5];						// win panel, text texture & rect
	sf::RectangleShape winPanel[5];
	sf::Texture winPanelTextTexture[5];			
	sf::RectangleShape winPanelText[5];

	sf::Sprite player1_spr;								// player1 sprite 
	sf::Sprite player2_spr;								// player2 sprite

	sf::RectangleShape hpBarBackground;					// hp bar background texture & rect
	sf::Texture hpBarBackgroundTexture;					
	sf::RectangleShape HpBar[2];						// player's hp bar

	sf::CircleShape p1_WS[2], p2_WS[2];					// checking player win round
	sf::CircleShape bp1_WS[2], bp2_WS[2]; 

	sf::Texture p1_sIcon[3];							// player skill icon textur & rect
	sf::Texture p2_sIcon[3];
	sf::RectangleShape p1_SImage[3];
	sf::RectangleShape p2_SImage[3];
	sf::RectangleShape p1_SImageBackground[3];
	sf::RectangleShape p2_SImageBackground[3];
	std::string p1_skillCountstr[3];		
	std::string p2_skillCountstr[3];

	sf::Font font;										// text font
	sf::Text p1_skillCount[3];							// player skill count text & rect
	sf::Text p2_skillCount[3];
	sf::RectangleShape p1_skillCountBackground[3];
	sf::RectangleShape p2_skillCountBackground[3];

	sf::Texture hitTexture;								// hit texture & rect
	sf::RectangleShape hit;

	void loadCharacterImage(int pNumber, sf::Texture& texture);															// load character image
	void setSkillIcon(int pNumber, sf::Texture *sIcon, sf::RectangleShape *p_sIcon, sf::RectangleShape *p_sIconB,		// setting player skill icons
		sf::Text *p_skillCount, sf::RectangleShape *p_skillCountBackground, std::string* p_skillCountstr, class Champion & c, bool player1);
	void updateSkillCount(class Champion &player, std::string* p_skillCountstr, sf::Text *p_skillCount);				// update player skill count
	void drawWindow();																									// draw object in window
	void drawRound();																									// draw round panel
	void resetGame(class Champion &player1, class Champion &player2, int &time, float &frameCount, float &frameCount2); // game setting in reset
	void setObject();																									// setting hpbar etc...
	void setRoundPanel();																								// setting round & fight panel
	void setWinPanel();																									// setting win panel
	void setGameOver(class Champion& winChamp);																			// setting object in game over
	void moveCharacter(class Champion &c, sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key jump, sf::Keyboard::Key barrier);
																														// move character when pressed key
    void attackCharacter(class Champion &c,  sf::Keyboard::Key normal,  sf::Keyboard::Key skill1,  sf::Keyboard::Key skill2,  sf::Keyboard::Key skill3, float &frameCount, std::string* p_skillCountstr, sf::Text *p_skillCount);
																														// attack character when pressed key
	void operationSkill(class Champion &c, int skillNumber, float &frameCount, std::string* p_skillCountstr, sf::Text *p_skillCount);
																														// operation attack skill
	void setChampionsFacing(class Champion &p1, class Champion &p2);													// setting champion facing
	void setChampionSprite(class Champion &c, sf::Sprite &s);															// update champion sprite
	void updateHpBar(class Champion p1, class Champion p2);																// update hpbar
	void checkDeath(class Champion &p1, class Champion &p2, int &time, float &frameCount, float &frameCount2);			// check player death
	void detectCollision_Champions(class Champion &p1, class Champion &p2, float &frameCount, float &frameCount2, int time); // detect collision champion and attackobject
	void drawAttackObject(class Champion &p1, class Champion &p2);														// draw attack object in window
	void drawHit(class Champion &p1, class Champion &p2);																// draw hit image in window 

private:
	int w_width;			// window width
	int w_height;			// window height
	int roundCount;			// check roundcount

	int player1Number;		// player1 model number
	int player2Number;		// player2 model number

	float roundPanelPosX;	// round panel position x
	float roundPanelPosY;	// round panel position y
	float panelSpeed;		// round panel speed
	float panel_ax;			// roudn panel acceleration x

	float winPanelPosX;		// win panel position x
	float winPanelPosY;		// win panel position y
	float winPanelSpeed;	// win panel speed
	float winPanel_ax;		// win panel acceleration x
	int gameOverCount;		// when game over, check frame count

	bool fight_start;		// fight panel operation
	bool round_start;		// round panel operation
	bool gameOver;			// is game over
	bool isEnd;				// is end
	int winChampionNumber;	// wining champion model number

	bool soundOn;			// sound

    sf::RenderWindow * _myWindow;	// console window

	sf::Music finSound;
};
#endif

