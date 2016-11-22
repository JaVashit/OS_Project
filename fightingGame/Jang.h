#include <SFML/Graphics.hpp>
#include <list>
#include "Champion.hpp"

class Jang : public Champion{
private:
	int skillNumber;		// ���� ����ϴ� ��ų�� ��ȣ
	int skillFrame[5];		// ��ų ��������Ʈ Ƚ��
	bool bSkill[3];			// ��ų ��� Ƚ�� ����

public:
	
	Jang(int p, int m_number, int width, int height) : Champion(p, m_number,width, height){  
		skillFrame[0] = 6;	// �Ϲ� ����
		skillFrame[1] = 14; // Ư�� ���� '1'
		skillFrame[2] = 22; // Ư�� ���� '2'
		skillFrame[3] = 60;	// Ư�� ���� '3'
		skillFrame[4] = 0;	// ��� ���� ����
		skillNumber = 0;
		attackObjList.clear();
		for(int i=0;i<2;i++)	// ��ų Ƚ�� �ʱ�ȭ
			bSkill[i] = true;	// bSkill[2]: Ư�� ��� '3'(��)�� ������ ������ �� true �ʱ�ȭ
	};
	~Jang();
	
	void useSkill(int skillnumber, int frameCount);				// ��ų ��� �� ��ų ��ȣ �Ѱ��ִ� �Լ�
	void crowdControlHit(float &frameCount);					// ���� ���� �� ȿ�� ������ �󸶳� �Ǹ�, �� ������ ������ ���°� ���ϴ� �� ����
	void insertAOList(int skillNumber);							// ���ݿ� ���� �⺻ ������ ����Ʈ
	void deleteAOList();										// ����Ʈ�� ��� ������Ʈ ���ִ� �Լ�
	void updateAOList();										// ����Ʈ�� ��� ������Ʈ ���ִ� �Լ� - ����ü�� �������� ������Ʈ
	void detectCollision(Champion &c, float &enemyFrameCount);	// �浹ó��
	std::list <AttackObject*> attackObjList;					// ��ų�� ����ϸ� ���� ������Ʈ ����

	void setSkillNumber(int skillNumber);						// ��ų��ȣ ���� �Լ�
	int getSkillNumber();										// ��ų��ȣ ��ȯ �Լ�
	int getSkillFrameTotal();									// ��ų�� ���Ǵ� �� ������ ��ȯ
	
	////////////////////////////////////////////////////////// Jang skill begin
	void skill_NormalAttack(int frameCount);					// �⺻ ���� (�˹�)
	void skill_RotateKick(int frameCount);						// Ư�� ���� '1' - B ��������
	void skill_doubleComboAttack(int frameCount);				// Ư�� ���� '2' - �߰����� C �÷�ġ��, �⸻���� F ������
	void skill_SpecialAttack(int frameCount);					// Ư�� ���� '3' - ��� �� ���� F������ ��
	void skill_Dash(int frameCount);							// ���� ����
	////////////////////////////////////////////////////////// Jang skill end

	////////////////////////////////////////////////////////// Jang hit begin
	void hit_KnockBack(int frameCount);							// �˹�
	void hit_stun(int frameCount);								// ����
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
