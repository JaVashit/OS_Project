#include "BSD.hpp"

const int PIC_SIZE_X = 170;
const int PIC_SIZE_Y = 100;
const int ENERGY_SIZE_X = 85;
const int ENERGY_SIZE_Y = 40;

BSD::~BSD() { }

void BSD::useSkill(int skillnumber, int frameCount, Champion &c) { // ��ų �ߵ�
	if (skillnumber == 0) {
		skill_NormalAttack(frameCount, c);
	}
	else if (skillnumber == 1) {
		skill_EnergyAttack(frameCount, c);
	}
	else if (skillnumber == 2) {
		skill_BSDHead(frameCount, c);
	}
	else if (skillnumber == 3) {
		skill_BSDPunch(frameCount, c);
	}
}

void BSD::skill_NormalAttack(int frameCount, Champion &c) { // Ȥ�ó� �ٸ��� �Ұ� ������� ���� ����
	calculateSpriteNormalAttack(frameCount, c);
}

void BSD::skill_EnergyAttack(int frameCount, Champion &c) { // Ȥ�ó� �ٸ��� �Ұ� ������� ���� ����
	calculateSpriteEnergyAttack(frameCount, c);
}

void BSD::skill_BSDHead(int frameCount, Champion &c) {
	calculateSpriteBSDHead(frameCount, c);
}

void BSD::skill_BSDPunch(int frameCount, Champion &c) {
	calculateSpriteBSDPunch(frameCount, c);
}

void BSD::hit_KnockBack(int frameCount, Champion &c) {
	calculateSpriteKnockBack(frameCount, c);
}

void BSD::hit_stun(int frameCount, Champion &c) {
	calculateSpriteStun(frameCount, c);
}

void BSD::loadCharacter(sf::Sprite &player, Champion &c) {
	player.setTextureRect(sf::IntRect(c.getSpr().x, c.getSpr().y, 170, 100));
	player.scale(2.0f, 2.0f);
	player.setOrigin(85, 50);
}

void BSD::calculateSpritePos(Champion &c) {
	c.setSpr(PIC_SIZE_X*0, 0);
}

void BSD::calculateSpriteNormalAttack(int frameCount, Champion &c) {  // ������ ī��Ʈ�� float�ε� int�� �Ѱܼ� ������ �ӵ��� �ٲ�� �ɰ��� �˾Ƽ� ������ �ٸ��ָ��
	if (frameCount == 0 || frameCount == 1) {
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 2);
	}
	else if (frameCount == 2 || frameCount == 3) {
		c.setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 2);
	}
	else if (frameCount == 4 || frameCount == 5) {
		c.setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 2);
	}
	else if (frameCount == 6 || frameCount == 7) {
		c.setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 2);
	}
	else if (frameCount == 8 || frameCount == 9) {
		c.setSpr(PIC_SIZE_X * 4, PIC_SIZE_Y * 2);
	}
	else if (frameCount == 10 || frameCount == 11) {
		c.setSpr(PIC_SIZE_X * 5, PIC_SIZE_Y * 2);
	}
	else if (frameCount == 12 || frameCount == 13) {
		c.setSpr(PIC_SIZE_X * 6, PIC_SIZE_Y * 2);
	}
	else {
		c.setSpr(PIC_SIZE_X * 7, PIC_SIZE_Y * 2);
	}
}

void BSD::calculateSpriteEnergyAttack(int frameCount, Champion &c) {  // ������ ī��Ʈ�� float�ε� int�� �Ѱܼ� ������ �ӵ��� �ٲ�� �ɰ��� �˾Ƽ� ������ �ٸ��ָ��
	if (frameCount == 0 || frameCount == 1) {
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 3);
	}
	else if (frameCount == 2 || frameCount == 3) {
		c.setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 3);
	}
	else if (frameCount == 4 || frameCount == 5) {
		c.setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 3);
	}
	else if (frameCount == 6 || frameCount == 7) {
		c.setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 3);
	}
	else if (frameCount == 8 || frameCount == 9) {
		c.setSpr(PIC_SIZE_X * 4, PIC_SIZE_Y * 3);
	}
	else if (frameCount == 10 || frameCount == 11) {
		c.setSpr(PIC_SIZE_X * 5, PIC_SIZE_Y * 3);
	}
	else if (frameCount == 12 || frameCount == 13) {
		c.setSpr(PIC_SIZE_X * 6, PIC_SIZE_Y * 3);
	}
	else {
		c.setSpr(PIC_SIZE_X * 7, PIC_SIZE_Y * 3);
	}
}

void BSD::calculateSpriteBlock(Champion &c) {
	c.setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 0);
}

void BSD::calculateSpriteBSDHead(int frameCount, Champion &c) {
	if (frameCount == 0 || frameCount == 1) {
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 4);
	}
	else if (frameCount == 2 || frameCount == 3) {
		c.setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 4);
	}
	else if (frameCount == 4 || frameCount == 5) {
		c.setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 4);
	}
	else if (frameCount == 6 || frameCount == 7) {
		c.setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 4);
	}
	else if (frameCount == 8 || frameCount == 9) {
		c.setSpr(PIC_SIZE_X * 4, PIC_SIZE_Y * 4);
	}
	else if (frameCount == 10 || frameCount == 11) {
		c.setSpr(PIC_SIZE_X * 5, PIC_SIZE_Y * 4);
	}
	else if (frameCount == 12 || frameCount == 13) {
		c.setSpr(PIC_SIZE_X * 6, PIC_SIZE_Y * 4);
	}
	else {
		c.setSpr(PIC_SIZE_X * 7, PIC_SIZE_Y * 4);
	}
}

void BSD::calculateSpriteBSDPunch(int frameCount, Champion &c) {
	if (frameCount == 0 || frameCount == 1) {
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 5);
	}
	else if (frameCount == 2 || frameCount == 3) {
		c.setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 5);
	}
	else if (frameCount == 4 || frameCount == 5) {
		c.setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 5);
	}
	else if (frameCount == 6 || frameCount == 7) {
		c.setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 5);
	}
	else if (frameCount == 8 || frameCount == 9) {
		c.setSpr(PIC_SIZE_X * 4, PIC_SIZE_Y * 5);
	}
	else if (frameCount == 10 || frameCount == 11) {
		c.setSpr(PIC_SIZE_X * 5, PIC_SIZE_Y * 5);
	}
	else if (frameCount == 12 || frameCount == 13) {
		c.setSpr(PIC_SIZE_X * 6, PIC_SIZE_Y * 5);
	}
	else {
		c.setSpr(PIC_SIZE_X * 7, PIC_SIZE_Y * 5);
	}
}


void BSD::calculateSpriteKnockBack(int frameCount, Champion &c) {
	if (frameCount < 4) {
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 1);
	}
	else if (frameCount < 8) {
		c.setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 1);
	}
	else {
		c.setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 1);
	}
}

void BSD::calculateSpriteStun(int frameCount, Champion &c) {
	if (frameCount < 2) {
		c.setSpr(PIC_SIZE_X * 6, PIC_SIZE_Y * 0);
	}
	else if (frameCount < 4) {
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 1);
	}
}

void BSD::setSkillNumber(int skillNumber) {
	this->skillNumber = skillNumber;
}

int BSD::getSkillNumber() {
	return skillNumber;
}

int BSD::getSkillFrameTotal() {
	return skillFrame[skillNumber];
}

int BSD::getCanUseSkillCount(int skillNumber) {
	return canUseSkillCount[skillNumber];
}

void BSD::updateAOList(Champion &c) {
	for (auto ao = c.attackObjList.begin(); ao != c.attackObjList.end(); ao++) {
		if ((*ao)->isthrow == false) {								// ����ü�� �ƴ� �͵�
			if ((*ao)->skillNumber == 0) {							// 0�� ��ų�� ������ ���� ���� (ĳ���� ���� �������� �ϱ� ������)
				if (c.getFacing()) {
					(*ao)->range_s = sf::Vector2f(c.getPosition().x - PIC_SIZE_X / 4 * 3, c.getPosition().y - PIC_SIZE_Y * 2);
					(*ao)->range_e = sf::Vector2f(c.getPosition().x - PIC_SIZE_X / 7, c.getPosition().y);
				}
				else {
					(*ao)->range_s = sf::Vector2f(c.getPosition().x - PIC_SIZE_X / 7 * 6, c.getPosition().y - PIC_SIZE_Y * 2);
					(*ao)->range_e = sf::Vector2f(c.getPosition().x - PIC_SIZE_X / 4, c.getPosition().y);
				}
			}
			if (!c.isAttacking())						// ����ü�� �ƴϱ� ������ ������ ������ �˾Ƽ� ���� ���Ѿ� ��
				(*ao)->check = true;
		}
		else {																			// ����ü��
			if ((*ao)->skillNumber == 1) {												// 1�� ��ų
				(*ao)->range_s += (*ao)->direct * (*ao)->speed;							// �ǰ� ���� ����
				(*ao)->range_e += (*ao)->direct * (*ao)->speed;
				(*ao)->obj.setPosition((*ao)->range_s);									// ����ü ��ġ�� �ǰ� ������ ���� ����
				if ((*ao)->range_e.x < 0 || (*ao)->range_s.x > c.w_Width || (*ao)->range_e.y > 400 || (*ao)->range_s.y < 0) {	//ȭ�� ������ ���� ��
					(*ao)->check = true;
				}
			}
			if ((*ao)->skillNumber == 2) {												// 2�� ��ų�� 1�� ��ų�� ����
				(*ao)->range_s += (*ao)->direct * (*ao)->speed;
				(*ao)->range_e += (*ao)->direct * (*ao)->speed;
				(*ao)->obj.setPosition((*ao)->range_s);
				if ((*ao)->range_e.x < 0 || (*ao)->range_s.x > c.w_Width || (*ao)->range_e.y > 400 || (*ao)->range_s.y < 0) {
					(*ao)->check = true;
				}
			}
			else if ((*ao)->skillNumber == 3) {											// 3�� ��ų
				if ((*ao)->hitcount % 10 <= 1) {										// �ǰ� ��, Ȥ�� �ǰ� �� ���� �ð� ������ �̹��� ����
					if (c.getFacing()) {
						if ((*ao)->range_e.x - (*ao)->range_s.x < PIC_SIZE_X * 2.5)		// �ǰ� ������ �̹��� ũ�� �ʰ��ϱ� ��
						{
							if((*ao)->hitcount < 29 && (*ao)->hitcount > 1)					// �ǰ� ��
								(*ao)->range_e += (*ao)->direct * ((*ao)->speed * 0.5f);	// ��ġ�� ������ �̵�
							else															// �ǰ� ���� �ƴ� ��
								(*ao)->range_e += (*ao)->direct * (*ao)->speed;				//��ġ�� ������ �̵�
						}
						float punchrange = (*ao)->range_e.x - (*ao)->range_s.x;			// �ǰ� ����
						if (punchrange > PIC_SIZE_X * 2.5)								// �ǰ� ������ �̹��� ũ�� �ʰ��� ��
						{
							punchrange = PIC_SIZE_X * 2.5;									// �̹��� ũ�� �ʰ����� �ʵ��� ����
							if((*ao)->hitcount == 30)	(*ao)->check = true;				// �ǰ����� �ʾ��� �� ����ü �Ҹ�
						}
						// ������ ��ġ�̱� ������ �����ʺ��� �������� ��������Ʈ�� �о���� ȭ�鿡�� �̵��ϵ��� ����
						(*ao)->obj.setTextureRect(sf::IntRect((*ao)->objSpr.x + PIC_SIZE_X - punchrange / 2.5, (*ao)->objSpr.y, punchrange / 2.5, PIC_SIZE_Y));
						(*ao)->obj.setPosition((*ao)->range_s);
					}
					else {
						if ((*ao)->range_e.x - (*ao)->range_s.x < PIC_SIZE_X * 2.5)
						{
							if ((*ao)->hitcount < 29 && (*ao)->hitcount > 1)
								(*ao)->range_s += (*ao)->direct * ((*ao)->speed * 0.5f);
							else
								(*ao)->range_s += (*ao)->direct * (*ao)->speed;
						}
						float punchrange = (*ao)->range_e.x - (*ao)->range_s.x;
						if (punchrange > PIC_SIZE_X * 2.5)
						{
							punchrange = PIC_SIZE_X * 2.5;
							if ((*ao)->hitcount == 30)	(*ao)->check = true;
						}
						(*ao)->obj.setTextureRect(sf::IntRect((*ao)->objSpr.x, (*ao)->objSpr.y, punchrange / 2.5, PIC_SIZE_Y));
						(*ao)->obj.setPosition((*ao)->range_s);
					}
				}

			}
			else {
				(*ao)->range_s += (*ao)->direct * (*ao)->speed;													// �̰� Ȥ�ó� �ʿ��ϸ� ���� ����
				(*ao)->range_e += (*ao)->direct * (*ao)->speed;
				if ((*ao)->range_e.x < 0 || (*ao)->range_s.x >c.w_Width || (*ao)->range_e.y > 400 || (*ao)->range_s.y < 0) {
					(*ao)->check = true;
				}
			}
		}
		(*ao)->frameCount += 0.02;	// ����ü�� ĳ������ frameCount�� �����ϱ� ���� �����߰�, �ӵ��� ĳ���Ͷ� �Ȱ���
	}
}

void BSD::detectCollision(Champion &champion, std::list<AttackObject*> &aoList, float &enemyFrameCount) { // �������� �����ϴ� ����Ʈ�ø���
	float left = champion.getPosition().x - PIC_SIZE_X;
	float right = champion.getPosition().x;
	float top = champion.getPosition().y - PIC_SIZE_Y*2.0 / 8.0*7.0;
	float bottom = champion.getPosition().y;
	for (auto ao = aoList.begin(); ao != aoList.end(); ao++) {
		if (((*ao)->range_s.x < left && (*ao)->range_e.x > left) || ((*ao)->range_s.x < right && (*ao)->range_e.x > right)) {
			if (((*ao)->range_s.y < top && (*ao)->range_e.y > top) || ((*ao)->range_s.y < bottom && (*ao)->range_e.y > bottom)) {
				// �¾���
				if ((*ao)->skillNumber == 0) {	// ��Ÿ ������ ������ ���� ��
					(*ao)->check = true;
					if (champion.isBarrier()) champion.setHp(champion.getHp() - (*ao)->damage*0.2);
					else {
						champion.isStun = true;
						enemyFrameCount = 0;
						champion.setHp(champion.getHp() - (*ao)->damage);
						champion.vx = (*ao)->enemyDirect.x;
						champion.vy = (*ao)->enemyDirect.y;
					}
					if (champion.getHp() < 0) champion.setHp(0);
				}
				else if ((*ao)->skillNumber == 1) {  // ������ ���� ������ ������ ���̵�
					(*ao)->check = true;
					if (champion.isBarrier()) champion.setHp(champion.getHp() - (*ao)->damage*0.2);
					else {
						champion.isStun = true;
						enemyFrameCount = 0;
						champion.setHp(champion.getHp() - (*ao)->damage);
						champion.vx = (*ao)->enemyDirect.x;
						champion.vy = (*ao)->enemyDirect.y;
					}
					if (champion.getHp() < 0) champion.setHp(0);
				}
				else if ((*ao)->skillNumber == 2) { // BSD �Ӹ� ������ ������ ���� ��
					if (champion.isBarrier())
					{
						if ((*ao)->hitcount == 0) 	(*ao)->check = true;				// ������ Ƚ����ŭ HIT���� ��� ����ü �Ҹ�
						else {
							if (enemyFrameCount > 1) {									// FrameCount�� 1�� �Ѿ�� �� �� �ǰ� üũ
								(*ao)->hitcount--;										// ������ HIT Ƚ�� ����
								champion.setHp(champion.getHp() - (*ao)->damage*0.2);
								enemyFrameCount = 0;									// FrameCount �ʱ�ȭ
							}
							else	enemyFrameCount += 0.02;							// FrameCount ����

							(*ao)->check = false;
						}
					}
					else {
						if ((*ao)->hitcount == 0) {										// ������ Ƚ����ŭ HIT���� ��� �˹��Ű�� �Ҹ�
							champion.isKnockBack = true;
							champion.vx = (*ao)->enemyDirect.x;
							champion.vy = (*ao)->enemyDirect.y;
							(*ao)->check = true;
						}
						else {
							if (enemyFrameCount > 2) {									// FrameCount�� 2�� �Ѿ�� �� �� �ǰ� üũ
								(*ao)->hitcount--;										// ������ HIT Ƚ�� ����
								champion.setHp(champion.getHp() - (*ao)->damage);

								champion.vx = (*ao)->enemyDirect.x / 7.0;
								champion.vy = (*ao)->enemyDirect.y / 7.0;
								enemyFrameCount = 0;									// FrameCount �ʱ�ȭ

							}
							else	champion.isStun = true;								// FrameCount ���� ���� ���� ����
						}
					}
					if (champion.getHp() < 0) champion.setHp(0);
				}
				else if ((*ao)->skillNumber == 3) {  // BSD ��ġ ������ ���� ��
					if ((*ao)->range_e.x - (*ao)->range_s.x < PIC_SIZE_X * 2.5)			// �ǰ� ������ �ִ� ������ �ʰ����� ���� ��
					{
						if (champion.isBarrier()) {
							if ((*ao)->hitcount >= 0 && enemyFrameCount > 2)			// FrameCount�� 2 �̻��̸� Hit Ƚ���� �������� ���
							{
								enemyFrameCount = 0;									// FrameCount �ʱ�ȭ
								if ((*ao)->hitcount % 10 == 0)	champion.setHp(champion.getHp() - (*ao)->damage*0.2);
								(*ao)->hitcount--;										// Hit Ƚ�� ����
							}
							else enemyFrameCount += 0.02;
						}
						else {
							if ((*ao)->hitcount >= 0 && enemyFrameCount > 2) {			// FrameCount�� 2 �̻��̸� Hit Ƚ���� �������� ���
								enemyFrameCount = 0;
								if ((*ao)->hitcount % 10 == 0) {						// 0��°, 10��°, 20��°, 30��° Hit�� ���
									champion.setHp(champion.getHp() - (*ao)->damage);
									champion.vx = (*ao)->enemyDirect.x / 10.0;
									champion.vy = (*ao)->enemyDirect.y / 10.0;
								}
								(*ao)->hitcount--;										// Hit Ƚ�� ����
							}
							else champion.isStun = true;								// �ƴ� �� ��� ����
						}
					}
					else if ((*ao)->range_e.x - (*ao)->range_s.x >= PIC_SIZE_X * 2.5)	// �ǰ� ������ �ִ� ������ �ʰ��� ��
					{
						if (champion.isBarrier())	champion.setHp(champion.getHp() - (*ao)->damage*0.2);
						else {
							champion.isKnockBack = true;
							champion.setHp(champion.getHp() - (*ao)->damage);
							champion.vx = (*ao)->enemyDirect.x;
							champion.vy = (*ao)->enemyDirect.y;
						}
						(*ao)->check = true;
					}
					if (champion.getHp() < 0) champion.setHp(0);
				}
			}
		}
	}
};