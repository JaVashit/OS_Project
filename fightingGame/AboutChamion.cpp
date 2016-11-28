#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "AboutChampion.hpp"

const int maxFrame = 400;

AboutChampion::AboutChampion(sf::RenderWindow *window):_windows(window)
{
	nextPageFrame = 0;
	nextPage = false;
	
	ac_Texture[0].loadFromFile("./images/aboutChampion/ac_gpl.png");
	ac_Texture[1].loadFromFile("./images/aboutChampion/ac_lgpl.png");
	ac_Texture[2].loadFromFile("./images/aboutChampion/ac_apache.png");
	ac_Texture[3].loadFromFile("./images/aboutChampion/ac_bsd.png");

	click_sPos[0] = sf::Vector2f(0,0);
	click_sPos[1] = sf::Vector2f(650,0);
	click_sPos[2] = sf::Vector2f(700,0);
	click_sPos[3] = sf::Vector2f(750,0);
	click_ePos[0] = sf::Vector2f(650,500);
	click_ePos[1] = sf::Vector2f(700,500);
	click_ePos[2] = sf::Vector2f(750,500);
	click_ePos[3] = sf::Vector2f(800,500);

	spreadOn = 0;

	for(int x=0; x<4; x++){
		mouseOn[x] = false;
		clickOn[x] = false;
		ac_Rect[x] = sf::RectangleShape(sf::Vector2f(click_ePos[x].x - click_sPos[x].x, click_ePos[x].y - click_sPos[x].y));
		ac_Rect[x].setTexture(&ac_Texture[x]);
		ac_Rect[x].setTextureRect(sf::IntRect(0, 0, (click_ePos[x].x- click_sPos[x].x)/650*1500, 839));
		ac_Rect[x].setPosition(click_sPos[x].x, click_sPos[x].y);
	}
}

void AboutChampion::run(){
	sf::Vector2u getWindowSize;
	sf::Event e;
	while (_windows->isOpen()) {
		
		getWindowSize = _windows->getSize();

		mousepos = sf::Mouse::getPosition(*_windows);
		updateMouseOn(mousepos);

		while (_windows->pollEvent(e)){
			if(e.type == sf::Event::MouseButtonPressed){
				setClick();
			}
		}
		if(nextPage){
			updateRectPos();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) return;
		_windows->clear();
		setColor();
		_windows->display();
	}
}

void AboutChampion::setColor(){
	for(int x=0; x<4; x++){
		if(mouseOn[x] && !clickOn[x] && !mouseOn[spreadOn]){
			if(x==0)
				ac_Rect[x].setFillColor(sf::Color(255,200,100));
			if(x==1)
				ac_Rect[x].setFillColor(sf::Color(255,125,125));
			if(x==2)
				ac_Rect[x].setFillColor(sf::Color(255,125,255));
			if(x==3)
				ac_Rect[x].setFillColor(sf::Color(125,125,255));
		}
		else if(x != spreadOn){
			if(x==0)
				ac_Rect[x].setFillColor(sf::Color(125,100,50));
			if(x==1)
				ac_Rect[x].setFillColor(sf::Color(125,65,65));
			if(x==2)
				ac_Rect[x].setFillColor(sf::Color(125,65,125));
			if(x==3)
				ac_Rect[x].setFillColor(sf::Color(65,65,125));
		}
		else{
			ac_Rect[x].setFillColor(sf::Color::White);
		}
		_windows->draw(ac_Rect[x]);
	}
}

void AboutChampion::setClick(){
	if(!nextPage && !mouseOn[spreadOn]){
		nextPage = true;
		for(int x=0; x<4; x++){
			clickOn[x] = mouseOn[x];
			if(clickOn[x]) spreadOn = x;
		}
	}
}

void AboutChampion::updateRectPos(){
	float _x = 0;
	for(int x=0; x<4; x++){
		if(clickOn[x]){
			if(_x < click_sPos[x].x){
				click_sPos[x].x-=1;
			}
			else if(_x > click_sPos[x].x){
				click_sPos[x].x+=1;
			}
			_x+=650;
			if(_x < click_ePos[x].x){
				click_ePos[x].x-=1;
			}
			else if(_x > click_ePos[x].x){
				click_ePos[x].x+=1;
			}
		}
		else{
			if(_x < click_sPos[x].x){
				click_sPos[x].x-=1;
			}
			else if(_x > click_sPos[x].x){
				click_sPos[x].x+=1;
			}
			_x+=50;
			if(_x < click_ePos[x].x){
				click_ePos[x].x-=1;
			}
			else if(_x > click_ePos[x].x){
				click_ePos[x].x+=1;
			}
		}
		ac_Rect[x] = sf::RectangleShape(sf::Vector2f(click_ePos[x].x - click_sPos[x].x, click_ePos[x].y - click_sPos[x].y));
		ac_Rect[x].setTexture(&ac_Texture[x]);
		ac_Rect[x].setTextureRect(sf::IntRect(0, 0, (click_ePos[x].x- click_sPos[x].x)/650*1500, 839));
		ac_Rect[x].setPosition(click_sPos[x].x, click_sPos[x].y);
	}
	nextPageFrame++;
	if(nextPageFrame > 800){
		nextPageFrame = 0;
		nextPage = false;
		for(int x=0; x<4; x++){
			clickOn[x] = false;
			ac_Rect[x] = sf::RectangleShape(sf::Vector2f(click_ePos[x].x - click_sPos[x].x, click_ePos[x].y - click_sPos[x].y));
			ac_Rect[x].setTexture(&ac_Texture[x]);
			ac_Rect[x].setTextureRect(sf::IntRect(0, 0, (click_ePos[x].x- click_sPos[x].x)/650*1500, 839));
			ac_Rect[x].setPosition(click_sPos[x].x, click_sPos[x].y);
		}
	}
}


void AboutChampion::updateMouseOn(sf::Vector2i mousePos){
	for(int x=0; x<4; x++){
		if(click_sPos[x].x < mousePos.x && click_ePos[x].x > mousePos.x && click_sPos[x].y < mousePos.y && click_ePos[x].y > mousePos.y){
			mouseOn[x] = true;	
		}
		else{
			mouseOn[x] = false;
		}

	}

}