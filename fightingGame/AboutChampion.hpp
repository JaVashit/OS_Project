#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>

class AboutChampion
{
public:
	AboutChampion(sf::RenderWindow*window);

	sf::Music ac_Music;					// background music

	sf::Texture backgroundTexture;		// background image texture
	sf::RectangleShape background;		

	sf::Texture ac_Texture[4];			// explain champion image
	sf::Texture ac_postit[4];			// post it texture
	sf::RectangleShape ac_Rect[4];

	sf::Vector2f click_sPos[4];			// click start pos vector
	sf::Vector2f click_ePos[4];			// click end pos vector

	sf::Vector2i mousepos;				// mouse position

	void updateMouseOn(sf::Vector2i mousepos);	// update mouse pos and  boolean mouseOn
	void setColor();							// set color image
	void updateRectPos();						// update rectangle pos
	void setClick();							// mouse pressed setting object
	void run();									// running func

private:
	
	bool mouseOn[4];					// mouse on image
	bool clickOn[4];					// click image
	int spreadOn;						// spread image number
	int nextPageFrame;					// update frame number
	bool nextPage;						// next page opening
	sf::RenderWindow *_windows;
};