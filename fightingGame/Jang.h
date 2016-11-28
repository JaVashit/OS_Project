#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Champion.hpp"

class Jang{
private:
	sf::Music mJang;		// Jang에 관련된 사운드를 관리하는 변수
	int skillNumber;		// 현재 사용하는 스킬의 번호
	int skillFrame[4];		// 스킬 스프라이트 횟수

public:
	
	Jang(){  

		skillFrame[0] = 6;	// 일반 공격
		skillFrame[1] = 14; // 특수 공격 '1'
		skillFrame[2] = 22; // 특수 공격 '2'
		skillFrame[3] = 60;	// 특수 공격 '3'
		canUseSkillCount[0] = 9999; // 일반 공격 횟수
		canUseSkillCount[1] = 3;	// 특수 공격 1 횟수 3회로 제한
		canUseSkillCount[2] = 2;	// 특수 공격 2 횟수 2회로 제한
		canUseSkillCount[3] = 1;	// 궁극기 횟수 1회로 제한
		skillNumber = 0;	// 어떤 스킬을 사용하는 지 알 수 있는 스킬 인덱스
	};
	~Jang();
	int canUseSkillCount[4];			// 스킬 사용 횟수 제한
	void useSkill(int skillnumber, int frameCount, class Champion &c);				// 스킬 사용 시 스킬 번호 넘겨주는 함수
	void updateAOList(class Champion &c, bool sound);								// 리스트를 계속 업데이트 해주는 함수 - 투사체의 포지션을 업데이트
	void detectCollision(class Champion &c, std::list<struct AttackObject*> &aoList, std::list<struct hitImage*> &hitList, float &enemyFrameCount, int time, bool sound);	// 충돌처리

	void setSkillNumber(int skillNumber);											// 스킬번호 설정 함수
	int getSkillNumber();															// 스킬번호 반환 함수
	int getSkillFrameTotal();														// 스킬에 사용되는 총 프레임 반환
	int getCanUseSkillCount(int skillNumber);
	void setCanUseSkillCount(int skillNumber, int maxCount);
	////////////////////////////////////////////////////////// Jang skill begin
	void skill_NormalAttack(int frameCount, class Champion &c);						// 기본 공격 (넉백)
	void skill_RotateKick(int frameCount, class Champion &c);						// 특수 공격 '1' - B 돌려차기
	void skill_doubleComboAttack(int frameCount, class Champion &c);				// 특수 공격 '2' - 중간고사는 C 올려치기, 기말고사는 F 지르기
	void skill_SpecialAttack(int frameCount, class Champion &c);					// 특수 공격 '3' - 벗어날 수 없는 F학점의 늪
	////////////////////////////////////////////////////////// Jang skill end

	////////////////////////////////////////////////////////// Jang hit begin
	void hit_KnockBack(int frameCount, class Champion &c);							// 넉백
	void hit_stun(int frameCount, class Champion &c);								// 스턴
	////////////////////////////////////////////////////////// Jang hit end

	////////////////////////////////////////////////////////// load Motion begin
	void loadCharacter(sf::Sprite&, class Champion &c);
    void calculateSpritePos(class Champion &c);
    void calculateSpriteBlock(class Champion &c);
	void calculateSpriteNormalAttack(int frameCount, class Champion &c);			
    void calculateSpriteRotateKick(int frameCount, class Champion &c);
    void calculateSpritedoubleComboAttack(int frameCount, class Champion &c);
    void calculateSpriteSpecialAttack(int frameCount, class Champion &c);
	void calculateSpriteStun(int frameCount, class Champion &c);
	void calculateSpriteKnockBack(int frameCount, class Champion &c);
	////////////////////////////////////////////////////////// load Motion end
};
