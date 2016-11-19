#include <SFML/Graphics.hpp>
#include <list>
#include "Champion.hpp"

class BSD : public Champion {
private:
	int necessaryMana[5];									// 스킬에 필요한 마나 
	int skillNumber;										// 현재 사용하는 스킬의 번호
	int skillFrame[5];										// 스킬이 몇개의 동작으로 이루어 졌는지 
public:

	BSD(int p, int m_number, int width, int height) : Champion(p, m_number, width, height) {
		necessaryMana[0] = 0;								// Champion class 상속
		necessaryMana[1] = 0;
		necessaryMana[2] = 0;
		necessaryMana[3] = 0;
		necessaryMana[4] = 0;
		skillFrame[0] = 13;
		skillFrame[1] = 13;
		skillFrame[2] = 13;
		skillFrame[3] = 13;
		skillFrame[4] = 0;
		skillNumber = 0;

		attackObjList.clear();
	};
	~BSD();


	void useSkill(int skillnumber, int frameCount);				// 스킬을 사용하면 사용하는 함수
	void crowdControlHit(float &frameCount);					// 스턴이나 넉백을 당했을때를 체크해서 효과를 발동하는 함수
	void insertAOList(int skillNumber);							// 공격을 했을 때, attackObject를 생성하는 함수 (이거는 각 캐릭터의 스킬마다 설정해주어야 함)
	void deleteAOList();										// attackObject의 check가 true 인것들을 지우는 함수
	void updateAOList();										// attackObject를 상대가 맞았거나 화면 밖으로 나갔을 때 check를 true로 바꿔주고
																// 투사체의 포지션을 업데이트 해줌
	void detectCollision(Champion &c, float &enemyFrameCount);	// 내 attackObject 리스트에 상대 정보를 비교하여 맞으면 효과가 발동 하도록하는 함수
	std::list <AttackObject*> attackObjList;					// 스킬을 사용하면 공격 오브젝트 생성

	void setSkillNumber(int skillNumber);						// 스킬번호 설정 함수
	int getSkillNumber();										// 스킬번호 반환 함수
	int getNecessaryMana(int skillNumber);						// 스킬 필요한 마나 반환 함수
	int getSkillFrameTotal();									// 스킬에 사용되는 총 프레임 반환

																////////////////////////////////////////////////////////// BSD skill begin
	void skill_NormalAttack(int frameCount);					// 기본 공격 (근거리, 넉백) - 밀쳐내기용 스킬
	void skill_EnergyAttack(int frameCount);					// 에너지 발사 공격 (투사체)
	void skill_BSDHead(int frameCount);							// BSD 머리 공격 (느린 투사체, 다중 HIT, 넉백)
	void skill_BSDPunch(int frameCount);						// BSD 펀치 공격 (넓은 범위, 4회 HIT 후 넉백)
	void skill_Dash(int frameCount);							// 아직 안함
																////////////////////////////////////////////////////////// BSD skill end

																////////////////////////////////////////////////////////// BSD hit begin
	void hit_KnockBack(int frameCount);							// 넉백
	void hit_stun(int frameCount);								// 스턴
																////////////////////////////////////////////////////////// BSD hit end

																////////////////////////////////////////////////////////// load Motion begin
	void loadCharacter(sf::Sprite&);
	void calculateSpritePos(int step);
	void calculateSpriteBlock();

	void calculateSpriteNormalAttack(int frameCount);			// 각각 스프라이트 좌표 찍어 주는 함수
	void calculateSpriteEnergyAttack(int frameCount);
	void calculateSpriteBSDHead(int frameCount);
	void calculateSpriteBSDPunch(int frameCount);
	void calculateSpriteDash(int frameCount);
	void calculateSpriteStun(int frameCount);
	void calculateSpriteKnockBack(int frameCount);
	////////////////////////////////////////////////////////// load Motion end
};
