#include "LGPL.hpp"

const int PIC_SIZE_X = 170;
const int PIC_SIZE_Y = 100;
const int ENERGY_SIZE_X = 85;
const int ENERGY_SIZE_Y = 40;

LGPL::~LGPL() { }

void LGPL::useSkill(int skillnumber, int frameCount, Champion &c) { // ��ų �ߵ�
	if (skillnumber == 0) {
		skill_NormalAttack(frameCount, c);
	}
	else if (skillnumber == 1) {
		skill_ResserBim(frameCount, c);
	}
	else if (skillnumber == 2) {
		skill_Boombaya(frameCount, c);
	}
	else if (skillnumber == 3) {
		calculateSpriteMagnetic(frameCount, c);
	}
}

void LGPL::skill_NormalAttack(int frameCount, Champion &c) { // Ȥ�ó� �ٸ��� �Ұ� ������� ���� ����
	calculateSpriteNormalAttack(frameCount, c);
}

void LGPL::skill_Magnetic(int frameCount, Champion &c) { 
	calculateSpriteMagnetic(frameCount, c);
}

void LGPL::skill_ResserBim(int frameCount, Champion &c) {
	calculateSpriteResserBim(frameCount, c);
}

void LGPL::skill_Boombaya(int frameCount, Champion &c) {
	calculateSpriteBoombaya(frameCount, c);
}

void LGPL::hit_KnockBack(int frameCount, Champion &c) {
	calculateSpriteKnockBack(frameCount, c);
}

void LGPL::hit_stun(int frameCount, Champion &c) {
	calculateSpriteStun(frameCount, c);
}

void LGPL::loadCharacter(sf::Sprite &player, Champion &c) {
	player.setTextureRect(sf::IntRect(c.getSpr().x, c.getSpr().y, PIC_SIZE_X, PIC_SIZE_Y));
	player.scale(2.0f, 2.0f);
	player.setOrigin(PIC_SIZE_X/2, PIC_SIZE_Y/2);
}

void LGPL::calculateSpritePos(Champion &c) {
	c.setSpr(PIC_SIZE_X*0, 0);
}

void LGPL::calculateSpriteNormalAttack(int frameCount, Champion &c) {  // ������ ī��Ʈ�� float�ε� int�� �Ѱܼ� ������ �ӵ��� �ٲ�� �ɰ��� �˾Ƽ� ������ �ٸ��ָ��
	if(frameCount == 0 ){
		c.setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 2);
	}
	else if(frameCount == 1 ){
		c.setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 2);
	}
	else if(frameCount == 2 ){
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 2);
	}
	else if(frameCount == 3 ){
		c.setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 2);
	}
	else if(frameCount == 4 ){
		c.setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 2);
	}
	else if(frameCount == 5 ){
		c.setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 2);
	}
	else{
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 0);
	}	
}

void LGPL::calculateSpriteMagnetic(int frameCount, Champion &c) {  // ������ ī��Ʈ�� float�ε� int�� �Ѱܼ� ������ �ӵ��� �ٲ�� �ɰ��� �˾Ƽ� ������ �ٸ��ָ��
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
		c.setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 4);
	}
	else if (frameCount == 8 || frameCount == 9) {
		c.setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 4);
	}
}

void LGPL::calculateSpriteBlock(Champion &c) {
	c.setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 0);
}

void LGPL::calculateSpriteBoombaya(int frameCount, Champion &c) {
	
	if (frameCount == 0 || frameCount == 1) {
		c.setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 0);
	}
	else if (frameCount == 2 || frameCount == 3) {
		c.setSpr(PIC_SIZE_X * 4, PIC_SIZE_Y * 1);
	}
	else if (frameCount == 4 || frameCount == 5) {
		c.setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 1);
	}
	
}

void LGPL::calculateSpriteResserBim(int frameCount, Champion &c) {
	if (frameCount == 0 || frameCount == 1) {
		c.setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 0);
	}
	else if (frameCount == 2 || frameCount == 3) {
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 3);
	}
	else if (frameCount == 4 || frameCount == 5) {
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 3);
	}
}


void LGPL::calculateSpriteKnockBack(int frameCount, Champion &c) {
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

void LGPL::calculateSpriteStun(int frameCount, Champion &c) {
	if (frameCount < 2) {
		c.setSpr(PIC_SIZE_X * 6, PIC_SIZE_Y * 0);
	}
	else if (frameCount < 4) {
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 1);
	}
}

void LGPL::setSkillNumber(int skillNumber) {
	this->skillNumber = skillNumber;
}

int LGPL::getSkillNumber() {
	return skillNumber;
}

int LGPL::getSkillFrameTotal() {
	return skillFrame[skillNumber];
}

int LGPL::getCanUseSkillCount(int skillNumber) {
	return canUseSkillCount[skillNumber];
}

void LGPL::updateAOList(Champion &c) {
	for (auto ao = c.attackObjList.begin(); ao != c.attackObjList.end(); ao++) {
		if ((*ao)->isthrow == false) {								// ����ü�� �ƴ� �͵�
			
		}
		else {																			// ����ü��
			if ((*ao)->skillNumber == 0) {												// 1�� ��ų
				(*ao)->range_s += (*ao)->direct * (*ao)->speed;							// �ǰ� ���� ����
				(*ao)->range_e += (*ao)->direct * (*ao)->speed;
				(*ao)->obj.setPosition((*ao)->range_s);									// ����ü ��ġ�� �ǰ� ������ ���� ����
				if ((*ao)->range_e.x < 0 || (*ao)->range_s.x > c.w_Width || (*ao)->range_e.y > 400 || (*ao)->range_s.y < 0) {	//ȭ�� ������ ���� ��
					(*ao)->check = true;
				}

			}
			if ((*ao)->skillNumber == 1) {												// 2�� ��ų�� 1�� ��ų�� ����
				(*ao)->range_s += (*ao)->direct * (*ao)->speed;
				(*ao)->range_e += (*ao)->direct * (*ao)->speed;
				(*ao)->obj.setPosition((*ao)->range_s);
				if ((*ao)->range_e.x < 0 || (*ao)->range_s.x > c.w_Width-200 || (*ao)->range_e.y > 400 || (*ao)->range_s.y < 0) {
					(*ao)->check = true;
				}
			}    
			if ((*ao)->skillNumber == 2) {												// 2�� ��ų�� 1�� ��ų�� ����
				(*ao)->range_s += (*ao)->direct * (*ao)->speed;
				(*ao)->range_e += (*ao)->direct * (*ao)->speed;
				(*ao)->obj.setPosition((*ao)->range_s);
				if ((*ao)->range_e.x < 0 || (*ao)->range_s.x > c.w_Width-200 || (*ao)->range_e.y > 400 || (*ao)->range_s.y < 0) {
					(*ao)->check = true;
				}
			}  
			if ((*ao)->skillNumber == 3) {												// 2�� ��ų�� 1�� ��ų�� ����
				(*ao)->range_s += (*ao)->direct * (*ao)->speed ;
				(*ao)->range_e += (*ao)->direct * (*ao)->speed;
				(*ao)->obj.setPosition((*ao)->range_s);
				if ((*ao)->range_e.x < 0 || (*ao)->range_s.x > c.w_Width-200 || (*ao)->range_e.y > 400 || (*ao)->range_s.y < 0) {
					(*ao)->check = true;
				}
			}      
		}
		(*ao)->frameCount += 0.2;	// ����ü�� ĳ������ frameCount�� �����ϱ� ���� �����߰�, �ӵ��� ĳ���Ͷ� �Ȱ���
	}
}

void LGPL::detectCollision(Champion &champion, std::list<AttackObject*> &aoList, float &enemyFrameCount) { // �������� �����ϴ� ����Ʈ�ø���
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
				else if ((*ao)->skillNumber == 2 ||(*ao)->skillNumber == 3) { // LGPL �Ӹ� ������ ������ ���� ��
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
			}
		}
	}
};