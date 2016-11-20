#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

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

class Champion{
private:
	sf::Vector2 <float> pos;
	sf::Vector2 <float> spr;
	int facing;
	int player;
	float speed;
	float ax;
	float ay;

	float hp;
	int mp;

	bool attack;
	bool barrier;
	bool grounded;
	bool dash;

	int modelNumber;
	int winScore;

public:
	int w_Width;											// ȭ�� ���� ũ��
	int w_Height;											// ȭ�� ���� ũ��

	Champion(int p, int m_number, int width, int height);	
	~Champion();
	
	bool selectSkin;
	bool isStun;											// �����̳�
	bool isKnockBack;										// �˹��̳�
	float vx;												// x�� �ӵ�
	float vy;												// y�� �ӵ� (��� �̰ŵ� private�� �־�� �ϴµ� �ٸ��ֵ��� �ǵ���� �Ǽ� �����Ƽ� �� ��)
		
	void setHp(float);										// hp���� ��ȯ
	float getHp();

	void setMp(int);										// mp���� ��ȯ
	int getMp();

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
	void setSpeed(float);
	void playerWin();

	void drawChampion();

	void loadCharacter(sf::Sprite&, int);					// �̰� �����δ� ���� ���� (�� ĳ���Ϳ� �־�������)
    void calculateSpritePos(int, int);
    void calculateSpritePunch(int);
    void calculateSpriteBlock(int);
    void nextSkin();

};