#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Opening.hpp"

const int maxFrame = 400;

Opening::Opening(sf::RenderWindow *window):_windows(window)
{
	sf::Music music;
	if (!music.openFromFile("./music/MenuMusic.ogg")) std::cout << "Error loading music" << std::endl;
	music.play();
	sf::Vector2u getWindowSize;

	setOpeningObject();

	while (_windows->isOpen()) {
		sf::Event event;
		getWindowSize = _windows->getSize();

		updateChampionRect();

		_windows->clear();
		_windows->draw(background[0]);
		if(drawChampion){
			_windows->draw(gpl_rect);
			_windows->draw(gpl_spr);
			_windows->draw(bsd_rect);
			_windows->draw(bsd_spr);
			_windows->draw(lgpl_rect);
			_windows->draw(lgpl_spr);
			_windows->draw(apa_rect);
			_windows->draw(apa_spr);
		}
		else{
			_windows->draw(title);
			updateTitle(part2_frameCount++);
		}

		_windows->display();

		if(part2_frameCount > 6000){
			return;
		}
	}
}

void Opening::setOpeningObject(){

	gpl_count = 0;
	bsd_count = 0;
	lgpl_count = 0;
	apa_count = 0;
	j_count = 0;
	final_count = 0;
	part2_frameCount = 0;

	gpl_start = true;
	bsd_start = false;
	lgpl_start = false;
	apa_start = false;
	j_start = false;

	drawChampion = true;

	backgroundTexture[0].loadFromFile("./images/opening_background.png");
	titleTexture.loadFromFile("./images/opening_text.png");
	BSD.loadFromFile("./images/character_win/bsd_win_bigimage.png");
	GPL.loadFromFile("./images/character_win/gpl_win_bigimage.png");
	APACHE.loadFromFile("./images/character_win/apache_win_bigimage.png");
	JANG.loadFromFile("./images/character_win/jang_win_bigimage.png");
	LGPL.loadFromFile("./images/character_win/lgpl_win_bigimage.png");

	
	background[0] = sf::RectangleShape(sf::Vector2f(800, 500));
	background[0].setTexture(&backgroundTexture[0]);
	background[0].setTextureRect(sf::IntRect(0, 0, 800, 500));
	background[0].setPosition(0,0);
	title.setTexture(&titleTexture);
	title = sf::RectangleShape(sf::Vector2f(50, 16));
	title.setTexture(&titleTexture);
	title.setTextureRect(sf::IntRect(0, 0, 500, 160));
	title.setPosition(375, 242);

	gpl_rect = sf::RectangleShape(sf::Vector2f(400.f, 250.f));
	gpl_rect.setTexture(&GPL);
	gpl_rect.setFillColor(sf::Color(255,120,0));
	gpl_rect.setTextureRect(sf::IntRect(80, 50, 800, 500));
	gpl_rect.setPosition(0-maxFrame,0);
	gpl_spr = sf::RectangleShape(sf::Vector2f(400.f, 250.f));
	gpl_spr.setTexture(&GPL);
	gpl_spr.setTextureRect(sf::IntRect(0, 0, 800, 500));
	gpl_spr.setPosition(0-maxFrame,0);

	bsd_rect = sf::RectangleShape(sf::Vector2f(400.f, 250.f));
	bsd_rect.setTexture(&BSD);
	bsd_rect.setFillColor(sf::Color(0,80,255));
	bsd_rect.setTextureRect(sf::IntRect(80, 50, 800, 500));
	bsd_rect.scale(-1, 1);
	bsd_rect.setPosition(maxFrame+800,0);
	bsd_spr = sf::RectangleShape(sf::Vector2f(400.f, 250.f));
	bsd_spr.setTexture(&BSD);
	bsd_spr.scale(-1, 1);
	bsd_spr.setTextureRect(sf::IntRect(0, 0, 800, 500));
	bsd_spr.setPosition(maxFrame+800,0);

	lgpl_rect = sf::RectangleShape(sf::Vector2f(400.f, 250.f));
	lgpl_rect.setTexture(&LGPL);
	lgpl_rect.setFillColor(sf::Color(180,125,125));
	lgpl_rect.setTextureRect(sf::IntRect(80, 50, 800, 500));
	lgpl_rect.setPosition(0,250+maxFrame);
	lgpl_spr = sf::RectangleShape(sf::Vector2f(400.f, 250.f));
	lgpl_spr.setTexture(&LGPL);
	lgpl_spr.setTextureRect(sf::IntRect(0, 0, 800, 500));
	lgpl_spr.setPosition(0,250+maxFrame);

	apa_rect = sf::RectangleShape(sf::Vector2f(400.f, 250.f));
	apa_rect.setTexture(&APACHE);
	apa_rect.setFillColor(sf::Color(150,0,150));
	apa_rect.setTextureRect(sf::IntRect(80, 50, 800, 500));
	apa_rect.setPosition(800+maxFrame,250);
	apa_rect.scale(-1, 1);
	apa_spr = sf::RectangleShape(sf::Vector2f(400.f, 250.f));
	apa_spr.setTexture(&APACHE);
	apa_spr.setTextureRect(sf::IntRect(0, 0, 800, 500));
	apa_spr.setPosition(800+maxFrame,250);
	apa_spr.scale(-1, 1);

	
}

void Opening::updateChampionRect(){
	if(drawChampion){
		if(gpl_start){
			gpl_rect.setPosition(-maxFrame+gpl_count,0);
			gpl_spr.setPosition(-maxFrame+gpl_count,0);
			gpl_count+=1;
			if(gpl_count > maxFrame){
				gpl_start = false;
				bsd_start = true;
			}
		}
		if(bsd_start){
			bsd_rect.setPosition(maxFrame+800-bsd_count,0);
			bsd_spr.setPosition(maxFrame+800-bsd_count,0);
			bsd_count+=1;
			if(bsd_count > maxFrame){
				bsd_start = false;
				lgpl_start = true;
			}
		}
		if(lgpl_start){
			lgpl_rect.setPosition(0-maxFrame+lgpl_count,250);
			lgpl_spr.setPosition(0-maxFrame+lgpl_count,250);
			lgpl_count+=1;
			if(lgpl_count > maxFrame){
				lgpl_start = false;
				apa_start = true;
			}
		}
		if(apa_start){
			apa_rect.setPosition(800+maxFrame-apa_count,250);
			apa_spr.setPosition(800+maxFrame-apa_count,250);
			if(apa_count > maxFrame){
				final_count += 1;
				if(final_count>500){
					printf("over\n");
					drawChampion = false;
					part2_frameCount = 0;
					
				}	
			}
			else{
				apa_count+=1;
			}
		}
	}
}

void Opening::updateTitle(int frameCount){
	//title = sf::RectangleShape(sf::Vector2f(50, 16));
	int random1 = frameCount;
	int random2 = frameCount;
	frameCount /= 10;

	float width = 50+frameCount;
	float dy = 500/160;
	float height = width/dy;
	title = sf::RectangleShape(sf::Vector2f(width, height));
	title.setTexture(&titleTexture);
	title.setTextureRect(sf::IntRect(0, 0, 500, 160));
	title.setPosition((800 - width)/2+(rand()%10)-5, (500 - height)/2+(rand()%8)-4);
}