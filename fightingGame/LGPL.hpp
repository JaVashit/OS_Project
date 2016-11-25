#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Champion.hpp"

class LGPL{
private:
	int skillNumber;										// 현재 사용하는 스킬의 번호
	int skillFrame[5];										// 스킬이 몇개의 동작으로 이루어 졌는지 
public:

	LGPL(){
		canUseSkillCount[0] = 9999;								// Champion class 상속
		canUseSkillCount[1] = 3;
		canUseSkillCount[2] = 2;
		canUseSkillCount[3] = 1;
		skillFrame[0] = 5;
		skillFrame[1] = 13;
		skillFrame[2] = 5;
		skillFrame[3] = 13;
		skillNumber = 0;
	};
	~LGPL();

	int canUseSkillCount[4];
	void useSkill(int skillnumber, int frameCount, class Champion &c);				// 스킬을 사용하면 사용하는 함수
	void updateAOList(class Champion &c);										// attackObject를 상대가 맞았거나 화면 밖으로 나갔을 때 check를 true로 바꿔주고
																// 투사체의 포지션을 업데이트 해줌
	void detectCollision(class Champion &c, std::list<struct AttackObject*> &aoList, float &enemyFrameCount);	// 내 attackObject 리스트에 상대 정보를 비교하여 맞으면 효과가 발동 하도록하는 함수

	void setSkillNumber(int skillNumber);						// 스킬번호 설정 함수
	int getSkillNumber();										// 스킬번호 반환 함수
	int getCanUseSkillCount(int skillNumber);						// 스킬 필요한 마나 반환 함수
	void setCanUseSkillCount(int skillNumber, int maxCount);
	int getSkillFrameTotal();									// 스킬에 사용되는 총 프레임 반환

																////////////////////////////////////////////////////////// LGPL skill begin
	void skill_NormalAttack(int frameCount, class Champion &c);					// 기본 공격 (근거리, 넉백) - 밀쳐내기용 스킬
	void skill_Boombaya(int frameCount, class Champion &c);						// 에너지 발사 공격 (투사체)
	void skill_Magnetic(int frameCount, class Champion &c);						// LGPL 머리 공격 (느린 투사체, 다중 HIT, 넉백)
	void skill_ResserBim(int frameCount, class Champion &c);						// LGPL 펀치 공격 (넓은 범위, 4회 HIT 후 넉백)
																////////////////////////////////////////////////////////// LGPL skill end

																////////////////////////////////////////////////////////// LGPL hit begin
	void hit_KnockBack(int frameCount,  class Champion &c);							// 넉백
	void hit_stun(int frameCount, class Champion &c);								// 스턴
																////////////////////////////////////////////////////////// LGPL hit end

																////////////////////////////////////////////////////////// load Motion begin
	void loadCharacter(sf::Sprite&, class Champion &c);
	void calculateSpritePos(class Champion &c);
	void calculateSpriteBlock(class Champion &c);

	void calculateSpriteNormalAttack(int frameCount, class Champion &c);			// 각각 스프라이트 좌표 찍어 주는 함수
	void calculateSpriteBoombaya(int frameCount, class Champion &c);
	void calculateSpriteResserBim(int frameCount, class Champion &c);
	void calculateSpriteMagnetic(int frameCount, class Champion &c);
	void calculateSpriteStun(int frameCount, class Champion &c);
	void calculateSpriteKnockBack(int frameCount, class Champion &c);
	////////////////////////////////////////////////////////// load Motion end
};
