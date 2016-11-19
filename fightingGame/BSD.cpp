#include "BSD.hpp"

const int PIC_SIZE_X = 170;
const int PIC_SIZE_Y = 100;
const int ENERGY_SIZE_X = 85;
const int ENERGY_SIZE_Y = 40;

BSD::~BSD() { }

void BSD::useSkill(int skillnumber, int frameCount) { // ��ų �ߵ�
	if (skillnumber == 0) {
		skill_NormalAttack(frameCount);
	}
	else if (skillnumber == 1) {
		skill_EnergyAttack(frameCount);
	}
	else if (skillnumber == 2) {
		skill_BSDHead(frameCount);
	}
	else if (skillnumber == 3) {
		skill_BSDPunch(frameCount);
	}
	else if (skillnumber == 4) {
		skill_Dash(frameCount);
	}
}

void BSD::crowdControlHit(float &frameCount) {		//cc�¾�����
	if (this->isStun) {
		hit_stun((int)frameCount);
		frameCount += 0.02;
		if (frameCount > 4) this->isStun = false;
	}
	else if (this->isKnockBack) {
		hit_KnockBack((int)frameCount);
		frameCount += 0.02;
		if (frameCount > 20) this->isKnockBack = false;
	}
}

void BSD::insertAOList(int skillNumber) {

	if (skillNumber == 0) {
		AttackObject* ao = new AttackObject(skillNumber, 5, 1);
		ao->damage = 5;																									//������ 5
		ao->check = false;																								//�ǰ� �ʱ�ȭ
		ao->direct = sf::Vector2f(0, 0);																				//����ü �ƴϹǷ� ���� X
		ao->isthrow = false;																							//����ü �ƴ�
		if (this->getFacing()) {																						//�ǰ� ���� ����
			ao->range_s = sf::Vector2f(this->getPosition().x - PIC_SIZE_X / 4 * 3, this->getPosition().y - PIC_SIZE_Y * 2);
			ao->range_e = sf::Vector2f(this->getPosition().x - PIC_SIZE_X / 7, this->getPosition().y);
			ao->enemyDirect = sf::Vector2f(0.7, -0.3);
		}
		else {
			ao->range_s = sf::Vector2f(this->getPosition().x - PIC_SIZE_X / 7 * 6, this->getPosition().y - PIC_SIZE_Y * 2);
			ao->range_e = sf::Vector2f(this->getPosition().x - PIC_SIZE_X / 4, this->getPosition().y);
			ao->enemyDirect = sf::Vector2f(-0.7, -0.3);
		}
		attackObjList.push_back(ao);
	}

	else if (skillNumber == 1) {
		AttackObject* ao = new AttackObject(skillNumber, 10, 0.15);

		if (!ao->throwTexture.loadFromFile("./images/character/bsd_sprite.png")) printf("Error loading vx_characters\n");		// �̹��� �ҷ�����
		int random = rand() % 3;																								//gpl, lgpl, apache �� �� ���� ��������Ʈ ���� ���� ����
		if (this->getFacing()) {
			ao->objSpr = sf::Vector2f(PIC_SIZE_X*random, PIC_SIZE_Y * 7);														// ��������Ʈ ����ְ�
			ao->obj.setTexture(ao->throwTexture);																				// �ؽ��� �־��ְ�
			ao->obj.setTextureRect(sf::IntRect(ao->objSpr.x, ao->objSpr.y, 170, 100));											// �簢�� ���� ���ϰ�
			ao->obj.scale(1.5f, 1.5f);																							// ũ�� �÷��ְ�

			ao->range_s = sf::Vector2f(this->getPosition().x, this->getPosition().y - ENERGY_SIZE_Y / 2 * 3);
			ao->range_e = sf::Vector2f(this->getPosition().x + ENERGY_SIZE_X, this->getPosition().y + ENERGY_SIZE_Y / 2 * 3);

			ao->direct = sf::Vector2f(1, 0);																					// ����ü, ������

			ao->enemyDirect = sf::Vector2f(0.1, -0.1);
		}
		else {
			ao->objSpr = sf::Vector2f(PIC_SIZE_X*random, PIC_SIZE_Y * 6);														// ��������Ʈ ����ְ�
			ao->obj.setTexture(ao->throwTexture);																				// �ؽ��� �־��ְ�
			ao->obj.setTextureRect(sf::IntRect(ao->objSpr.x, ao->objSpr.y, 170, 100));											// �簢�� ���� ���ϰ�
			ao->obj.scale(1.5f, 1.5f);																							// ũ�� �÷��ְ�

			ao->range_s = sf::Vector2f(this->getPosition().x - PIC_SIZE_X - ENERGY_SIZE_X, this->getPosition().y - ENERGY_SIZE_Y / 2 * 3);
			ao->range_e = sf::Vector2f(this->getPosition().x - PIC_SIZE_X, this->getPosition().y + ENERGY_SIZE_Y / 2 * 3);

			ao->direct = sf::Vector2f(-1, 0);																						// ����ü, ����

			ao->enemyDirect = sf::Vector2f(-0.1, -0.1);
		}

		// ��ġ �����ְ�
		ao->damage = 10;																									// ������ 10
		ao->check = false;																									// check �ʱ�ȭ
		ao->isthrow = true;																									// ����ü

		attackObjList.push_back(ao);
	}

	else if (skillNumber == 2) {
		AttackObject* ao = new AttackObject(skillNumber, 3, 0.05);

		if (!ao->throwTexture.loadFromFile("./images/character/bsd_sprite.png")) printf("Error loading vx_characters\n");		// �̹��� �ҷ�����
		if (this->getFacing()) {
			ao->objSpr = sf::Vector2f(PIC_SIZE_X * 6, PIC_SIZE_Y * 7);															// ��������Ʈ ����ְ�
			ao->obj.setTexture(ao->throwTexture);																				// �ؽ��� �־��ְ�
			ao->obj.setTextureRect(sf::IntRect(ao->objSpr.x, ao->objSpr.y, 170, 100));											// �簢�� ���� ���ϰ�
			ao->obj.scale(1.5f, 1.5f);																							// ũ�� �÷��ְ�

			ao->range_s = sf::Vector2f(this->getPosition().x, this->getPosition().y - ENERGY_SIZE_Y / 2 * 3);
			ao->range_e = sf::Vector2f(this->getPosition().x + ENERGY_SIZE_X, this->getPosition().y + ENERGY_SIZE_Y / 2 * 3);

			ao->direct = sf::Vector2f(1, 0);																					// ����ü, ������

			ao->enemyDirect = sf::Vector2f(0.5, -0.4);
		}
		else {
			ao->objSpr = sf::Vector2f(PIC_SIZE_X * 6, PIC_SIZE_Y * 6);															// ��������Ʈ ����ְ�
			ao->obj.setTexture(ao->throwTexture);																				// �ؽ��� �־��ְ�
			ao->obj.setTextureRect(sf::IntRect(ao->objSpr.x, ao->objSpr.y, 170, 100));											// �簢�� ���� ���ϰ�
			ao->obj.scale(1.5f, 1.5f);																							// ũ�� �÷��ְ�

			ao->range_s = sf::Vector2f(this->getPosition().x - PIC_SIZE_X - ENERGY_SIZE_X, this->getPosition().y - ENERGY_SIZE_Y / 2 * 3);
			ao->range_e = sf::Vector2f(this->getPosition().x - PIC_SIZE_X, this->getPosition().y + ENERGY_SIZE_Y / 2 * 3);

			ao->direct = sf::Vector2f(-1, 0);																					// ����ü, ����

			ao->enemyDirect = sf::Vector2f(-0.5, -0.4);
		}

		// ��ġ �����ְ�
		ao->damage = 3;																										// 1 HIT �� 3 ������
		ao->check = false;																									// check �ʱ�ȭ
		ao->isthrow = true;																									// ����ü��
		ao->hitcount = 10;																									// �� 10ȸ HIT

		attackObjList.push_back(ao);
	}
	else if (skillNumber == 3) {			// ���� ���� �̹����� ������ �ϱ� ������ ���ٸ��� ����
		AttackObject* ao = new AttackObject(skillNumber, 15, 0.7);

		if (!ao->throwTexture.loadFromFile("./images/character/bsd_sprite.png")) printf("Error loading vx_characters\n");	// �̹��� �ҷ�����
		if (this->getFacing()) {
			ao->objSpr = sf::Vector2f(PIC_SIZE_X * 1, PIC_SIZE_Y * 8);														// ��������Ʈ ����ְ�
			ao->obj.setTexture(ao->throwTexture);																			// �ؽ��� �־��ְ�
			ao->obj.setTextureRect(sf::IntRect(ao->objSpr.x, ao->objSpr.y, 170, 100));										// �簢�� ���� ���ϰ�

			ao->range_s = sf::Vector2f(this->getPosition().x + PIC_SIZE_X / 3 * 1, this->getPosition().y - PIC_SIZE_Y);
			ao->range_e = sf::Vector2f(this->getPosition().x + PIC_SIZE_X / 3 * 1, this->getPosition().y + PIC_SIZE_Y);

			ao->direct = sf::Vector2f(1, 0);																				// ����ü, ������

			ao->enemyDirect = sf::Vector2f(0.8, -0.8);
		}
		else {
			ao->objSpr = sf::Vector2f(PIC_SIZE_X * 0, PIC_SIZE_Y * 8);														// ��������Ʈ ����ְ�
			ao->obj.setTexture(ao->throwTexture);																			// �ؽ��� �־��ְ�
			ao->obj.setTextureRect(sf::IntRect(ao->objSpr.x, ao->objSpr.y, 170, 100));										// �簢�� ���� ���ϰ�

			ao->range_s = sf::Vector2f(this->getPosition().x - PIC_SIZE_X / 3 * 1, this->getPosition().y - PIC_SIZE_Y);
			ao->range_e = sf::Vector2f(this->getPosition().x - PIC_SIZE_X / 3 * 1, this->getPosition().y + PIC_SIZE_Y);

			ao->direct = sf::Vector2f(-1, 0);																				// ����ü, ����

			ao->enemyDirect = sf::Vector2f(-0.8, -0.8);
		}

		ao->obj.scale(2.5f, 2.5f);																							// ũ�� Ű���ֱ�
		ao->damage = 15;																									// 1 HIT �� 15 ������
		ao->check = false;																									// check �ʱ�ȭ
		ao->isthrow = true;																									// ����ü
		ao->hitcount = 30;																									// �� 4ȸ HIT

		attackObjList.push_back(ao);																					// �־��ش�
	}
	else if (skillNumber == 4) {

	}
}

void BSD::skill_NormalAttack(int frameCount) { // Ȥ�ó� �ٸ��� �Ұ� ������� ���� ����
	calculateSpriteNormalAttack(frameCount);
}

void BSD::skill_EnergyAttack(int frameCount) { // Ȥ�ó� �ٸ��� �Ұ� ������� ���� ����
	calculateSpriteEnergyAttack(frameCount);
}

void BSD::skill_BSDHead(int frameCount) {
	calculateSpriteBSDHead(frameCount);
}

void BSD::skill_BSDPunch(int frameCount) {
	calculateSpriteBSDPunch(frameCount);
}

void BSD::skill_Dash(int frameCount) {

}

void BSD::hit_KnockBack(int frameCount) {
	calculateSpriteKnockBack(frameCount);
}

void BSD::hit_stun(int frameCount) {
	calculateSpriteStun(frameCount);
}

void BSD::loadCharacter(sf::Sprite &player) {
	player.setTextureRect(sf::IntRect(this->getSpr().x, this->getSpr().y, 170, 100));
	player.scale(2.0f, 2.0f);
	player.setOrigin(85, 50);
}

void BSD::calculateSpritePos(int step) {
	this->setSpr(PIC_SIZE_X*step, 0);
}

void BSD::calculateSpriteNormalAttack(int frameCount) {  // ������ ī��Ʈ�� float�ε� int�� �Ѱܼ� ������ �ӵ��� �ٲ�� �ɰ��� �˾Ƽ� ������ �ٸ��ָ��
	if (frameCount == 0 || frameCount == 1) {
		this->setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 2);
	}
	else if (frameCount == 2 || frameCount == 3) {
		this->setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 2);
	}
	else if (frameCount == 4 || frameCount == 5) {
		this->setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 2);
	}
	else if (frameCount == 6 || frameCount == 7) {
		this->setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 2);
	}
	else if (frameCount == 8 || frameCount == 9) {
		this->setSpr(PIC_SIZE_X * 4, PIC_SIZE_Y * 2);
	}
	else if (frameCount == 10 || frameCount == 11) {
		this->setSpr(PIC_SIZE_X * 5, PIC_SIZE_Y * 2);
	}
	else if (frameCount == 12 || frameCount == 13) {
		this->setSpr(PIC_SIZE_X * 6, PIC_SIZE_Y * 2);
	}
	else {
		this->setSpr(PIC_SIZE_X * 7, PIC_SIZE_Y * 2);
	}
}

void BSD::calculateSpriteEnergyAttack(int frameCount) {  // ������ ī��Ʈ�� float�ε� int�� �Ѱܼ� ������ �ӵ��� �ٲ�� �ɰ��� �˾Ƽ� ������ �ٸ��ָ��
	if (frameCount == 0 || frameCount == 1) {
		this->setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 3);
	}
	else if (frameCount == 2 || frameCount == 3) {
		this->setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 3);
	}
	else if (frameCount == 4 || frameCount == 5) {
		this->setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 3);
	}
	else if (frameCount == 6 || frameCount == 7) {
		this->setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 3);
	}
	else if (frameCount == 8 || frameCount == 9) {
		this->setSpr(PIC_SIZE_X * 4, PIC_SIZE_Y * 3);
	}
	else if (frameCount == 10 || frameCount == 11) {
		this->setSpr(PIC_SIZE_X * 5, PIC_SIZE_Y * 3);
	}
	else if (frameCount == 12 || frameCount == 13) {
		this->setSpr(PIC_SIZE_X * 6, PIC_SIZE_Y * 3);
	}
	else {
		this->setSpr(PIC_SIZE_X * 7, PIC_SIZE_Y * 3);
	}
}

void BSD::calculateSpriteBlock() {
	this->setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 0);
}

void BSD::calculateSpriteBSDHead(int frameCount) {
	if (frameCount == 0 || frameCount == 1) {
		this->setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 4);
	}
	else if (frameCount == 2 || frameCount == 3) {
		this->setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 4);
	}
	else if (frameCount == 4 || frameCount == 5) {
		this->setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 4);
	}
	else if (frameCount == 6 || frameCount == 7) {
		this->setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 4);
	}
	else if (frameCount == 8 || frameCount == 9) {
		this->setSpr(PIC_SIZE_X * 4, PIC_SIZE_Y * 4);
	}
	else if (frameCount == 10 || frameCount == 11) {
		this->setSpr(PIC_SIZE_X * 5, PIC_SIZE_Y * 4);
	}
	else if (frameCount == 12 || frameCount == 13) {
		this->setSpr(PIC_SIZE_X * 6, PIC_SIZE_Y * 4);
	}
	else {
		this->setSpr(PIC_SIZE_X * 7, PIC_SIZE_Y * 4);
	}
}

void BSD::calculateSpriteBSDPunch(int frameCount) {
	if (frameCount == 0 || frameCount == 1) {
		this->setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 5);
	}
	else if (frameCount == 2 || frameCount == 3) {
		this->setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 5);
	}
	else if (frameCount == 4 || frameCount == 5) {
		this->setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 5);
	}
	else if (frameCount == 6 || frameCount == 7) {
		this->setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 5);
	}
	else if (frameCount == 8 || frameCount == 9) {
		this->setSpr(PIC_SIZE_X * 4, PIC_SIZE_Y * 5);
	}
	else if (frameCount == 10 || frameCount == 11) {
		this->setSpr(PIC_SIZE_X * 5, PIC_SIZE_Y * 5);
	}
	else if (frameCount == 12 || frameCount == 13) {
		this->setSpr(PIC_SIZE_X * 6, PIC_SIZE_Y * 5);
	}
	else {
		this->setSpr(PIC_SIZE_X * 7, PIC_SIZE_Y * 5);
	}
}


void BSD::calculateSpriteKnockBack(int frameCount) {
	if (frameCount < 4) {
		this->setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 1);
	}
	else if (frameCount < 8) {
		this->setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 1);
	}
	else {
		this->setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 1);
	}
}

void BSD::calculateSpriteStun(int frameCount) {
	if (frameCount < 2) {
		this->setSpr(PIC_SIZE_X * 6, PIC_SIZE_Y * 0);
	}
	else if (frameCount < 4) {
		this->setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 1);
	}
}

void BSD::calculateSpriteDash(int frameCount) {

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

int BSD::getNecessaryMana(int skillNumber) {
	return necessaryMana[skillNumber];
}
void BSD::deleteAOList() {
	auto iter = attackObjList.begin();
	auto iter2 = iter;
	for (iter; iter != attackObjList.end(); iter = iter2) {
		iter2++;
		if ((*iter)->check) {
			attackObjList.erase(iter);
		}
	}
}

void BSD::updateAOList() {
	for (auto ao = attackObjList.begin(); ao != attackObjList.end(); ao++) {
		if ((*ao)->isthrow == false) {								// ����ü�� �ƴ� �͵�
			if ((*ao)->skillNumber == 0) {							// 0�� ��ų�� ������ ���� ���� (ĳ���� ���� �������� �ϱ� ������)
				if (this->getFacing()) {
					(*ao)->range_s = sf::Vector2f(this->getPosition().x - PIC_SIZE_X / 4 * 3, this->getPosition().y - PIC_SIZE_Y * 2);
					(*ao)->range_e = sf::Vector2f(this->getPosition().x - PIC_SIZE_X / 7, this->getPosition().y);
				}
				else {
					(*ao)->range_s = sf::Vector2f(this->getPosition().x - PIC_SIZE_X / 7 * 6, this->getPosition().y - PIC_SIZE_Y * 2);
					(*ao)->range_e = sf::Vector2f(this->getPosition().x - PIC_SIZE_X / 4, this->getPosition().y);
				}
			}
			if (!isAttacking())						// ����ü�� �ƴϱ� ������ ������ ������ �˾Ƽ� ���� ���Ѿ� ��
				(*ao)->check = true;
		}
		else {																			// ����ü��
			if ((*ao)->skillNumber == 1) {												// 1�� ��ų
				(*ao)->range_s += (*ao)->direct * (*ao)->speed;							// �ǰ� ���� ����
				(*ao)->range_e += (*ao)->direct * (*ao)->speed;
				(*ao)->obj.setPosition((*ao)->range_s);									// ����ü ��ġ�� �ǰ� ������ ���� ����
				if ((*ao)->range_e.x < 0 || (*ao)->range_s.x > w_Width || (*ao)->range_e.y > 400 || (*ao)->range_s.y < 0) {	//ȭ�� ������ ���� ��
					(*ao)->check = true;
				}
			}
			if ((*ao)->skillNumber == 2) {												// 2�� ��ų�� 1�� ��ų�� ����
				(*ao)->range_s += (*ao)->direct * (*ao)->speed;
				(*ao)->range_e += (*ao)->direct * (*ao)->speed;
				(*ao)->obj.setPosition((*ao)->range_s);
				if ((*ao)->range_e.x < 0 || (*ao)->range_s.x > w_Width || (*ao)->range_e.y > 400 || (*ao)->range_s.y < 0) {
					(*ao)->check = true;
				}
			}
			else if ((*ao)->skillNumber == 3) {											// 3�� ��ų
				if ((*ao)->hitcount % 10 <= 1) {										// �ǰ� ��, Ȥ�� �ǰ� �� ���� �ð� ������ �̹��� ����
					if (this->getFacing()) {
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
				if ((*ao)->range_e.x < 0 || (*ao)->range_s.x > w_Width || (*ao)->range_e.y > 400 || (*ao)->range_s.y < 0) {
					(*ao)->check = true;
				}
			}
		}
		(*ao)->frameCount += 0.02;	// ����ü�� ĳ������ frameCount�� �����ϱ� ���� �����߰�, �ӵ��� ĳ���Ͷ� �Ȱ���
	}
}

void BSD::detectCollision(Champion &champion, float &enemyFrameCount) { // �������� �����ϴ� ����Ʈ�ø���
	float left = champion.getPosition().x - PIC_SIZE_X;
	float right = champion.getPosition().x;
	float top = champion.getPosition().y - PIC_SIZE_Y*2.0 / 8.0*7.0;
	float bottom = champion.getPosition().y;
	for (auto ao = attackObjList.begin(); ao != attackObjList.end(); ao++) {
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