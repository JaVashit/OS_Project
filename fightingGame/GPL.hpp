#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Champion.hpp"

class GPL : public Champion{
private:
	int necessaryMana[5];									// ��ų�� �ʿ��� ���� 
	int skillNumber;										// ���� ����ϴ� ��ų�� ��ȣ
	int skillFrame[5];										// ��ų�� ��� �������� �̷�� ������ 
	int playerNumber;
public:
	
	GPL(int p, int m_number, int width, int height) : Champion(p, m_number,width, height){  
		necessaryMana[0] = 0;								// Champion class ���
		necessaryMana[1] = 0;
		necessaryMana[2] = 0;
		necessaryMana[3] = 0;
		necessaryMana[4] = 0;
		skillFrame[0] = 12;
		skillFrame[1] = 12;
		skillFrame[2] = 24;
		skillFrame[3] = 24;
		skillFrame[4] = 0;
		skillNumber = 0;
		playerNumber = p;
		attackObjList.clear();
	};
	~GPL();

	
	void useSkill(int skillnumber, int frameCount);				// ��ų�� ����ϸ� ����ϴ� �Լ�
	void crowdControlHit(float &frameCount);					// �����̳� �˹��� ���������� üũ�ؼ� ȿ���� �ߵ��ϴ� �Լ�
	void insertAOList(int skillNumber);							// ������ ���� ��, attackObject�� �����ϴ� �Լ� (�̰Ŵ� �� ĳ������ ��ų���� �������־�� ��)
	void deleteAOList();										// attackObject�� check�� true �ΰ͵��� ����� �Լ�
	void updateAOList();										// attackObject�� ��밡 �¾Ұų� ȭ�� ������ ������ �� check�� true�� �ٲ��ְ�
																// ����ü�� �������� ������Ʈ ����
	void detectCollision(Champion &c, float &enemyFrameCount);	// �� attackObject ����Ʈ�� ��� ������ ���Ͽ� ������ ȿ���� �ߵ� �ϵ����ϴ� �Լ�
	std::list <AttackObject*> attackObjList;					// ��ų�� ����ϸ� ���� ������Ʈ ����

	void setSkillNumber(int skillNumber);						// ��ų��ȣ ���� �Լ�
	int getSkillNumber();										// ��ų��ȣ ��ȯ �Լ�
	int getNecessaryMana(int skillNumber);						// ��ų �ʿ��� ���� ��ȯ �Լ�
	int getSkillFrameTotal();									// ��ų�� ���Ǵ� �� ������ ��ȯ
	
	////////////////////////////////////////////////////////// GPL skill begin
	void skill_NormalAttack(int frameCount);					// �⺻ ���� (�˹�)
	void skill_FinalAttack(int frameCount);						// ������ ���� (��������) - ������ ������ �ſ� ���� (�˹�)
	void skill_WindofSword(int frameCount);						// �ٶ��� ��ó (���ӵ�) - ��� ���� (�ѹ� ������ ��ΰ��°���)
	void skill_Ogonpogotovnosti(int frameCount);				// ���̶�� - ��� ���Ͽ� �� �߾����� ���� (�̰� �ߵ��Ǹ� �����ٰ� ���� ��)
	void skill_Dash(int frameCount);							// ���� ����
	////////////////////////////////////////////////////////// GPL skill end

	////////////////////////////////////////////////////////// GPL hit begin
	void hit_KnockBack(int frameCount);							// �˹�
	void hit_stun(int frameCount);								// ����
	////////////////////////////////////////////////////////// GPL hit end

	////////////////////////////////////////////////////////// load Motion begin
	void loadCharacter(sf::Sprite&);
    void calculateSpritePos(int step);
    void calculateSpriteBlock();

	void calculateSpriteNormalAttack(int frameCount);			// ���� ��������Ʈ ��ǥ ��� �ִ� �Լ�
    void calculateSpriteFinalAttack(int frameCount);
    void calculateSpriteWindofSword(int frameCount);
    void calculateSpriteOgonpogotovnosti(int frameCount);
    void calculateSpriteDash(int frameCount);
	void calculateSpriteStun(int frameCount);
	void calculateSpriteKnockBack(int frameCount);
	////////////////////////////////////////////////////////// load Motion end

	void resetGame(){
	}
};
