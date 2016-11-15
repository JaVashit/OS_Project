#include <SFML/Graphics.hpp>
#include <list>
#include "Champion.hpp"

struct AttackObject{
	float damage;
	sf::Vector2f range_s;
	sf::Vector2f range_e;
	sf::Vector2f direct;
	float speed;
	bool check;
	AttackObject(int damage, sf::Vector2f range_s, sf::Vector2f range_e, sf::Vector2f direct, float speed){
		this->damage = damage;
		this->range_s = range_s;
		this->range_e = range_e;
		this->direct = direct;
		this->speed = speed;
		check = false;
	}
};

class GPL : public Champion{
private:
	int necessaryMana[5];									// 스킬에 필요한 마나 
	int skillNumber;										// 현재 사용하는 스킬의 번호
	int skillFrame[5];										// 스킬이 몇개의 동작으로 이루어 졌는지 
public:
	
	GPL(int p, int m_number, int width, int height) : Champion(p, m_number,width, height){  
		necessaryMana[0] = 0;								// Champion class 상속
		necessaryMana[1] = 0;
		necessaryMana[2] = 0;
		necessaryMana[3] = 0;
		necessaryMana[4] = 0;
		skillFrame[0] = 12;
		skillFrame[1] = 12;
		skillFrame[2] = 24;
		skillFrame[3] = 0;
		skillFrame[4] = 0;
		skillNumber = 0;
		attackObjList.clear();
	};
	~GPL();
	
	void useSkill(int skillnumber, int frameCount);			// 스킬을 사용하면 사용하는 함수

	std::list <AttackObject> attackObjList;					// 스킬을 사용하면 공격 오브젝트 생성

	void setSkillNumber(int skillNumber);					// 스킬번호 설정 함수
	int getSkillNumber();									// 스킬번호 반환 함수

	int getSkillFrameTotal();
	
	////////////////////////////////////////////////////////// GPL skill begin
	void skill_NormalAttack(int frameCount);
	void skill_FinalAttack(int frameCount);
	void skill_WindofSword(int frameCount);
	void skill_Ogonpogotovnosti(int frameCount);
	void skill_Dash(int frameCount);
	////////////////////////////////////////////////////////// GPL skill end

	////////////////////////////////////////////////////////// load Motion begin
	void loadCharacter(sf::Sprite&);
    void calculateSpritePos(int step);
    void calculateSpriteBlock();

	void calculateSpriteNormalAttack(int frameCount);
    void calculateSpriteFinalAttack(int frameCount);
    void calculateSpriteWindofSword(int frameCount);
    void calculateSpriteOgonpogotovnosti(int frameCount);
    void calculateSpriteDash(int frameCount);
	////////////////////////////////////////////////////////// load Motion end
};
