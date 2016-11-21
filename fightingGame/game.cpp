#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "game.hpp"
#include "Champion.hpp"
#include "GPL.hpp"
#include "BSD.hpp"
#include "Jang.h"

Game::Game(sf::RenderWindow *window): _myWindow(window){
    ay = 600;
    damage = 10;
    
    dmgred = 0.8;
	w_width = _myWindow->getSize().x;
	w_height = _myWindow->getSize().y;
	background =  sf::RectangleShape(sf::Vector2f(800.f,500.f));

	//Characters
    if (!characterTexture.loadFromFile("./images/character/bsd_sprite.png")) std::cout << "Error loading vx_characters" << std::endl;
    if (!characterTexture2.loadFromFile("./images/character/gpl_sprite.png")) std::cout << "Error loading vx_characters" << std::endl;

	//Background
    if (!backgroundTexture.loadFromFile("./images/stage/stage01.png")) std::cout << "Error loading citybg" << std::endl;

	//music
	if (!music.openFromFile("./music/FightMusic.ogg")) std::cout << "Error loading normal music" << std:: endl;
}

int Game::Run()
{
    setObject();
	BSD c1 = BSD(1, 0, w_width, w_height);
	GPL c2 = GPL(0, 0, w_width, w_height);

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
        while (_myWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                _myWindow->close();
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            return -1;
        }
        
        //Player 1 movement
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !c1.isStun && !c1.isKnockBack){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				c1.move(0, 5, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				c1.move(5, 0, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && c1.isGrounded()) {
				c1.move(0, 0, -4);
			}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				c1.move(0, 0, 0);
				c1.setBarrier(true);
				c1.calculateSpriteBlock();
				//player1.setTextureRect(sf::IntRect(c1.getSpr().x,c1.getSpr().y,32,32));
			} 
			else{
				c1.setBarrier(false);
			}
        }
        //Player 1 actions
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !c1.isAttacking() && !c1.isStun && !c1.isKnockBack) {
			c1.setAttack(true);
			frameCount = 0;
			c1.setSkillNumber(0);
			c1.useSkill(c1.getSkillNumber(), (int)frameCount);
			c1.insertAOList(0);
        }
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && !c1.isAttacking() && !c1.isStun && !c1.isKnockBack) {
			c1.setAttack(true);
			frameCount = 0;
			c1.setSkillNumber(1);
			c1.useSkill(c1.getSkillNumber(), (int)frameCount);
			c1.insertAOList(1);
        }
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && !c1.isAttacking() && !c1.isStun && !c1.isKnockBack) {
			c1.setAttack(true);
			frameCount = 0;
			c1.setSkillNumber(2);
			c1.useSkill(c1.getSkillNumber(), (int)frameCount);
			c1.insertAOList(2);
        }
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && !c1.isAttacking()) {
			frameCount = 0;
			c1.setSkillNumber(3);
			c1.useSkill(c1.getSkillNumber(), (int)frameCount);
			c1.insertAOList(3);
        }
		if(c1.isAttacking()){
			frameCount += 0.02;
			c1.useSkill(c1.getSkillNumber(), (int)frameCount);
			if(frameCount>c1.getSkillFrameTotal()){
				c1.setAttack(false);
				c1.calculateSpritePos(0);
			}
		}
        
        //Player 2 movement
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Dash) && !c2.isStun && !c2.isKnockBack){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				c2.move(0, 5, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				c2.move(5, 0, 0);
            }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up )&& c2.isGrounded()) {
				c2.move(0, 0, -4);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				c2.move(0, 0, 0);
				c2.setBarrier(true);
				c2.calculateSpriteBlock();
				//player2.setTextureRect(sf::IntRect(c2.getSpr().x,c2.getSpr().y,32,32));
			} 
			else{
				c2.setBarrier(false);
			}
        }
        //Player 2 actions
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8) && !c2.isAttacking() && !c2.isStun && !c2.isKnockBack) {
			c2.setAttack(true);
			frameCount2 = 0;
			c2.setSkillNumber(0);
			c2.useSkill(c2.getSkillNumber(), (int)frameCount2);
			c2.insertAOList(0);
        }
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num9) && !c2.isAttacking() && !c2.isStun && !c2.isKnockBack) {
			c2.setAttack(true);
			frameCount2 = 0;
			c2.setSkillNumber(1);
			c2.useSkill(c2.getSkillNumber(), (int)frameCount2);
			c2.insertAOList(1);
        }
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0) && !c2.isAttacking() && !c2.isStun && !c2.isKnockBack) {
			c2.setAttack(true);
			frameCount2 = 0;
			c2.setSkillNumber(2);
			c2.useSkill(c2.getSkillNumber(), (int)frameCount2);
			c2.insertAOList(2);
        }
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Dash) && !c2.isAttacking()) {
			frameCount2 = 0;
			c2.setSkillNumber(3);
			c2.useSkill(c2.getSkillNumber(), (int)frameCount2);
			c2.insertAOList(3);
        }
		if(c2.isAttacking()){
			frameCount2 += 0.02;
			c2.useSkill(c2.getSkillNumber(), (int)frameCount2);
			if(frameCount2>c2.getSkillFrameTotal()){
				c2.setAttack(false);
				c2.calculateSpritePos(0);
			}
		}

		if(c1.getPosition().x > c2.getPosition().x){
			c1.setFacing(0);
			c2.setFacing(1);
		}
		else{
			c1.setFacing(1);
			c2.setFacing(0);
		}

		c1.crowdControlHit(frameCount);
		c2.crowdControlHit(frameCount2);

        //Sprite update
		if(!c1.isAttacking() && !c1.isBarrier() && !c1.isKnockBack && !c1.isStun){
			c1.calculateSpritePos(0);
		}
		if(!c2.isAttacking() && !c2.isBarrier() && !c2.isKnockBack && !c2.isStun){
			c2.calculateSpritePos(0);
		}
		
		player1_spr.setTextureRect(sf::IntRect((int)c1.getSpr().x, (int)c1.getSpr().y, 170, 100));
        player2_spr.setTextureRect(sf::IntRect((int)c2.getSpr().x, (int)c2.getSpr().y, 170, 100));
		
		//Character position update
		c1.caculatePosXY();
		c2.caculatePosXY();
		player1_spr.setPosition(c1.getPosition());
		player2_spr.setPosition(c2.getPosition());
		
		//HPbars update
		HpBar1.setScale(c1.getHp()/100*1.f,1.f);
		HpBar2.setScale(-c2.getHp()/100*1.f,1.f);
		
		if (c1.isDeath()) {
			c2.playerWin();
			c2.isKnockBack = true;
			if(c2.getWinScore() >= 2){
				music.stop();
				return 0;
			}
			else if(c2.getWinScore() >= 1){
				p2_WS1.setFillColor(sf::Color(225,225,0));
			}
			resetGame(c1, c2);
			c1.attackObjList.clear();
			c2.attackObjList.clear();
		}
		if (c2.isDeath()) {
			c1.playerWin();
			if(c1.getWinScore() >= 2){
				music.stop();
				return 0;
			}
			else if(c1.getWinScore() >= 1){
				p1_WS1.setFillColor(sf::Color(225,225,0));
			}
			resetGame(c1, c2);
			c1.attackObjList.clear();
			c2.attackObjList.clear();
		}
		if(c1.getFacing()){
			player1_spr.setScale(-2.f, 2.f);
		}
		else{
			player1_spr.setScale(2.f, 2.f);
		}
		if(c2.getFacing()){
			player2_spr.setScale(-2.f, 2.f);
		}
		else{
			player2_spr.setScale(2.f, 2.f);
		}
		c1.updateAOList();
		c1.deleteAOList();
		c1.detectCollision(c2, frameCount2);
		c2.updateAOList();
		c2.deleteAOList();
		c2.detectCollision(c1, frameCount);

        _myWindow->clear();
        _myWindow->draw(background);
        _myWindow->draw(HpBar1);
        _myWindow->draw(HpBar2);
		_myWindow->draw(bp1_WS1);
		_myWindow->draw(bp1_WS2);
		_myWindow->draw(bp2_WS1);
		_myWindow->draw(bp2_WS2);
		_myWindow->draw(p1_WS1);
		_myWindow->draw(p1_WS2);
		_myWindow->draw(p2_WS1);
		_myWindow->draw(p2_WS2);

		for(auto q = c1.attackObjList.begin(); q!= c1.attackObjList.end(); q++){
			/*sf::RectangleShape a(sf::Vector2f((*q)->range_e.x-(*q)->range_s.x, (*q)->range_e.y-(*q)->range_s.y));
			a.setFillColor(sf::Color(255,0,0));
			a.setPosition(sf::Vector2f(((*q)->range_e.x+(*q)->range_s.x)/2, ((*q)->range_e.y+(*q)->range_s.y)/2));
			_myWindow->draw(a);*/
			if((*q)->isthrow){
				_myWindow->draw((*q)->obj);
			}
		}

		for(auto q = c2.attackObjList.begin(); q!= c2.attackObjList.end(); q++){
			if((*q)->isthrow){
				_myWindow->draw((*q)->obj);
			}
		}

		_myWindow->draw(player1_spr);
		_myWindow->draw(player2_spr);
		_myWindow->display();
    }
 
    return 0;
}



int Game::setScore(bool player,int scoreValue){
    if (!player){
		score1 = scoreValue;
		return score1;
	}
	else {
		score2 = scoreValue;
		return score2;
	}
}

int Game::getScore(bool player){
    if (!player) return score1;
    else return score2;
}

void Game::resetGame(Champion &player1, Champion &player2){
	player1.setHp(100);
	player1.setMp(0);
	player1.setFacing(1);
	player1.setPosition(60, 340);
	player1.setSpr(0, 0);
	player1.isKnockBack = false;
	player1.isStun = false;
	player1.vx = 0;

	player2.setHp(100);
	player2.setMp(0);
	player2.setFacing(0);
	player2.setPosition(w_width-60, 340);
	player2.setSpr(0, 0);
	player2.isKnockBack = false;
	player2.isStun = false;
	player2.vx = 0;
}

void Game::setObject(){
	HpBar1 = sf::RectangleShape(sf::Vector2f(350.f,25.f));
	HpBar2 = sf::RectangleShape(sf::Vector2f(350.f,25.f));

	HpBar1.setFillColor(sf::Color(50,100,50));
    HpBar1.setPosition(25.f,25.f);
    HpBar2.setFillColor(sf::Color(50,100,50));
    HpBar2.setPosition(775.f,25.f);
    HpBar2.setScale(-1.f,1.f);

	p1_WS1 = sf::CircleShape(10, 30);
	p1_WS1.setPosition(25.f, 60.f);
	p1_WS1.setFillColor(sf::Color(200,200,200));
	p1_WS2 = sf::CircleShape(10, 30);
	p1_WS2.setPosition(50.f, 60.f);
	p1_WS2.setFillColor(sf::Color(200,200,200));
	p2_WS1 = sf::CircleShape(10, 30);
	p2_WS1.setPosition(730.f, 60.f);
	p2_WS1.setFillColor(sf::Color(200,200,200));
	p2_WS2 = sf::CircleShape(10, 30);
	p2_WS2.setPosition(755.f, 60.f);
	p2_WS2.setFillColor(sf::Color(200,200,200));

	bp1_WS1 = sf::CircleShape(13, 30);
	bp1_WS1.setPosition(25.f-3, 60.f-3);
	bp1_WS1.setFillColor(sf::Color(0,0,0));
	bp1_WS2 = sf::CircleShape(13, 30);
	bp1_WS2.setPosition(50.f-3, 60.f-3);
	bp1_WS2.setFillColor(sf::Color(0,0,0));
	bp2_WS1 = sf::CircleShape(13, 30);
	bp2_WS1.setPosition(730.f-3, 60.f-3);
	bp2_WS1.setFillColor(sf::Color(0,0,0));
	bp2_WS2 = sf::CircleShape(13, 30);
	bp2_WS2.setPosition(755.f-3, 60.f-3);
	bp2_WS2.setFillColor(sf::Color(0,0,0));
}