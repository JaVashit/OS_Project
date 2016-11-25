#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Champion.hpp"

class Apache{
private:
	int skillNumber;
	int skillFrame[4];
public:
	Apache(){
		canUseSkillCount[0] = 9999;
		canUseSkillCount[1] = 5;
		canUseSkillCount[2] = 5;
		canUseSkillCount[3] = 5;
		skillFrame[0] = 12;
		skillFrame[1] = 12;
		skillFrame[2] = 12;
		skillFrame[3] = 12;
		skillNumber = 0;
	};

	~Apache();

	int canUseSkillCount[4];
	void useSkill(int skillnumber, int frameCount, class Champion &c);				// 스킬을 사용하면 사용하는 함수
	void updateAOList(Champion &c);										// attackObject를 상대가 맞았거나 화면 밖으로 나갔을 때 check를 true로 바꿔주고
																// 투사체의 포지션을 업데이트 해줌
	void detectCollision(class Champion &c, std::list<struct AttackObject*> &aoList, std::list<struct hitImage*> &hitList, float &enemyFrameCount, int time);	// 내 attackObject 리스트에 상대 정보를 비교하여 맞으면 효과가 발동 하도록하는 함수

	void setSkillNumber(int skillNumber);						// 스킬번호 설정 함수
	int getSkillNumber();										// 스킬번호 반환 함수
	int getCanUseSkillCount(int skillNumber);						// 스킬 필요한 마나 반환 함수
	void setCanUseSkillCount(int skillNumber, int maxCount);
	int getSkillFrameTotal();									// 스킬에 사용되는 총 프레임 반환
																////////////////////////////////////////////////////////// GPL skill begin
	void skill_NormalAttack(int frameCount, class Champion &c);					// 기본 공격 (넉백)
	void skill_SpinAttack(int frameCount, class Champion &c);						// 최후의 공격 (무지아픔) - 범위는 적은데 매우 아픔 (넉백)
	void skill_Teleport(int frameCount, class Champion &c);						// 바람의 상처 (지속딜) - 상대 스턴 (한번 맞으면 골로가는거임)
	void skill_Assassination(int frameCount, class Champion &c);				// 자이라궁 - 상대 스턴에 맵 중앙으로 모음 (이거 발동되면 끝났다고 보면 됨)
																////////////////////////////////////////////////////////// GPL skill end

																////////////////////////////////////////////////////////// GPL hit begin
	void hit_KnockBack(int frameCount, class Champion &c);							// 넉백
	void hit_stun(int frameCount, class Champion &c);								// 스턴
																////////////////////////////////////////////////////////// GPL hit end

																////////////////////////////////////////////////////////// load Motion begin
	void loadCharacter(sf::Sprite&, class Champion &c);
	void calculateSpritePos(class Champion &c);
	void calculateSpriteBlock(class Champion &c);

	void calculateSpriteNormalAttack(int frameCount, class Champion &c);			// 각각 스프라이트 좌표 찍어 주는 함수
	void calculateSpriteSpinAttack(int frameCount, class Champion &c);
	void calculateSpriteTeleport(int frameCount, class Champion &c);
	void calculateSpriteAssassination(int frameCount, class Champion &c);
	void calculateSpriteStun(int frameCount, class Champion &c);
	void calculateSpriteKnockBack(int frameCount, class Champion &c);
	////////////////////////////////////////////////////////// load Motion end
};
