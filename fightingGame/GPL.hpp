#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Champion.hpp"

class GPL{
private:
	sf::Music mGPL;
	int skillNumber;										// ���� ����ϴ� ��ų�� ��ȣ
	int skillFrame[4];										// ��ų�� ��� �������� �̷�� ������ 
public:
	GPL(){  
		canUseSkillCount[0] = 9999;								// Champion class ���
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

	int canUseSkillCount[4];											// ��ų ��� Ƚ��
	void useSkill(int skillnumber, int frameCount, class Champion &c);		// ��ų�� ����ϸ� ����ϴ� �Լ�
	void updateAOList(class Champion& c);										// attackObject�� ��밡 �¾Ұų� ȭ�� ������ ������ �� check�� true�� �ٲ��ְ�
																		// ����ü�� �������� ������Ʈ ����
	void detectCollision(class Champion &c, std::list<struct AttackObject*> &aoList, float &enemyFrameCount);			// �� attackObject ����Ʈ�� ��� ������ ���Ͽ� ������ ȿ���� �ߵ� �ϵ����ϴ� �Լ�

	void setSkillNumber(int skillNumber);								// ��ų��ȣ ���� �Լ�
	int getSkillNumber();												// ��ų��ȣ ��ȯ �Լ�
	int getCanUseSkillCount(int skillNumber);							// ��ų �ʿ��� ���� ��ȯ �Լ�
	int getSkillFrameTotal();											// ��ų�� ���Ǵ� �� ������ ��ȯ
	////////////////////////////////////////////////////////// GPL skill begin
	void skill_NormalAttack(int frameCount, class Champion &c);				// �⺻ ���� (�˹�)
	void skill_FinalAttack(int frameCount, class Champion &c);				// ������ ���� (��������) - ������ ������ �ſ� ���� (�˹�)
	void skill_WindofSword(int frameCount, class Champion &c);				// �ٶ��� ��ó (���ӵ�) - ��� ���� (�ѹ� ������ ��ΰ��°���)
	void skill_Ogonpogotovnosti(int frameCount, class Champion &c);			// ���̶�� - ��� ���Ͽ� �� �߾����� ���� (�̰� �ߵ��Ǹ� �����ٰ� ���� ��)
	////////////////////////////////////////////////////////// GPL skill end

	////////////////////////////////////////////////////////// GPL hit begin
	void hit_KnockBack(int frameCount, class Champion &c);					// �˹�
	void hit_stun(int frameCount, class Champion &c);							// ����
	////////////////////////////////////////////////////////// GPL hit end

	////////////////////////////////////////////////////////// load Motion begin
	void loadCharacter(sf::Sprite&, class Champion &c);
    void calculateSpritePos(class Champion &c);
	void calculateSpriteBlock(class Champion &c);

	void calculateSpriteNormalAttack(int frameCount, class Champion &c);		// ���� ��������Ʈ ��ǥ ��� �ִ� �Լ�
    void calculateSpriteFinalAttack(int frameCount, class Champion &c);
    void calculateSpriteWindofSword(int frameCount, class Champion &c);
    void calculateSpriteOgonpogotovnosti(int frameCount, class Champion &c);
	void calculateSpriteStun(int frameCount, class Champion &c);
	void calculateSpriteKnockBack(int frameCount, class Champion &c);
	////////////////////////////////////////////////////////// load Motion end

};
