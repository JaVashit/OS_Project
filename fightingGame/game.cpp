#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "game.hpp"
#include "Champion.hpp"

const int PIC_SIZE_X = 170;
const int PIC_SIZE_Y = 100;
const float FRAMESPEED = 0.02;

Game::Game(sf::RenderWindow *window): _myWindow(window){
	w_width = _myWindow->getSize().x;
	w_height = _myWindow->getSize().y;
	background =  sf::RectangleShape(sf::Vector2f(800.f,500.f));
	
	//Characters
    if (!characterTexture.loadFromFile("./images/character/gpl_sprite.png")) std::cout << "Error loading vx_characters" << std::endl;
    if (!characterTexture2.loadFromFile("./images/character/bsd_sprite.png")) std::cout << "Error loading vx_characters" << std::endl;

	//Background
    if (!backgroundTexture.loadFromFile("./images/stage/stage01.png")) std::cout << "Error loading citybg" << std::endl;

	//music
	if (!music.openFromFile("./music/FightMusic.ogg")) std::cout << "Error loading normal music" << std:: endl;
}

int Game::Run()
{
	roundCount = 1;
    setObject();
	//round
	setRoundPanel();
	setWinPanel();
	
	Champion c1 = Champion(1, 0, w_width, w_height);
	Champion c2 = Champion(0, 1, w_width, w_height);

	background.setTexture(&backgroundTexture);
    //Create and load player 1 arguments
   
    player1_spr.setTexture(characterTexture);                       //Load texture to sprite
    c1.loadCharacter(player1_spr);                    //Select character texture, scale, origin
 
    //Create and load player 2 arguments
    player2_spr.setTexture(characterTexture2);
    c2.loadCharacter(player2_spr);

    music.play();
    
    //Other variables
    int time = 0;
	float frameCount = 0;
	float frameCount2 = 0;
    while (_myWindow->isOpen())
	{
		time++;
		sf::Event event;
		while (_myWindow->pollEvent(event)){						// close console
			if (event.type == sf::Event::Closed)
				_myWindow->close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){		// pressed escape
			return -1;
		}

		if(!round_start && !fight_start && !gameOver){				// in Game
			moveCharacter(c1, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::S);								//Player 1 movement
			attackCharacter(c1, sf::Keyboard::Q, sf::Keyboard::Num1, sf::Keyboard::Num2, sf::Keyboard::Num3, frameCount);		//Player 1 actions
			moveCharacter(c2, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down);					//Player 2 movement
			attackCharacter(c2, sf::Keyboard::Num8, sf::Keyboard::Num9, sf::Keyboard::Num0, sf::Keyboard::Dash, frameCount2);	//Player 2 actions
			
			setChampionsFacing(c1, c2);									// update champions facing
			c1.crowdControlHit(frameCount);								// player1 set sprite konck back & stun
			c2.crowdControlHit(frameCount2);							// player2 set sprite konck back & stun
			setChampionSprite(c1, player1_spr);							// Sprite & Character position update
			setChampionSprite(c2, player2_spr);
			updateHpBar(c1, c2);										// HPbars update
			checkDeath(c1, c2, time, frameCount, frameCount2);			// Death check and restart or gameover
			detectCollision_Champions(c1, c2, frameCount, frameCount2);	// update AttackObjectList & detectCollision
		}
		drawWindow();					// drawObject
		drawAttackObject(c1, c2);		// drawAttackObject
		_myWindow->display();			// display

		if(time==1){					// draw roundPanel & fightPanel
			round_start = true;
		}
		if(isEnd){						// is Game Over
			music.stop();
			return 0;
		}
    }
	
	return 0;
}

void Game::setChampionSprite(Champion &c, sf::Sprite &s){
	c.caculatePosXY();
	s.setPosition(c.getPosition());
	if(!c.isAttacking() && !c.isBarrier() && !c.isKnockBack && !c.isStun){
		c.calculateSpritePos();
	}
	if(c.getFacing()){
		s.setScale(-2.f, 2.f);
	}
	else{
		s.setScale(2.f, 2.f);
	}
	s.setTextureRect(sf::IntRect((int)c.getSpr().x, (int)c.getSpr().y, PIC_SIZE_X, PIC_SIZE_Y));
}

void Game::updateHpBar(Champion p1, Champion p2){
	HpBar[0].setScale(p1.getHp()/100*1.f,1.f);
	HpBar[1].setScale(-p2.getHp()/100*1.f,1.f);
}

void Game::resetGame(Champion &player1, Champion &player2, int &time, float &frameCount, float &frameCount2){
	player1.setHp(100);
	player1.setFacing(1);
	player1.setPosition(60, 340);
	player1.setSpr(0, 0);
	player1.isKnockBack = false;
	player1.isStun = false;
	player1.vx = 0;
	player1.vy = 0;

	player2.setHp(100);
	player2.setFacing(0);
	player2.setPosition(w_width-60, 340);
	player2.setSpr(0, 0);
	player2.isKnockBack = false;
	player2.isStun = false;
	player2.vx = 0;
	player2.vy = 0;

	time = 0;

	frameCount = player1.getSkillFrameTotal();
	frameCount2 = player2.getSkillFrameTotal();

	roundCount++;
}

void Game::moveCharacter(Champion &c, sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key jump, sf::Keyboard::Key barrier){
	if (!c.isAttacking() && !c.isStun && !c.isKnockBack){
		if (sf::Keyboard::isKeyPressed(right)) {
			c.move(0, 5, 0);
		}
		if (sf::Keyboard::isKeyPressed(left)) {
			c.move(5, 0, 0);
		}
		if (sf::Keyboard::isKeyPressed(jump) && c.isGrounded()) {
			c.move(0, 0, -4);
		}
		if (sf::Keyboard::isKeyPressed(barrier)) {
			c.move(0, 0, 0);
			c.setBarrier(true);
			c.calculateSpriteBlock();
		} 
		else{
			c.setBarrier(false);
		}
	}
}

void Game::operationSkill(Champion &c, int skillNumber, float &frameCount){
	c.setAttack(true);
	frameCount = 0;
	c.setSkillNumber(skillNumber);
	c.useSkill((int)frameCount);
	c.insertAOList(skillNumber);
}

void Game::attackCharacter(Champion& c,  sf::Keyboard::Key normal,  sf::Keyboard::Key skill1,  sf::Keyboard::Key skill2,  sf::Keyboard::Key skill3, float& frameCount){
	if (sf::Keyboard::isKeyPressed(normal) && !c.isAttacking() && !c.isStun && !c.isKnockBack) {
		operationSkill(c, 0, frameCount);
	}
	else if(sf::Keyboard::isKeyPressed(skill1) && !c.isAttacking() && !c.isStun && !c.isKnockBack) {
		operationSkill(c, 1, frameCount);
	}
	else if(sf::Keyboard::isKeyPressed(skill2) && !c.isAttacking() && !c.isStun && !c.isKnockBack) {
		operationSkill(c, 2, frameCount);
	}
	else if(sf::Keyboard::isKeyPressed(skill3) && !c.isAttacking()) {
		operationSkill(c, 3, frameCount);
	}
	if(c.isAttacking()){
		frameCount += FRAMESPEED;
		c.useSkill(frameCount);
		if(frameCount>c.getSkillFrameTotal()){
			c.setAttack(false);
			c.calculateSpritePos();
		}
	}
}

void Game::checkDeath(Champion &p1, Champion &p2, int &time, float &frameCount, float &frameCount2){
	if (p1.isDeath()) {										// player1이 죽었을 경우
		p2.playerWin();
		p2.isKnockBack = true;
		if(p2.getWinScore() >= 2){							// player2가 2승했을 경우
			p2_WS[1].setFillColor(sf::Color(225,225,0));	// 동그라미 색칠
			setGameOver(p2);								// 게임 종료 시작
		}
		else if(p2.getWinScore() >= 1){						// player2가 1승했을 경우
			p2_WS[0].setFillColor(sf::Color(225,225,0));	// 동그라미 색칠
			resetGame(p1, p2, time, frameCount, frameCount2);// 게임 다시 시작
		}
		p1.attackObjList.clear();							// aoList 초기화
		p2.attackObjList.clear();
	}
	if (p2.isDeath()) {										// player2가 죽었을 경우		
		p1.playerWin();	
		p1.isKnockBack = true;
		if(p1.getWinScore() >= 2){							// player1이 2승했을 경우
			p1_WS[1].setFillColor(sf::Color(225,225,0));	// 동그라미 색칠
			setGameOver(p1);								// 게임 종료 시작
		}
		else if(p1.getWinScore() >= 1){						// player1이 1승했을 경우
			p1_WS[0].setFillColor(sf::Color(225,225,0));	// 동그라미 색칠
			resetGame(p1, p2, time, frameCount, frameCount2);// 게임 다시 시작
		}
		p1.attackObjList.clear();							// aoList 초기화
		p2.attackObjList.clear();
	}
}

void Game::setChampionsFacing(Champion &p1, Champion &p2){
	if(p1.getPosition().x > p2.getPosition().x){
		p1.setFacing(0);
		p2.setFacing(1);
	}
	else{
		p1.setFacing(1);
		p2.setFacing(0);
	}
}

void Game::detectCollision_Champions(class Champion &p1, class Champion &p2, float &frameCount, float &frameCount2){
	p1.updateAOList();
	p1.deleteAOList();
	p1.detectCollision(p2, frameCount2);
	p2.updateAOList();
	p2.deleteAOList();
	p2.detectCollision(p1, frameCount);
}

void Game::setObject(){
	HpBar[0] = sf::RectangleShape(sf::Vector2f(350.f,25.f));
	HpBar[1] = sf::RectangleShape(sf::Vector2f(350.f,25.f));
		 
	HpBar[0].setFillColor(sf::Color(50,100,50));
    HpBar[0].setPosition(25.f,25.f);
    HpBar[1].setFillColor(sf::Color(50,100,50));
    HpBar[1].setPosition(775.f,25.f);
    HpBar[1].setScale(-1.f,1.f);

	p1_WS[0] = sf::CircleShape(10, 30);
	p1_WS[0].setPosition(25.f, 60.f);
	p1_WS[0].setFillColor(sf::Color(200,200,200));
	p1_WS[1] = sf::CircleShape(10, 30);
	p1_WS[1].setPosition(50.f, 60.f);
	p1_WS[1].setFillColor(sf::Color(200,200,200));
	p2_WS[0] = sf::CircleShape(10, 30);
	p2_WS[0].setPosition(730.f, 60.f);
	p2_WS[0].setFillColor(sf::Color(200,200,200));
	p2_WS[1] = sf::CircleShape(10, 30);
	p2_WS[1].setPosition(755.f, 60.f);
	p2_WS[1].setFillColor(sf::Color(200,200,200));

	bp1_WS[0] = sf::CircleShape(13, 30);
	bp1_WS[0].setPosition(25.f-3, 60.f-3);
	bp1_WS[0].setFillColor(sf::Color(0,0,0));
	bp1_WS[1] = sf::CircleShape(13, 30);
	bp1_WS[1].setPosition(50.f-3, 60.f-3);
	bp1_WS[1].setFillColor(sf::Color(0,0,0));
	bp2_WS[0] = sf::CircleShape(13, 30);
	bp2_WS[0].setPosition(730.f-3, 60.f-3);
	bp2_WS[0].setFillColor(sf::Color(0,0,0));
	bp2_WS[1] = sf::CircleShape(13, 30);
	bp2_WS[1].setPosition(755.f-3, 60.f-3);
	bp2_WS[1].setFillColor(sf::Color(0,0,0));

	round_start = false;
	fight_start = false;
	gameOver = false;
	isEnd = false;
}

void Game::drawWindow(){
	_myWindow->clear();
	_myWindow->draw(background);
	for(int x=0; x<2; x++){
		_myWindow->draw(HpBar[x]);
		_myWindow->draw(bp1_WS[x]);
		_myWindow->draw(bp2_WS[x]);
		_myWindow->draw(p1_WS[x]);
		_myWindow->draw(p2_WS[x]);
	}

	_myWindow->draw(player1_spr);
	_myWindow->draw(player2_spr);

	if(round_start){
		if(roundPanelPosX<100) panel_ax = -abs(panel_ax);
		panelSpeed -= panel_ax;
		roundPanelPosX -= panelSpeed;
		roundPanel[roundCount].setPosition(roundPanelPosX,roundPanelPosY);
		_myWindow->draw(roundPanel[roundCount]);
		if(roundPanelPosX<-600){
			round_start = false;
			fight_start = true;
			roundPanelPosX = 800;
			panelSpeed = 1.2;
			panel_ax = 0.001;
		}
	}
	if(fight_start){
		if(roundPanelPosX<100) panel_ax = -abs(panel_ax);
		panelSpeed -= panel_ax;
		roundPanelPosX -= panelSpeed;
		roundPanel[0].setPosition(roundPanelPosX,roundPanelPosY);
		_myWindow->draw(roundPanel[0]);
		if(roundPanelPosX<-600){
			fight_start = false;
			roundPanelPosX = 800;
			panelSpeed = 1.2;
			panel_ax = 0.001;
		}
	}
	if(gameOver){
		if(winPanelSpeed < 0.01 && winPanelSpeed > 0 ){
			gameOverCount++;
		}
		else{
			if(winPanelPosX<200) panel_ax = -abs(panel_ax);
			winPanelSpeed -= winPanel_ax;
			winPanelPosX -= winPanelSpeed;
		}
		if(gameOverCount>500){
			winPanelSpeed = -0.1;
			gameOverCount++;
		}
		winPanel[winChampionNumber].setPosition(winPanelPosX,winPanelPosY);
		winPanelText[winChampionNumber].setPosition(+200-winPanelPosX,winPanelPosY+50);
		_myWindow->draw(winPanel[winChampionNumber]);
		_myWindow->draw(winPanelText[winChampionNumber]);
		if(gameOverCount>2000) isEnd = true;
	}
}

void Game::drawAttackObject(Champion &p1, Champion &p2){
	for(auto ao = p1.attackObjList.begin(); ao!= p1.attackObjList.end(); ao++){
		if((*ao)->isthrow){
			_myWindow->draw((*ao)->obj);
		}
	}

	for(auto ao = p2.attackObjList.begin(); ao!= p2.attackObjList.end(); ao++){
		if((*ao)->isthrow){
			_myWindow->draw((*ao)->obj);
		}
	}
}

void Game::setRoundPanel(){
	roundPanelPosX = 800;
	roundPanelPosY = 150;
	panelSpeed = 1.2;
	panel_ax = 0.001;
	roundPanelTexture[0].loadFromFile("./images/stage/fight.png");
	roundPanelTexture[1].loadFromFile("./images/stage/round1.png");
	roundPanelTexture[2].loadFromFile("./images/stage/round2.png");
	roundPanelTexture[3].loadFromFile("./images/stage/finalRound.png");
	roundPanel[0] = sf::RectangleShape(sf::Vector2f(600, 200));
	roundPanel[0].setTexture(&roundPanelTexture[0]);
	roundPanel[0].setTextureRect(sf::IntRect(0, 0, 357, 114));
	roundPanel[0].setPosition(roundPanelPosX,roundPanelPosY);
	roundPanel[1] = sf::RectangleShape(sf::Vector2f(600, 200));
	roundPanel[1].setTexture(&roundPanelTexture[1]);
	roundPanel[1].setTextureRect(sf::IntRect(0, 0, 357, 114));
	roundPanel[1].setPosition(roundPanelPosX,roundPanelPosY);
	roundPanel[2] = sf::RectangleShape(sf::Vector2f(600, 200));
	roundPanel[2].setTexture(&roundPanelTexture[2]);
	roundPanel[2].setTextureRect(sf::IntRect(0, 0, 357, 114));
	roundPanel[2].setPosition(roundPanelPosX,roundPanelPosY);
	roundPanel[3] = sf::RectangleShape(sf::Vector2f(600, 200));
	roundPanel[3].setTexture(&roundPanelTexture[3]);
	roundPanel[3].setTextureRect(sf::IntRect(0, 0, 357, 114));
	roundPanel[3].setPosition(roundPanelPosX,roundPanelPosY);
}

void Game::setWinPanel(){
	winPanelPosX = 800;
	winPanelPosY = 0;
	winPanelSpeed = 1.25;
	winPanel_ax = 0.001;

	winPanelTexture[0].loadFromFile("./images/character_win/gpl_win_bigimage.png");
	winPanelTexture[1].loadFromFile("./images/character_win/bsd_win_bigimage.png");
	winPanelTexture[2].loadFromFile("./images/character_win/lgpl_win_bigimage.png");
	winPanelTexture[3].loadFromFile("./images/character_win/apache_win_bigimage.png");
	winPanelTexture[4].loadFromFile("./images/character_win/jang_win_bigimage.png");
	winPanelTextTexture[0].loadFromFile("./images/character_win/gpl_win_text.png");
	winPanelTextTexture[1].loadFromFile("./images/character_win/bsd_win_text.png");
	winPanelTextTexture[2].loadFromFile("./images/character_win/lgpl_win_text.png");
	winPanelTextTexture[3].loadFromFile("./images/character_win/apache_win_text.png");
	winPanelTextTexture[4].loadFromFile("./images/character_win/jang_win_text.png");
	winPanel[0] = sf::RectangleShape(sf::Vector2f(800, 500));
	winPanel[0].setTexture(&winPanelTexture[0]);
	winPanel[0].setTextureRect(sf::IntRect(0, 0, 800, 500));
	winPanel[0].setPosition(winPanelPosX,winPanelPosY);
	winPanel[1] = sf::RectangleShape(sf::Vector2f(800, 500));
	winPanel[1].setTexture(&winPanelTexture[1]);
	winPanel[1].setTextureRect(sf::IntRect(0, 0, 800, 500));
	winPanel[1].setPosition(winPanelPosX,winPanelPosY);
	winPanel[2] = sf::RectangleShape(sf::Vector2f(800, 500));
	winPanel[2].setTexture(&winPanelTexture[2]);
	winPanel[2].setTextureRect(sf::IntRect(0, 0, 800, 500));
	winPanel[2].setPosition(winPanelPosX,winPanelPosY);
	winPanel[3] = sf::RectangleShape(sf::Vector2f(800, 500));
	winPanel[3].setTexture(&winPanelTexture[3]);
	winPanel[3].setTextureRect(sf::IntRect(0, 0, 800, 500));
	winPanel[3].setPosition(winPanelPosX,winPanelPosY);
	winPanel[4] = sf::RectangleShape(sf::Vector2f(800, 500));
	winPanel[4].setTexture(&winPanelTexture[4]);
	winPanel[4].setTextureRect(sf::IntRect(0, 0, 800, 500));
	winPanel[4].setPosition(winPanelPosX,winPanelPosY);
	
	float reverse = -800-400;
	winPanelText[0] = sf::RectangleShape(sf::Vector2f(400, 80));
	winPanelText[0].setTexture(&winPanelTextTexture[0]);
	winPanelText[0].setTextureRect(sf::IntRect(0, 0, 248, 45));
	winPanelText[0].setPosition(winPanelPosX+reverse,winPanelPosY);
	winPanelText[1] = sf::RectangleShape(sf::Vector2f(400, 70));
	winPanelText[1].setTexture(&winPanelTextTexture[1]);
	winPanelText[1].setTextureRect(sf::IntRect(0, 0, 201, 37));
	winPanelText[1].setPosition(winPanelPosX+reverse,winPanelPosY);
	winPanelText[2] = sf::RectangleShape(sf::Vector2f(200, 200));
	winPanelText[2].setTexture(&winPanelTextTexture[2]);
	winPanelText[2].setTextureRect(sf::IntRect(0, 0, 124, 121));
	winPanelText[2].setPosition(winPanelPosX+reverse,winPanelPosY);
	winPanelText[3] = sf::RectangleShape(sf::Vector2f(400, 70));
	winPanelText[3].setTexture(&winPanelTextTexture[3]);
	winPanelText[3].setTextureRect(sf::IntRect(0, 0, 178, 31));
	winPanelText[3].setPosition(winPanelPosX+reverse,winPanelPosY);
	winPanelText[4] = sf::RectangleShape(sf::Vector2f(400, 80));
	winPanelText[4].setTexture(&winPanelTextTexture[4]);
	winPanelText[4].setTextureRect(sf::IntRect(0, 0, 215, 49));
	winPanelText[4].setPosition(winPanelPosX+reverse,winPanelPosY);
}

void Game::setGameOver(Champion& winChamp){
	winChampionNumber = winChamp.getModelNumber();
	gameOverCount = 0;
	gameOver = true;
}