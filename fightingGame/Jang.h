#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Champion.hpp"

class Jang{
private:
	sf::Music mJang;		// Jang�� ���õ� ���带 �����ϴ� ����
	int skillNumber;		// ���� ����ϴ� ��ų�� ��ȣ
	int skillFrame[4];		// ��ų ��������Ʈ Ƚ��

public:
	
	Jang(){  

		skillFrame[0] = 6;	// �Ϲ� ����
		skillFrame[1] = 14; // Ư�� ���� '1'
		skillFrame[2] = 22; // Ư�� ���� '2'
		skillFrame[3] = 60;	// Ư�� ���� '3'
		canUseSkillCount[0] = 9999; // �Ϲ� ���� Ƚ��
		canUseSkillCount[1] = 3;	// Ư�� ���� 1 Ƚ�� 3ȸ�� ����
		canUseSkillCount[2] = 2;	// Ư�� ���� 2 Ƚ�� 2ȸ�� ����
		canUseSkillCount[3] = 1;	// �ñر� Ƚ�� 1ȸ�� ����
		skillNumber = 0;	// � ��ų�� ����ϴ� �� �� �� �ִ� ��ų �ε���
	};
	~Jang();
	int canUseSkillCount[4];			// ��ų ��� Ƚ�� ����
	void useSkill(int skillnumber, int frameCount, class Champion &c);				// ��ų ��� �� ��ų ��ȣ �Ѱ��ִ� �Լ�
	void updateAOList(class Champion &c, bool sound);								// ����Ʈ�� ��� ������Ʈ ���ִ� �Լ� - ����ü�� �������� ������Ʈ
	void detectCollision(class Champion &c, std::list<struct AttackObject*> &aoList, std::list<struct hitImage*> &hitList, float &enemyFrameCount, int time, bool sound);	// �浹ó��

	void setSkillNumber(int skillNumber);											// ��ų��ȣ ���� �Լ�
	int getSkillNumber();															// ��ų��ȣ ��ȯ �Լ�
	int getSkillFrameTotal();														// ��ų�� ���Ǵ� �� ������ ��ȯ
	int getCanUseSkillCount(int skillNumber);
	void setCanUseSkillCount(int skillNumber, int maxCount);
	////////////////////////////////////////////////////////// Jang skill begin
	void skill_NormalAttack(int frameCount, class Champion &c);						// �⺻ ���� (�˹�)
	void skill_RotateKick(int frameCount, class Champion &c);						// Ư�� ���� '1' - B ��������
	void skill_doubleComboAttack(int frameCount, class Champion &c);				// Ư�� ���� '2' - �߰����� C �÷�ġ��, �⸻���� F ������
	void skill_SpecialAttack(int frameCount, class Champion &c);					// Ư�� ���� '3' - ��� �� ���� F������ ��
	////////////////////////////////////////////////////////// Jang skill end

	////////////////////////////////////////////////////////// Jang hit begin
	void hit_KnockBack(int frameCount, class Champion &c);							// �˹�
	void hit_stun(int frameCount, class Champion &c);								// ����
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
