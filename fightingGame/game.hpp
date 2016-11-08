#ifndef GAME_H
#define GAME_H

class Game
{
public:
    Game(sf::RenderWindow* window);
    int Run();
    void Hell();
    int setScore(bool,int);
    int getScore(bool);
    
private:
    int score1;
    int score2;
	int w_width;
	int w_height;
    bool hell;
    float ay, damage, dmgred;
    sf::RenderWindow * _myWindow;
};
#endif

