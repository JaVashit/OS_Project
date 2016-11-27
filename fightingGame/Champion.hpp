#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "GPL.hpp"
#include "BSD.hpp"
#include "Apache.hpp"
#include "Jang.h"
#include "LGPL.hpp"

struct AttackObject{
	float damage;
	int skillNumber;				// ��ų��ȣ
	sf::Vector2f range_s;			// ������ ������ ���� ��ǥ
	sf::Vector2f range_e;			// ������ ������ �� ��ǥ
	sf::Vector2f direct;			// ����ü�� ���� ����
	sf::Vector2f enemyDirect;		// ���� �°� ���ư��� ����
	sf::Texture throwTexture;		// ����ü �ؽ���
	float frameCount;

	bool isthrow;					// ����ü����?
	sf::Sprite obj;					// ����ü �׸�
	sf::Vector2f objSpr;			// ����ü �׸� �ҷ��ö� ��ǥ
	float speed;					// ����ü ���ǵ�
	bool check;						// ������ �¾Ұų� ȭ�鿡�� ����ų�, ���������ϰ�� ������ ������ �� üũ
	int hitcount;					// ����ü �� Ÿ�� Ƚ��
	AttackObject(int skillNumber, int damage, float speed){
		this->skillNumber = skillNumber;
		this->damage = damage;
		this->speed = speed;
		check = false;
		int hitcount = 0;
		frameCount = 0;
	}
};

struct hitImage{
	sf::Vector2f pos;
	float frameCount;
	sf::Texture hitTexture;
	sf::RectangleShape hit;
	hitImage(sf::Vector2f position){
		int random1 = rand()%50 - 25;
		int random2 = rand()%50 - 25;
		pos = sf::Vector2f(position.x-50+random1, position.y-50+random2);
		frameCount = 100;
		//hit = sf::RectangleShape(sf::Vector2f(50,50));
		//hit.setTexture(&hitTexture);
		//hit.setPosition(position);
	}
};

class Champion {
private:
	Champion *s_champion;
	sf::Vector2 <float> pos;
	sf::Vector2 <float> spr;
	int facing;
	int player;

	int max_SkillCount[4];

	float speed;
	float ax;
	float ay;

	float hp;

	bool attack;
	bool barrier;
	bool grounded;
	bool dash;

	int modelNumber;
	int winScore;
	int skillNumber;

public:
	
	int w_Width;											// ȭ�� ���� ũ��
	int w_Height;											// ȭ�� ���� ũ��
	class GPL		*gpl;
	class BSD		*bsd;
	class Apache	*apache;
	class Jang		*jang;
	class LGPL		*lgpl;
	Champion(int p, int m_number, int width, int height);	
	~Champion();
	
	bool selectSkin;
	bool isStun;											// �����̳�
	bool isKnockBack;										// �˹��̳�
	float vx;												// x�� �ӵ�
	float vy;												// y�� �ӵ� (��� �̰ŵ� private�� �־�� �ϴµ� �ٸ��ֵ��� �ǵ���� �Ǽ� �����Ƽ� �� ��)
		
	void setHp(float);										// hp���� ��ȯ
	float getHp();

	void setPosition(float, float);							// position���� ��ȯ
	sf::Vector2<float> getPosition();
	void setSpr(float, float);								// sprite���� ��ȯ
	sf::Vector2<float> getSpr();

	void move(float left, float right, float jump);			// ������ �Լ�	
	void caculatePosXY();									// x,y�� �ӵ��� ���ӵ��� �̿��� ��ǥ�� ������Ʈ��

	void setAttack(bool attacking);							// attack barrier ground facing, dash, speed ���� �� ��ȯ
	void setBarrier(bool barriering);
	void setGrounded(bool grounded);
	void setFacing(int facing);
	void setDash(bool);
	bool isDash();
	bool isAttacking();
	bool isBarrier();
	bool isGrounded();
	bool isDeath();
	bool getFacing();
	float getSpeed();
	int getWinScore();
	void setSpeed(float);
	void playerWin();
	int getModelNumber();
	int getMaxCanUseSkillCount(int skillNumber);

	void crowdControlHit(float &frameCount);

	std::list <AttackObject*> attackObjList;					// ��ų�� ����ϸ� ���� ������Ʈ ����
	std::list <hitImage*> hitList;
	void insertAOList(int skillNumber);							// ������ ���� ��, attackObject�� �����ϴ� �Լ� (�̰Ŵ� �� ĳ������ ��ų���� �������־�� ��)
	void updateAOList();
	void useSkill(int frameCount);
	void deleteAOList();

	void loadCharacter(sf::Sprite&);
    void calculateSpritePos();
    void calculateSpriteBlock();
	int getCanUseSkillCount(int skillNumber);
	void setCanUseSkillCount();
	void setSkillNumber(int skillNumber);
	int getSkillFrameTotal();
	void detectCollision(Champion& champion, float &enemyFrameCount, int time);
};