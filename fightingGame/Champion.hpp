#pragma once
#include <SFML/Graphics.hpp>
#include <vector>


class Champion{
private:
	sf::Vector2 <float> pos;
	sf::Vector2 <float> spr;
	int facing;
	int player;
	float speed;
	float ay;
	float vy;

	int hp;
	int mp;

	bool attack;
	bool barrier;
	bool grounded;
	bool dash;

	int modelNumber;

public:
	int w_Width;
	int w_Height;

	Champion(int p, int m_number, int width, int height);
	~Champion();
	
	bool selectSkin;
	bool isStun;

	void setHp(int);
	int getHp();

	void setMp(int);
	int getMp();

	void setPosition(float, float);
	sf::Vector2<float> getPosition();
	void setSpr(float, float);
	sf::Vector2<float> getSpr();

	void move(float left, float right, float jump);
	void caculatePosY();

	void setAttack(bool attacking);
	void setBarrier(bool barriering);
	void setGrounded(bool grounded);
	void setFacing(int facing);
	void setDash(bool);
	bool isDash();
	bool isAttacking();
	bool isBarrier();
	bool isGrounded();
	bool isDeath();
	float getSpeed();
	void setSpeed(float);

	

	void drawChampion();

	void loadCharacter(sf::Sprite&, int);
    void calculateSpritePos(int, int);
    void calculateSpritePunch(int);
    void calculateSpriteBlock(int);
    void nextSkin();

};