#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Opening.hpp"

Opening::Opening(sf::RenderWindow *window):_windows(window)
{

	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("./images/stage/stage01.png")) std::cout << "Error loading citybg" << std::endl;
	sf::Texture BSD;
	if (!BSD.loadFromFile("./images/character_win/bsd_win_bigimage.png")) std::cout << "Error loading b1h" << std::endl;
	sf::Texture GPL;
	if (!GPL.loadFromFile("./images/character_win/gpl_win_bigimage.png")) std::cout << "Error loading b1" << std::endl;
	sf::Texture APACHE;
	if (!APACHE.loadFromFile("./images/character_win/apache_win_bigimage.png")) std::cout << "Error loading b2h" << std::endl;
	sf::Texture JANG;
	if (!JANG.loadFromFile("./images/character_win/jang_win_bigimage.png")) std::cout << "Error loading b2" << std::endl;
	sf::Texture LGPL;
	if (!LGPL.loadFromFile("./images/character_win/lgpl_win_bigimage.png")) std::cout << "Error loading b3h" << std::endl;
	
	sf::RectangleShape background(sf::Vector2f(800.f, 500.f));
	background.setTexture(&backgroundTexture);
	background.setFillColor(sf::Color(0,0,0));

	const int maxFrame = 400;
	
	sf::RectangleShape gpl_rect(sf::Vector2f(400.f, 250.f));
	gpl_rect.setTexture(&GPL);
	gpl_rect.setFillColor(sf::Color(255,120,0));
	gpl_rect.setTextureRect(sf::IntRect(80, 50, 800, 500));
	gpl_rect.setPosition(0-maxFrame,0);
	sf::RectangleShape gpl_spr(sf::Vector2f(400.f, 250.f));
	gpl_spr.setTexture(&GPL);
	gpl_spr.setTextureRect(sf::IntRect(0, 0, 800, 500));
	gpl_spr.setPosition(0-maxFrame,0);

	sf::RectangleShape bsd_rect(sf::Vector2f(400.f, 250.f));
	bsd_rect.setTexture(&BSD);
	bsd_rect.setFillColor(sf::Color(0,80,255));
	bsd_rect.setTextureRect(sf::IntRect(80, 50, 800, 500));
	bsd_rect.scale(-1, 1);
	bsd_rect.setPosition(maxFrame+800,0);
	sf::RectangleShape bsd_spr(sf::Vector2f(400.f, 250.f));
	bsd_spr.setTexture(&BSD);
	bsd_spr.scale(-1, 1);
	bsd_spr.setTextureRect(sf::IntRect(0, 0, 800, 500));
	bsd_spr.setPosition(maxFrame+800,0);

	sf::RectangleShape lgpl_rect(sf::Vector2f(400.f, 250.f));
	lgpl_rect.setTexture(&LGPL);
	lgpl_rect.setFillColor(sf::Color(180,125,125));
	lgpl_rect.setTextureRect(sf::IntRect(80, 50, 800, 500));
	lgpl_rect.setPosition(0,250+maxFrame);
	sf::RectangleShape lgpl_spr(sf::Vector2f(400.f, 250.f));
	lgpl_spr.setTexture(&LGPL);
	lgpl_spr.setTextureRect(sf::IntRect(0, 0, 800, 500));
	lgpl_spr.setPosition(0,250+maxFrame);

	sf::RectangleShape apa_rect(sf::Vector2f(400.f, 250.f));
	apa_rect.setTexture(&APACHE);
	apa_rect.setFillColor(sf::Color(150,0,150));
	apa_rect.setTextureRect(sf::IntRect(80, 50, 800, 500));
	apa_rect.setPosition(800+maxFrame,250);
	apa_rect.scale(-1, 1);
	sf::RectangleShape apa_spr(sf::Vector2f(400.f, 250.f));
	apa_spr.setTexture(&APACHE);
	apa_spr.setTextureRect(sf::IntRect(0, 0, 800, 500));
	apa_spr.setPosition(800+maxFrame,250);
	apa_spr.scale(-1, 1);



	sf::Font font;
	if (!font.loadFromFile("./images/OCR_A_Std.ttf")) std::cout << "Error loading font" << std::endl;



	sf::Music music;
	if (!music.openFromFile("./music/MenuMusic.ogg")) std::cout << "Error loading music" << std::endl;
	music.play();
	sf::Vector2u getWindowSize;
	float gpl_count = 0;
	float bsd_count = 0;
	float lgpl_count = 0;
	float apa_count = 0;
	float j_count = 0;
	float final_count = 0;
	bool gpl_start = true;
	bool bsd_start = false;
	bool lgpl_start = false;
	bool apa_start = false;
	bool j_start = false;

	while (_windows->isOpen()) {
		sf::Event event;
		getWindowSize = _windows->getSize();
		_windows->draw(background);
		_windows->draw(gpl_rect);
		_windows->draw(gpl_spr);
		_windows->draw(bsd_rect);
		_windows->draw(bsd_spr);
		_windows->draw(lgpl_rect);
		_windows->draw(lgpl_spr);
		_windows->draw(apa_rect);
		_windows->draw(apa_spr);
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
				if(final_count>500)
					break;
			}
			else{
				apa_count+=1;
			}
		}

		_windows->display();
	}
}