#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Opening
{
public:
	Opening(sf::RenderWindow *window);
	sf::Texture backgroundTexture[4];
	sf::Texture titleTexture;
	sf::Texture BSD;
	sf::Texture GPL;
	sf::Texture APACHE;
	sf::Texture JANG;
	sf::Texture LGPL;
	sf::RectangleShape background[4];
	sf::RectangleShape title;
	sf::RectangleShape gpl_rect;
	sf::RectangleShape gpl_spr;
	sf::RectangleShape bsd_rect;
	sf::RectangleShape bsd_spr;
	sf::RectangleShape lgpl_rect;
	sf::RectangleShape lgpl_spr;
	sf::RectangleShape apa_rect;
	sf::RectangleShape apa_spr;

	void setOpeningObject();
	void updateChampionRect();
	void updateTitle(int frameCount);


private:
	sf::RenderWindow *_windows;

	float gpl_count;
	float bsd_count;
	float lgpl_count;
	float apa_count;
	float j_count;
	float final_count;
	int part2_frameCount;
	bool gpl_start;
	bool bsd_start;
	bool lgpl_start;
	bool apa_start;
	bool j_start;

	bool drawChampion;
};