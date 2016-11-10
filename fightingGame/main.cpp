#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "game.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 500), "Game 100");
    
    sf::Texture backgroundTexture;    
    if (!backgroundTexture.loadFromFile("./images/FightGameMenu.png")) std::cout << "Error loading citybg" << std::endl;
    
    sf::Texture button1H;    
    if (!button1H.loadFromFile("./images/MenuButton1Hover.png")) std::cout << "Error loading b1h" << std::endl;
    sf::Texture button1NH;    
    if (!button1NH.loadFromFile("./images/MenuButton1.png")) std::cout << "Error loading b1" << std::endl;
    sf::Texture button2H;    
    if (!button2H.loadFromFile("./images/MenuButton2Hover.png")) std::cout << "Error loading b2h" << std::endl;
    sf::Texture button2NH;    
    if (!button2NH.loadFromFile("./images/MenuButton2.png")) std::cout << "Error loading b2" << std::endl;
    sf::Texture button3H;    
    if (!button3H.loadFromFile("./images/MenuButton3Hover.png")) std::cout << "Error loading b3h" << std::endl;
    sf::Texture button3NH;    
    if (!button3NH.loadFromFile("./images/MenuButton3.png")) std::cout << "Error loading b3" << std::endl;

    sf::RectangleShape background(sf::Vector2f(800.f,500.f));
    background.setTexture(&backgroundTexture);
    
    sf::RectangleShape button1(sf::Vector2f(300.f,85.f));
    button1.setTexture(&button1NH);
    button1.setPosition(250,100);
    sf::RectangleShape button2(sf::Vector2f(300.f,85.f));
    button2.setTexture(&button2NH);
    button2.setPosition(250,200);
    sf::RectangleShape button3(sf::Vector2f(300.f,85.f));
    button3.setTexture(&button3NH);
    button3.setPosition(250,300);
    
    Game game(&window);
    game.setScore(0,0);
    game.setScore(1,0);
    
    sf::Font font;
    if (!font.loadFromFile("./images/OCR_A_Std.ttf")) std::cout << "Error loading font" << std::endl;
    
    sf::Text score1;
    score1.setFont(font);
    score1.setPosition(25,25);
    score1.setCharacterSize(50);
    score1.setColor(sf::Color::Black);
    
    sf::Text score2;
    score2.setFont(font);
    score2.setPosition(725,25);
    score2.setCharacterSize(50);
    score2.setColor(sf::Color::Black);
    
  
    sf::Music music;
    if (!music.openFromFile("./music/MenuMusic.ogg")) std::cout << "Error loading music" << std::endl;
    music.play();
    
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("./music/ButtonFX.ogg")) std::cout << "Error loading fx" << std::endl;
    sf::Sound buttonSound;
    buttonSound.setBuffer(buffer);
    
    sf::SoundBuffer buffer2;
    if (!buffer2.loadFromFile("./music/death.ogg")) std::cout << "Error loading death sound" << std::endl;
    sf::Sound deathsound;
    deathsound.setBuffer(buffer2);
    deathsound.setVolume(50);
    
    
    bool fxtime = false;
    
    while (window.isOpen()){
        sf::Event event;
        sf::Vector2i mousepos = sf::Mouse::getPosition(window);
        
        std::stringstream ss1;
        std::stringstream ss2;
        std::string str1;
        std::string str2;
        ss1 << game.getScore(0);
        ss1 >> str1;
        score1.setString(str1);
        ss2 << game.getScore(1);
        ss2 >> str2;
        score2.setString(str2);
        
        
        if (mousepos.x > 250 && mousepos.x < 550) {
            if (mousepos.y >= 100 && mousepos.y <= 175){
                button1.setTexture(&button1H);
                if (!fxtime) {
                    buttonSound.play();
                    fxtime = true;
                }
            }
            else if (mousepos.y >= 200 && mousepos.y <= 275){
                button2.setTexture(&button2H);
                if (!fxtime) {
                    buttonSound.play();
                    fxtime = true;
                }
            } else if (mousepos.y >= 300 && mousepos.y <= 375){
                button3.setTexture(&button3H);
                if (!fxtime) {
                    buttonSound.play();
                    fxtime = true;
                }
            } else {
                button1.setTexture(&button1NH);
                button2.setTexture(&button2NH);
                button3.setTexture(&button3NH);
                fxtime = false;
            }
        } else {
                button1.setTexture(&button1NH);
                button2.setTexture(&button2NH);
                button3.setTexture(&button3NH);
                fxtime = false;
        }
        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (mousepos.x > 250 && mousepos.x < 550) {
                        if (mousepos.y > 100 && mousepos.y < 180){
                            music.stop();
                            int a = game.Run();
                            deathsound.play();
                            music.play();
                            if (a==0 || a==1) {
                                game.setScore(a,game.getScore(a)+1+1*1);
                                if (game.getScore(1) == 10) score2.setPosition(700,25);
                                std::cout << "player " << a+1 << " won" << std::endl;
                            }
                        }
                        else if (mousepos.y >= 200 && mousepos.y <= 280){
                            game.setScore(0,0);
                            game.setScore(1,0);
                        }
                        else if (mousepos.y >= 300 && mousepos.y <= 380){
                            window.close();
                        }
                    }
                }
            }
            
        }
        
        
        window.clear();
        
        window.draw(background);
        window.draw(button1);
        window.draw(button2);
        window.draw(button3);
        window.draw(score1);
        window.draw(score2);
     

        window.display();
    
    }
    return -1;
}