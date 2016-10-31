#include <iostream>
//#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "character.hpp"
#include "game.hpp"

Game::Game(sf::RenderWindow *window): _myWindow(window){
    ay = 600;
    damage = 10;
    hell = 0;
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
    if (hell) {
        background.setFillColor(sf::Color::Red);
        ay = 3000;
        damage = 20;
    } else {
        ay = 600;
        damage = 10;
    }
    
    Character character1(1);
    Character character2(2);
    
    //Create and load player 1 arguments
    sf::Sprite player1;
    player1.setTexture(characterTexture);                       //Load texture to sprite
    character1.LoadCharacter(player1);                    //Select character texture, scale, origin
 
    //Create and load player 2 arguments
    sf::Sprite player2; 
    player2.setTexture(characterTexture);
    character2.LoadCharacter(player2);

   
    //HP Bars
    sf::RectangleShape HpBar1(sf::Vector2f(350.f,25.f)), HpBar2(sf::Vector2f(350.f,25.f));
    HpBar1.setFillColor(sf::Color(50,100,50));
    HpBar1.setPosition(25.f,25.f);
    HpBar2.setFillColor(sf::Color(50,100,50));
    HpBar2.setPosition(775.f,25.f);
    HpBar2.setScale(-1.f,1.f);
    
    
    sf::Music music;
    if (hell){
        if (!music.openFromFile("./music/HellMusic.ogg")) std::cout << "Error loading Hell music" << std:: endl;
    } else {
        if (!music.openFromFile("./music/FightMusic.ogg")) std::cout << "Error loading normal music" << std:: endl;
    }
    music.play();
    
    //Other variables
    float gametime1 = 0, gametime2 = 0;
    int step1 = 0, step2 = 0;
    bool grounded1 = 1, grounded2 = 1, selectskin1 = 0, selectskin2 = 0, punch1 = 1, punch2 = 1;
    bool blocking1 = 0, blocking2 = 0;
    
    sf::Clock deltaClock;
    
    while (_myWindow->isOpen())
    {
        sf::Time deltaTime = deltaClock.restart();
        gametime1 += deltaTime.asSeconds();
        gametime2 += deltaTime.asSeconds();
        
        sf::Event event;
        while (_myWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                _myWindow->close();
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            return -1;
        }
        
        
        //Skin selector
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) && !selectskin1){    
            character1.NextSkin();
            selectskin1 = true;
        }
        else if (! sf::Keyboard::isKeyPressed(sf::Keyboard::N) && selectskin1) {
            selectskin1 = false;
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::M) && !selectskin2){    
            character2.NextSkin();
            selectskin2 = true;  
        }
        else if (! sf::Keyboard::isKeyPressed(sf::Keyboard::M) && selectskin2) {
            selectskin2 = false;
        }
 
        
        //Player 1 movement
        if (grounded1 && ! sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                if (!hell) character1.vel.x += 20;
                else character1.vel.x += 60;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                if (!hell) character1.vel.x -= 20;
                else character1.vel.x -= 60;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                character1.vel.y = -200;
                grounded1 = 0;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                character1.vel.x = 0;
                blocking1 = true;
                
                
                character1.CalculateSpriteBlock();
                player1.setTextureRect(sf::IntRect(character1.spr.x,character1.spr.y,32,32));
                
                
                if (character1.hp < 100.f) {
                    if (!hell) character1.hp += 2.5*deltaTime.asSeconds();
                    else character1.hp += 30*deltaTime.asSeconds();
                }
            } else blocking1 = false;
        }
        //Player 1 actions
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !punch1 && ! sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            if (character1.pos.x <= character2.pos.x+75 && character1.pos.x > character2.pos.x && abs(character2.pos.y-character1.pos.y) <= 25 && character1.facing == 0){
                if (character2.facing == 1 && blocking2){
                    character2.hp -= damage*(1-blocking2*dmgred);
                } else {
                    character2.hp -= damage;
                }
            }
            else if (character1.pos.x >= character2.pos.x-75 && character1.pos.x < character2.pos.x && abs(character2.pos.y-character1.pos.y) <= 25 && character1.facing == 1){
                if (character2.facing == 0 && blocking2){
                    character2.hp -= damage*(1-blocking2*dmgred);
                } else {
                    character2.hp -= damage;
                }
            }
            punch1 = true;
            character1.CalculateSpritePunch();
            player1.setTextureRect(sf::IntRect(character1.spr.x,character1.spr.y,32,32));
        }
        else if (! sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && punch1){
            punch1 = false;
            character1.CalculateSpritePos(0);
        }
        
        
        
        //Player 2 movement
        if (grounded2 && ! sf::Keyboard::isKeyPressed(sf::Keyboard::Dash)){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                if (!hell) character2.vel.x += 20;
                else character2.vel.x += 60;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                if (!hell) character2.vel.x -= 20;
                else character2.vel.x -= 60;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                character2.vel.y = -200;
                grounded2 = 0;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                character2.vel.x = 0;
                blocking2 = true;
                
                character2.CalculateSpriteBlock();
                player2.setTextureRect(sf::IntRect(character2.spr.x,character2.spr.y,32,32));
                
                if (character2.hp < 100.f) {
                    if (!hell) character2.hp += 2.5*deltaTime.asSeconds();
                    else character2.hp += 30*deltaTime.asSeconds();
                }
            } else blocking2 = false;
        }
        //Player 2 actions
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash) && !punch2 && !blocking2) {
            //Player 1      Player 2 
            if (character2.pos.x <= character1.pos.x+75 && character2.pos.x > character1.pos.x && abs(character1.pos.y-character2.pos.y) <= 25 && character2.facing == 0            ){
                if (character1.facing == 1 && blocking1){
                    character1.hp -= damage*(1-blocking1*dmgred);
                } else {
                    character1.hp -= damage;
                }
            }
            
            //Player 2      Player 1
            else if (character2.pos.x >= character1.pos.x-75 && character2.pos.x < character1.pos.x && abs(character1.pos.y-character2.pos.y) <= 25 && character2.facing == 1){
                if (character1.facing == 0 && blocking1){
                    character1.hp -= damage*(1-blocking1*dmgred);
                } else {
                    character1.hp -= damage;
                }
            }
            
            punch2 = true;
            character2.CalculateSpritePunch();
            player2.setTextureRect(sf::IntRect(character2.spr.x,character2.spr.y,32,32));
        }
        else if (! sf::Keyboard::isKeyPressed(sf::Keyboard::Dash) && punch2){
            punch2 = false;
            character2.CalculateSpritePos(0);
        }
 
        
 
        //X position updates
            if (character1.vel.x != 0){
                if (grounded1) character1.vel.x *= 0.9;
                else character1.vel.x *= 0.9995;
                character1.pos.x += character1.vel.x * deltaTime.asSeconds();
                
                if (abs(character1.vel.x) > 0.05 && grounded1) {
                    if (gametime1 >= 0.2) {
                        if (step1 == 0) step1 = 1;
                        else step1 = -step1;
                        gametime1 = 0;
                    }
                } else if (grounded1) {
                    character1.vel.x = 0;
                    step1 = 0;
                }
                if (! sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && ! sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                    if (character1.vel.x > 0) character1.facing = 1;
                    else if (character1.vel.x < 0) character1.facing = 0;
                    character1.CalculateSpritePos(step1);
                    player1.setTextureRect(sf::IntRect(character1.spr.x,character1.spr.y,32,32));
                }
                if (character1.pos.x < 30) {character1.pos.x = 30; character1.vel.x = 0;}
                else if (character1.pos.x > 770) {character1.pos.x = 770; character1.vel.x = 0;}
                
            }
            if (character2.vel.x != 0){
                if (grounded2) character2.vel.x *= 0.9;
                else character2.vel.x *= 0.9995;
                character2.pos.x += character2.vel.x * deltaTime.asSeconds();
                
                if (abs(character2.vel.x) > 0.05 && grounded2) {
                    if (gametime2 >= 0.2) {
                        if (step2 == 0) step2 = 1;
                        else step2 = -step2;
                        gametime2 = 0;
                    }
                } else if (grounded2) {
                    character2.vel.x = 0;
                    step2 = 0;
                }
                if (! sf::Keyboard::isKeyPressed(sf::Keyboard::Dash) && ! sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                    if (character2.vel.x > 0) character2.facing = 1;
                    else if (character2.vel.x < 0) character2.facing = 0;
                }
                if (character2.pos.x < 30) {character2.pos.x = 30; character2.vel.x = 0;}
                else if (character2.pos.x > 770) {character2.pos.x = 770; character2.vel.x = 0;}
            }
        //Y position updates
            if (!grounded1) {
                character1.vel.y += ay * deltaTime.asSeconds();
                character1.pos.y += character1.vel.y * deltaTime.asSeconds();
                if (character1.pos.y > 440) {grounded1 = 1; character1.vel.y = 0; character1.pos.y = 440;}
            }
            if (!grounded2) {
                character2.vel.y += ay * deltaTime.asSeconds();
                character2.pos.y += character2.vel.y * deltaTime.asSeconds();
                if (character2.pos.y > 440) {grounded2 = 1; character2.vel.y = 0; character2.pos.y = 440;}
            }
        
        //Sprite update
            if (!punch1 && !blocking1){
                character1.CalculateSpritePos(step1);
                player1.setTextureRect(sf::IntRect(character1.spr.x,character1.spr.y,32,32));
            }
            if (!punch2 && !blocking2){
                character2.CalculateSpritePos(step2);
                player2.setTextureRect(sf::IntRect(character2.spr.x,character2.spr.y,32,32));
            }
        
        //Character position update
            player1.setPosition(character1.pos.x, character1.pos.y);
            player2.setPosition(character2.pos.x, character2.pos.y);
            
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

void Game::Hell(){
    
    hell = (!hell);
    
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