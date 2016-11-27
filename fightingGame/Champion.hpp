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
	int skillNumber;				// 스킬번호
	sf::Vector2f range_s;			// 데미지 영역의 시작 좌표
	sf::Vector2f range_e;			// 데미지 영역의 끝 좌표
	sf::Vector2f direct;			// 투사체의 방향 벡터
	sf::Vector2f enemyDirect;		// 적이 맞고 날아가는 벡터
	sf::Texture throwTexture;		// 투사체 텍스쳐
	float frameCount;

	bool isthrow;					// 투사체인지?
	sf::Sprite obj;					// 투사체 그림
	sf::Vector2f objSpr;			// 투사체 그림 불러올때 좌표
	float speed;					// 투사체 스피드
	bool check;						// 적에게 맞았거나 화면에서 벗어났거나, 근접공격일경우 공격이 끝났을 때 체크
	int hitcount;					// 투사체 적 타격 횟수
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
	
	int w_Width;											// 화면 가로 크기
	int w_Height;											// 화면 세로 크기
	class GPL		*gpl;
	class BSD		*bsd;
	class Apache	*apache;
	class Jang		*jang;
	class LGPL		*lgpl;
	Champion(int p, int m_number, int width, int height);	
	~Champion();
	
	bool selectSkin;
	bool isStun;											// 스턴이냐
	bool isKnockBack;										// 넉백이냐
	float vx;												// x축 속도
	float vy;												// y축 속도 (사실 이거도 private에 넣어야 하는데 다른애들이 건드려야 되서 귀찮아서 걍 뺌)
		
	void setHp(float);										// hp설정 반환
	float getHp();

	void setPosition(float, float);							// position설정 반환
	sf::Vector2<float> getPosition();
	void setSpr(float, float);								// sprite설정 반환
	sf::Vector2<float> getSpr();

	void move(float left, float right, float jump);			// 움직임 함수	
	void caculatePosXY();									// x,y를 속도와 가속도를 이용해 좌표를 업데이트함

	void setAttack(bool attacking);							// attack barrier ground facing, dash, speed 설정 및 반환
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

	std::list <AttackObject*> attackObjList;					// 스킬을 사용하면 공격 오브젝트 생성
	std::list <hitImage*> hitList;
	void insertAOList(int skillNumber);							// 공격을 했을 때, attackObject를 생성하는 함수 (이거는 각 캐릭터의 스킬마다 설정해주어야 함)
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