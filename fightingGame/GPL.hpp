#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Champion.hpp"

class GPL{
private:
	sf::Music mGPL;
	int skillNumber;										// 현재 사용하는 스킬의 번호
	int skillFrame[4];										// 스킬이 몇개의 동작으로 이루어 졌는지 
public:
	GPL(){  
		canUseSkillCount[0] = 9999;								// Champion class 상속
		canUseSkillCount[1] = 3;
		canUseSkillCount[2] = 2;
		canUseSkillCount[3] = 1;
		skillFrame[0] = 12;
		skillFrame[1] = 12;
		skillFrame[2] = 24;
		skillFrame[3] = 24;
		skillNumber = 0;
	}
	~GPL();

	int canUseSkillCount[4];											// 스킬 사용 횟수
	void useSkill(int skillnumber, int frameCount, class Champion &c);		// 스킬을 사용하면 사용하는 함수
	void updateAOList(class Champion& c);										// attackObject를 상대가 맞았거나 화면 밖으로 나갔을 때 check를 true로 바꿔주고
																		// 투사체의 포지션을 업데이트 해줌
	void detectCollision(class Champion &c, std::list<struct AttackObject*> &aoList, float &enemyFrameCount);			// 내 attackObject 리스트에 상대 정보를 비교하여 맞으면 효과가 발동 하도록하는 함수

	void setSkillNumber(int skillNumber);								// 스킬번호 설정 함수
	int getSkillNumber();												// 스킬번호 반환 함수
	int getCanUseSkillCount(int skillNumber);							// 스킬 필요한 마나 반환 함수
	int getSkillFrameTotal();											// 스킬에 사용되는 총 프레임 반환
	////////////////////////////////////////////////////////// GPL skill begin
	void skill_NormalAttack(int frameCount, class Champion &c);				// 기본 공격 (넉백)
	void skill_FinalAttack(int frameCount, class Champion &c);				// 최후의 공격 (무지아픔) - 범위는 적은데 매우 아픔 (넉백)
	void skill_WindofSword(int frameCount, class Champion &c);				// 바람의 상처 (지속딜) - 상대 스턴 (한번 맞으면 골로가는거임)
	void skill_Ogonpogotovnosti(int frameCount, class Champion &c);			// 자이라궁 - 상대 스턴에 맵 중앙으로 모음 (이거 발동되면 끝났다고 보면 됨)
	////////////////////////////////////////////////////////// GPL skill end

	////////////////////////////////////////////////////////// GPL hit begin
	void hit_KnockBack(int frameCount, class Champion &c);					// 넉백
	void hit_stun(int frameCount, class Champion &c);							// 스턴
	////////////////////////////////////////////////////////// GPL hit end

	////////////////////////////////////////////////////////// load Motion begin
	void loadCharacter(sf::Sprite&, class Champion &c);
    void calculateSpritePos(class Champion &c);
	void calculateSpriteBlock(class Champion &c);

	void calculateSpriteNormalAttack(int frameCount, class Champion &c);		// 각각 스프라이트 좌표 찍어 주는 함수
    void calculateSpriteFinalAttack(int frameCount, class Champion &c);
    void calculateSpriteWindofSword(int frameCount, class Champion &c);
    void calculateSpriteOgonpogotovnosti(int frameCount, class Champion &c);
	void calculateSpriteStun(int frameCount, class Champion &c);
	void calculateSpriteKnockBack(int frameCount, class Champion &c);
	////////////////////////////////////////////////////////// load Motion end

};
