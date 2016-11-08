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
	Champion c1 = Champion(1, 0);
	Champion c2 = Champion(0, 0);
    
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
    
    
    sf::Music music;
   if (!music.openFromFile("./music/FightMusic.ogg")) std::cout << "Error loading normal music" << std:: endl;
    
    music.play();
    
    //Other variables
    
    sf::Clock deltaClock;
    
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
		if (c1.isGrounded() && ! sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            } 
        }
        //Player 1 actions
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            
           
            player1.setTextureRect(sf::IntRect(character1.spr.x,character1.spr.y,32,32));
        }
        
        //Player 2 movement
        if (! sf::Keyboard::isKeyPressed(sf::Keyboard::Dash)){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                
                
                player2.setTextureRect(sf::IntRect(character2.spr.x,character2.spr.y,32,32));
            } 
        }
        //Player 2 actions
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash)) {
            //Player 1      Player 2 
            
            //Player 2      Player 1
        }
        else if (! sf::Keyboard::isKeyPressed(sf::Keyboard::Dash)){
            character2.CalculateSpritePos(0);
        }
 
        //Sprite update
        
        //Character position update
            
        //HP bars update
            HpBar1.setScale(character1.hp/100*1.f,1.f);
            HpBar2.setScale(-character2.hp/100*1.f,1.f);
            if (character1.hp <= 0) {
                return 1;
            }
            if (character2.hp <= 0) {
                return 0;
            }
            
        _myWindow->clear();
        _myWindow->draw(background);
        _myWindow->draw(HpBar1);
        _myWindow->draw(HpBar2);
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