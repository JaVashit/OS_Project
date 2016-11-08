#include <SFML/Graphics.hpp>
#include <vector>


class Champion{
private:
	sf::Vector2 <float> pos;
	sf::Vector2 <float> spr;
	bool facing;
	int player;
	float speed;

	int hp;
	int mp;

	bool attack;
	bool barrier;
	bool grounded;

	int modelNumber;

public:
	Champion(int p, int m_number);
	~Champion();
	
	bool selectSkin;

	void setHp(int);
	int getHp();

	void setMp(int);
	int getMp();

	void setPosition(float, float);
	sf::Vector2<float> getPosition();
	
	void setAttack(bool);
	void setBarrier(bool);
	void setGrounded(bool);
	bool isAttacking();
	bool isBarrier();
	bool isGrounded();
	bool isDeath();
	float getSpeed();
	void setSpeed(float);

	void drawChampion();

	void loadCharacter(sf::Sprite&);
    void calculateSpritePos(int);
    void calculateSpritePunch();
    void calculateSpriteBlock();
    void nextSkin();

};