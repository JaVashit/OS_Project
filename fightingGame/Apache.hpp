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
	void useSkill(int skillnumber, int frameCount, class Champion &c);				// ��ų�� ����ϸ� ����ϴ� �Լ�
	void updateAOList(Champion &c);										// attackObject�� ��밡 �¾Ұų� ȭ�� ������ ������ �� check�� true�� �ٲ��ְ�
																// ����ü�� �������� ������Ʈ ����
	void detectCollision(class Champion &c, std::list<struct AttackObject*> &aoList, std::list<struct hitImage*> &hitList, float &enemyFrameCount, int time);	// �� attackObject ����Ʈ�� ��� ������ ���Ͽ� ������ ȿ���� �ߵ� �ϵ����ϴ� �Լ�

	void setSkillNumber(int skillNumber);						// ��ų��ȣ ���� �Լ�
	int getSkillNumber();										// ��ų��ȣ ��ȯ �Լ�
	int getCanUseSkillCount(int skillNumber);						// ��ų �ʿ��� ���� ��ȯ �Լ�
	void setCanUseSkillCount(int skillNumber, int maxCount);
	int getSkillFrameTotal();									// ��ų�� ���Ǵ� �� ������ ��ȯ
																////////////////////////////////////////////////////////// GPL skill begin
	void skill_NormalAttack(int frameCount, class Champion &c);					// �⺻ ���� (�˹�)
	void skill_SpinAttack(int frameCount, class Champion &c);						// ������ ���� (��������) - ������ ������ �ſ� ���� (�˹�)
	void skill_Teleport(int frameCount, class Champion &c);						// �ٶ��� ��ó (���ӵ�) - ��� ���� (�ѹ� ������ ��ΰ��°���)
	void skill_Assassination(int frameCount, class Champion &c);				// ���̶�� - ��� ���Ͽ� �� �߾����� ���� (�̰� �ߵ��Ǹ� �����ٰ� ���� ��)
																////////////////////////////////////////////////////////// GPL skill end

																////////////////////////////////////////////////////////// GPL hit begin
	void hit_KnockBack(int frameCount, class Champion &c);							// �˹�
	void hit_stun(int frameCount, class Champion &c);								// ����
																////////////////////////////////////////////////////////// GPL hit end

																////////////////////////////////////////////////////////// load Motion begin
	void loadCharacter(sf::Sprite&, class Champion &c);
	void calculateSpritePos(class Champion &c);
	void calculateSpriteBlock(class Champion &c);

	void calculateSpriteNormalAttack(int frameCount, class Champion &c);			// ���� ��������Ʈ ��ǥ ��� �ִ� �Լ�
	void calculateSpriteSpinAttack(int frameCount, class Champion &c);
	void calculateSpriteTeleport(int frameCount, class Champion &c);
	void calculateSpriteAssassination(int frameCount, class Champion &c);
	void calculateSpriteStun(int frameCount, class Champion &c);
	void calculateSpriteKnockBack(int frameCount, class Champion &c);
	////////////////////////////////////////////////////////// load Motion end
};
