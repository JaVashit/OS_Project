#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>

class AboutChampion
{
public:
	AboutChampion(sf::RenderWindow*window);

	sf::Music ac_Music;

	sf::Texture backgroundTexture;
	sf::RectangleShape background;

	sf::Texture ac_Texture[4];
	sf::RectangleShape ac_Rect[4];

	sf::Vector2f click_sPos[4];
	sf::Vector2f click_ePos[4];

	sf::Vector2i mousepos;

	void updateMouseOn(sf::Vector2i mousepos);
	void setColor();
	void updateRectPos();
	void setClick();
	void run();

private:
	
	bool mouseOn[4];
	bool clickOn[4];
	int spreadOn;
	int nextPageFrame;
	bool nextPage;
	sf::RenderWindow *_windows;
};