#include <SFML/Graphics.hpp>
#include <list>
#include "Champion.hpp"

class Jang : public Champion{
private:
	int skillNumber;		// 현재 사용하는 스킬의 번호
	int skillFrame[5];		// 스킬 스프라이트 횟수
	bool bSkill[3];			// 스킬 사용 횟수 제한

public:
	
	Jang(int p, int m_number, int width, int height) : Champion(p, m_number,width, height){  
		skillFrame[0] = 6;	// 일반 공격
		skillFrame[1] = 14; // 특수 공격 '1'
		skillFrame[2] = 22; // 특수 공격 '2'
		skillFrame[3] = 60;	// 특수 공격 '3'
		skillFrame[4] = 0;	// 대시 공격 없음
		skillNumber = 0;
		attackObjList.clear();
		for(int i=0;i<2;i++)	// 스킬 횟수 초기화
			bSkill[i] = true;	// bSkill[2]: 특수 기술 '3'(궁)은 게임을 시작할 때 true 초기화
	};
	~Jang();
	
	void useSkill(int skillnumber, int frameCount);				// 스킬 사용 시 스킬 번호 넘겨주는 함수
	void crowdControlHit(float &frameCount);					// 공격 판정 시 효과 지속이 얼마나 되며, 몇 프레임 단위로 상태가 변하는 지 결정
	void insertAOList(int skillNumber);							// 공격에 대한 기본 정보의 리스트
	void deleteAOList();										// 리스트를 계속 업데이트 해주는 함수
	void updateAOList();										// 리스트를 계속 업데이트 해주는 함수 - 투사체의 포지션을 업데이트
	void detectCollision(Champion &c, float &enemyFrameCount);	// 충돌처리
	std::list <AttackObject*> attackObjList;					// 스킬을 사용하면 공격 오브젝트 생성

	void setSkillNumber(int skillNumber);						// 스킬번호 설정 함수
	int getSkillNumber();										// 스킬번호 반환 함수
	int getSkillFrameTotal();									// 스킬에 사용되는 총 프레임 반환
	
	////////////////////////////////////////////////////////// Jang skill begin
	void skill_NormalAttack(int frameCount);					// 기본 공격 (넉백)
	void skill_RotateKick(int frameCount);						// 특수 공격 '1' - B 돌려차기
	void skill_doubleComboAttack(int frameCount);				// 특수 공격 '2' - 중간고사는 C 올려치기, 기말고사는 F 지르기
	void skill_SpecialAttack(int frameCount);					// 특수 공격 '3' - 벗어날 수 없는 F학점의 늪
	void skill_Dash(int frameCount);							// 아직 안함
	////////////////////////////////////////////////////////// Jang skill end

	////////////////////////////////////////////////////////// Jang hit begin
	void hit_KnockBack(int frameCount);							// 넉백
	void hit_stun(int frameCount);								// 스턴
	////////////////////////////////////////////////////////// Jang hit end

	////////////////////////////////////////////////////////// load Motion begin
	void loadCharacter(sf::Sprite&);
    void calculateSpritePos(int step);
    void calculateSpriteBlock();
	void calculateSpriteNormalAttack(int frameCount);			
    void calculateSpriteRotateKick(int frameCount);
    void calculateSpritedoubleComboAttack(int frameCount);
    void calculateSpriteSpecialAttack(int frameCount);
    void calculateSpriteDash(int frameCount);
	void calculateSpriteStun(int frameCount);
	void calculateSpriteKnockBack(int frameCount);
	////////////////////////////////////////////////////////// load Motion end
};
