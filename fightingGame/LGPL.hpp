#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Champion.hpp"

class LGPL{
private:
	int skillNumber;										// ���� ����ϴ� ��ų�� ��ȣ
	int skillFrame[5];										// ��ų�� ��� �������� �̷�� ������ 
public:

	LGPL(){
		canUseSkillCount[0] = 9999;								// Champion class ���
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
	void useSkill(int skillnumber, int frameCount, class Champion &c);				// ��ų�� ����ϸ� ����ϴ� �Լ�
	void updateAOList(class Champion &c);										// attackObject�� ��밡 �¾Ұų� ȭ�� ������ ������ �� check�� true�� �ٲ��ְ�
																// ����ü�� �������� ������Ʈ ����
	void detectCollision(class Champion &c, std::list<struct AttackObject*> &aoList, float &enemyFrameCount);	// �� attackObject ����Ʈ�� ��� ������ ���Ͽ� ������ ȿ���� �ߵ� �ϵ����ϴ� �Լ�

	void setSkillNumber(int skillNumber);						// ��ų��ȣ ���� �Լ�
	int getSkillNumber();										// ��ų��ȣ ��ȯ �Լ�
	int getCanUseSkillCount(int skillNumber);						// ��ų �ʿ��� ���� ��ȯ �Լ�
	void setCanUseSkillCount(int skillNumber, int maxCount);
	int getSkillFrameTotal();									// ��ų�� ���Ǵ� �� ������ ��ȯ

																////////////////////////////////////////////////////////// LGPL skill begin
	void skill_NormalAttack(int frameCount, class Champion &c);					// �⺻ ���� (�ٰŸ�, �˹�) - ���ĳ���� ��ų
	void skill_Boombaya(int frameCount, class Champion &c);						// ������ �߻� ���� (����ü)
	void skill_Magnetic(int frameCount, class Champion &c);						// LGPL �Ӹ� ���� (���� ����ü, ���� HIT, �˹�)
	void skill_ResserBim(int frameCount, class Champion &c);						// LGPL ��ġ ���� (���� ����, 4ȸ HIT �� �˹�)
																////////////////////////////////////////////////////////// LGPL skill end

																////////////////////////////////////////////////////////// LGPL hit begin
	void hit_KnockBack(int frameCount,  class Champion &c);							// �˹�
	void hit_stun(int frameCount, class Champion &c);								// ����
																////////////////////////////////////////////////////////// LGPL hit end

																////////////////////////////////////////////////////////// load Motion begin
	void loadCharacter(sf::Sprite&, class Champion &c);
	void calculateSpritePos(class Champion &c);
	void calculateSpriteBlock(class Champion &c);

	void calculateSpriteNormalAttack(int frameCount, class Champion &c);			// ���� ��������Ʈ ��ǥ ��� �ִ� �Լ�
	void calculateSpriteBoombaya(int frameCount, class Champion &c);
	void calculateSpriteResserBim(int frameCount, class Champion &c);
	void calculateSpriteMagnetic(int frameCount, class Champion &c);
	void calculateSpriteStun(int frameCount, class Champion &c);
	void calculateSpriteKnockBack(int frameCount, class Champion &c);
	////////////////////////////////////////////////////////// load Motion end
};
