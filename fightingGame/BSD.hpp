#include <SFML/Graphics.hpp>
#include <list>
#include "Champion.hpp"

class BSD : public Champion {
private:
	int necessaryMana[5];									// ��ų�� �ʿ��� ���� 
	int skillNumber;										// ���� ����ϴ� ��ų�� ��ȣ
	int skillFrame[5];										// ��ų�� ��� �������� �̷�� ������ 
public:

	BSD(int p, int m_number, int width, int height) : Champion(p, m_number, width, height) {
		necessaryMana[0] = 0;								// Champion class ���
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

																////////////////////////////////////////////////////////// BSD skill begin
	void skill_NormalAttack(int frameCount);					// �⺻ ���� (�ٰŸ�, �˹�) - ���ĳ���� ��ų
	void skill_EnergyAttack(int frameCount);					// ������ �߻� ���� (����ü)
	void skill_BSDHead(int frameCount);							// BSD �Ӹ� ���� (���� ����ü, ���� HIT, �˹�)
	void skill_BSDPunch(int frameCount);						// BSD ��ġ ���� (���� ����, 4ȸ HIT �� �˹�)
	void skill_Dash(int frameCount);							// ���� ����
																////////////////////////////////////////////////////////// BSD skill end

																////////////////////////////////////////////////////////// BSD hit begin
	void hit_KnockBack(int frameCount);							// �˹�
	void hit_stun(int frameCount);								// ����
																////////////////////////////////////////////////////////// BSD hit end

																////////////////////////////////////////////////////////// load Motion begin
	void loadCharacter(sf::Sprite&);
	void calculateSpritePos(int step);
	void calculateSpriteBlock();

	void calculateSpriteNormalAttack(int frameCount);			// ���� ��������Ʈ ��ǥ ��� �ִ� �Լ�
	void calculateSpriteEnergyAttack(int frameCount);
	void calculateSpriteBSDHead(int frameCount);
	void calculateSpriteBSDPunch(int frameCount);
	void calculateSpriteDash(int frameCount);
	void calculateSpriteStun(int frameCount);
	void calculateSpriteKnockBack(int frameCount);
	////////////////////////////////////////////////////////// load Motion end
};
