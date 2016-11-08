#ifndef GAME_H
#define GAME_H

class Game
{
public:
    Game(sf::RenderWindow* window);
    int Run();
    
    int setScore(bool,int);
    int getScore(bool);
    
private:
    int score1;
    int score2;
	int w_width;
	int w_height;
   
    float ay, damage, dmgred;
    sf::RenderWindow * _myWindow;
};
#endif

