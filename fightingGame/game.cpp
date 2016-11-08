#include <iostream>
//#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "character.hpp"
#include "game.hpp"
#include "Champion.hpp"

Game::Game(sf::RenderWindow *window): _myWindow(window){
    ay = 600;
    damage = 10;
    
    dmgred = 0.8;
	w_width = _myWindow->getSize().x;
	w_height = _myWindow->getSize().y;
}

int Game::Run()
{
    
    //Characters
    sf::Texture characterTexture;
    if (!characterTexture.loadFromFile("./images/vx_characters.png")) std::cout << "Error loading vx_characters" << std::endl;
    
    //Background
    sf::Texture backgroundTexture;    
    if (!backgroundTexture.loadFromFile("./images/FightGameBG.png")) std::cout << "Error loading citybg" << std::endl;
    sf::RectangleShape background(sf::Vector2f(800.f,500.f));
    background.setTexture(&backgroundTexture);
    
	ay = 600;
    damage = 10;
    
    
    Character character1(1);
    Character character2(2);
	Champion c1 = Champion(1, 0, w_width, w_height);
	Champion c2 = Champion(0, 0, w_width, w_height);
    
    //Create and load player 1 arguments
    sf::Sprite player1;
    player1.setTexture(characterTexture);                       //Load texture to sprite
    c1.loadCharacter(player1);                    //Select character texture, scale, origin
 
    //Create and load player 2 arguments
    sf::Sprite player2; 
    player2.setTexture(characterTexture);
    c2.loadCharacter(player2);

   
    //HP Bars
    sf::RectangleShape HpBar1(sf::Vector2f(350.f,25.f)), HpBar2(sf::Vector2f(350.f,25.f));
    HpBar1.setFillColor(sf::Color(50,100,50));
    HpBar1.setPosition(25.f,25.f);
    HpBar2.setFillColor(sf::Color(50,100,50));
    HpBar2.setPosition(775.f,25.f);
    HpBar2.setScale(-1.f,1.f);
	sf::RectangleShape MpBar1(sf::Vector2f(350.f,10.f)), MpBar2(sf::Vector2f(350.f,10.f));
    MpBar1.setFillColor(sf::Color(255,255,0));
    MpBar1.setPosition(25.f,45.f);
    MpBar2.setFillColor(sf::Color(255,255,0));
    MpBar2.setPosition(775.f,45.f);
    MpBar2.setScale(-1.f,1.f);
    
    sf::Music music;
   if (!music.openFromFile("./music/FightMusic.ogg")) std::cout << "Error loading normal music" << std:: endl;
    
    music.play();
    
    //Other variables
    
    while (_myWindow->isOpen())
    {
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
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				c1.move(0, 5, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				c1.move(5, 0, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && c1.isGrounded()) {
				c1.move(0, 0, -5);
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			c1.setAttack(true);
            c1.calculateSpritePunch();
            //player1.setTextureRect(sf::IntRect(c1.getSpr().x,c1.getSpr().y,32,32));
        }
		else{
			c1.setAttack(false);
			//c1.calculateSpritePos(0);
		}
        
        //Player 2 movement
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Dash)){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				c2.move(0, 5, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				c2.move(5, 0, 0);
            }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up )&& c2.isGrounded()) {
				c2.move(0, 0, -5);
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash)) {
            c2.setAttack(true);
            c2.calculateSpritePunch();
			//player2.setTextureRect(sf::IntRect(c2.getSpr().x,c2.getSpr().y,32,32));
        }
		else{
			c2.setAttack(false);
			//c2.calculateSpritePos(0);
		}

		if(c1.getPosition().x > c2.getPosition().x){
			c1.setFacing(0);
			c2.setFacing(1);
		}
		else{
			c1.setFacing(1);
			c2.setFacing(0);
		}

        //Sprite update
		if(!c1.isAttacking() && !c1.isBarrier()){
			c1.calculateSpritePos(0);
		}
		if(!c2.isAttacking() && !c2.isBarrier()){
			c2.calculateSpritePos(0);
		}
		player1.setTextureRect(sf::IntRect(c1.getSpr().x, c1.getSpr().y, 32, 32));
        player2.setTextureRect(sf::IntRect(c2.getSpr().x, c2.getSpr().y, 32, 32));
		
		//Character position update
		c1.caculatePosY();
		c2.caculatePosY();
		player1.setPosition(c1.getPosition());
		player2.setPosition(c2.getPosition());
		
		//HP, MP bars update
		HpBar1.setScale(c1.getHp()/100*1.f,1.f);
		HpBar2.setScale(-c2.getHp()/100*1.f,1.f);
		MpBar1.setScale(c1.getMp()/100*1.f,1.f);
		MpBar2.setScale(-c2.getMp()/100*1.f,1.f);
		
		if (c1.getHp() <= 0) {
			return 1;
		}
		if (c2.getHp() <= 0) {
			return 0;
		}

        _myWindow->clear();
        _myWindow->draw(background);
        _myWindow->draw(HpBar1);
        _myWindow->draw(HpBar2);
		_myWindow->draw(MpBar1);
        _myWindow->draw(MpBar2);
        _myWindow->draw(player2);
        _myWindow->draw(player1);
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