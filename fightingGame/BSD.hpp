#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Champion.hpp"

class BSD{
private:
										// ��ų�� �ʿ��� ���� 
	int skillNumber;										// ���� ����ϴ� ��ų�� ��ȣ
	int skillFrame[4];										// ��ų�� ��� �������� �̷�� ������ 
public:

	BSD(){
		canUseSkillCount[0] = 9999;								// Champion class ���
		canUseSkillCount[1] = 3;
		canUseSkillCount[2] = 2;
		canUseSkillCount[3] = 1;
		skillFrame[0] = 13;
		skillFrame[1] = 13;
		skillFrame[2] = 13;
		skillFrame[3] = 13;
		skillNumber = 0;
	}
	~BSD();

	int canUseSkillCount[4];
	void useSkill(int skillnumber, int frameCount, class Champion &c);				// ��ų�� ����ϸ� ����ϴ� �Լ�
	void updateAOList(class Champion &c);										// attackObject�� ��밡 �¾Ұų� ȭ�� ������ ������ �� check�� true�� �ٲ��ְ�
																// ����ü�� �������� ������Ʈ ����
	void detectCollision(class Champion &c, std::list<struct AttackObject*> &aoList, std::list<struct hitImage*> &hitList, float &enemyFrameCount, int time);	// �� attackObject ����Ʈ�� ��� ������ ���Ͽ� ������ ȿ���� �ߵ� �ϵ����ϴ� �Լ�

	void setSkillNumber(int skillNumber);						// ��ų��ȣ ���� �Լ�
	int getSkillNumber();										// ��ų��ȣ ��ȯ �Լ�
	int getCanUseSkillCount(int skillNumber);						// ��ų �ʿ��� ���� ��ȯ �Լ�
	void setCanUseSkillCount(int skillNumber, int maxCount);
	int getSkillFrameTotal();									// ��ų�� ���Ǵ� �� ������ ��ȯ
																////////////////////////////////////////////////////////// BSD skill begin
	void skill_NormalAttack(int frameCount, class Champion &c);					// �⺻ ���� (�ٰŸ�, �˹�) - ���ĳ���� ��ų
	void skill_EnergyAttack(int frameCount, class Champion &c);					// ������ �߻� ���� (����ü)
	void skill_BSDHead(int frameCount, class Champion &c);							// BSD �Ӹ� ���� (���� ����ü, ���� HIT, �˹�)
	void skill_BSDPunch(int frameCount, class Champion &c);						// BSD ��ġ ���� (���� ����, 4ȸ HIT �� �˹�)
																////////////////////////////////////////////////////////// BSD skill end

																////////////////////////////////////////////////////////// BSD hit begin
	void hit_KnockBack(int frameCount, class Champion &c);							// �˹�
	void hit_stun(int frameCount, class Champion &c);								// ����
																////////////////////////////////////////////////////////// BSD hit end

																////////////////////////////////////////////////////////// load Motion begin
	void loadCharacter(sf::Sprite&, Champion &c);
	void calculateSpritePos(Champion &c);
	void calculateSpriteBlock(Champion &c);

	void calculateSpriteNormalAttack(int frameCount, Champion &c);			// ���� ��������Ʈ ��ǥ ��� �ִ� �Լ�
	void calculateSpriteEnergyAttack(int frameCount, Champion &c);
	void calculateSpriteBSDHead(int frameCount, Champion &c);
	void calculateSpriteBSDPunch(int frameCount, Champion &c);
	void calculateSpriteStun(int frameCount, Champion &c);
	void calculateSpriteKnockBack(int frameCount, Champion &c);
	////////////////////////////////////////////////////////// load Motion end
};
