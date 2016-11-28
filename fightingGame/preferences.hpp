#ifndef PREFERENCES_H
#define PREFERENCES_H

class Preferences
{
public:
	Preferences(sf::RenderWindow *tywindow);
	bool keyboard(bool on);

private:
	int keyPos_x, keyPos_y;
	int _width;
	int _height;
	sf::RenderWindow *_tywindows;

};

#endif
