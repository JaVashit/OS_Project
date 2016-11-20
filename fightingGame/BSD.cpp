#include "BSD.hpp"

const int PIC_SIZE_X = 170;
const int PIC_SIZE_Y = 100;
const int ENERGY_SIZE_X = 85;
const int ENERGY_SIZE_Y = 40;

BSD::~BSD() { }

void BSD::useSkill(int skillnumber, int frameCount) { // 스킬 발동
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

void BSD::crowdControlHit(float &frameCount) {		//cc맞았을때
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
		ao->damage = 5;																									//데미지 5
		ao->check = false;																								//피격 초기화
		ao->direct = sf::Vector2f(0, 0);																				//투사체 아니므로 방향 X
		ao->isthrow = false;																							//투사체 아님
		if (this->getFacing()) {																						//피격 범위 설정
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

		if (!ao->throwTexture.loadFromFile("./images/character/bsd_sprite.png")) printf("Error loading vx_characters\n");		// 이미지 불러오고
		int random = rand() % 3;																								//gpl, lgpl, apache 중 한 개의 스프라이트 선택 위한 난수
		if (this->getFacing()) {
			ao->objSpr = sf::Vector2f(PIC_SIZE_X*random, PIC_SIZE_Y * 7);														// 스프라이트 찍어주고
			ao->obj.setTexture(ao->throwTexture);																				// 텍스쳐 넣어주고
			ao->obj.setTextureRect(sf::IntRect(ao->objSpr.x, ao->objSpr.y, 170, 100));											// 사각형 범위 정하고
			ao->obj.scale(1.5f, 1.5f);																							// 크기 늘려주고

			ao->range_s = sf::Vector2f(this->getPosition().x, this->getPosition().y - ENERGY_SIZE_Y / 2 * 3);
			ao->range_e = sf::Vector2f(this->getPosition().x + ENERGY_SIZE_X, this->getPosition().y + ENERGY_SIZE_Y / 2 * 3);

			ao->direct = sf::Vector2f(1, 0);																					// 투사체, 오른쪽

			ao->enemyDirect = sf::Vector2f(0.1, -0.1);
		}
		else {
			ao->objSpr = sf::Vector2f(PIC_SIZE_X*random, PIC_SIZE_Y * 6);														// 스프라이트 찍어주고
			ao->obj.setTexture(ao->throwTexture);																				// 텍스쳐 넣어주고
			ao->obj.setTextureRect(sf::IntRect(ao->objSpr.x, ao->objSpr.y, 170, 100));											// 사각형 범위 정하고
			ao->obj.scale(1.5f, 1.5f);																							// 크기 늘려주고

			ao->range_s = sf::Vector2f(this->getPosition().x - PIC_SIZE_X - ENERGY_SIZE_X, this->getPosition().y - ENERGY_SIZE_Y / 2 * 3);
			ao->range_e = sf::Vector2f(this->getPosition().x - PIC_SIZE_X, this->getPosition().y + ENERGY_SIZE_Y / 2 * 3);

			ao->direct = sf::Vector2f(-1, 0);																						// 투사체, 왼쪽

			ao->enemyDirect = sf::Vector2f(-0.1, -0.1);
		}

		// 위치 정해주고
		ao->damage = 10;																									// 데미지 10
		ao->check = false;																									// check 초기화
		ao->isthrow = true;																									// 투사체

		attackObjList.push_back(ao);
	}

	else if (skillNumber == 2) {
		AttackObject* ao = new AttackObject(skillNumber, 3, 0.05);

		if (!ao->throwTexture.loadFromFile("./images/character/bsd_sprite.png")) printf("Error loading vx_characters\n");		// 이미지 불러오고
		if (this->getFacing()) {
			ao->objSpr = sf::Vector2f(PIC_SIZE_X * 6, PIC_SIZE_Y * 7);															// 스프라이트 찍어주고
			ao->obj.setTexture(ao->throwTexture);																				// 텍스쳐 넣어주고
			ao->obj.setTextureRect(sf::IntRect(ao->objSpr.x, ao->objSpr.y, 170, 100));											// 사각형 범위 정하고
			ao->obj.scale(1.5f, 1.5f);																							// 크기 늘려주고

			ao->range_s = sf::Vector2f(this->getPosition().x, this->getPosition().y - ENERGY_SIZE_Y / 2 * 3);
			ao->range_e = sf::Vector2f(this->getPosition().x + ENERGY_SIZE_X, this->getPosition().y + ENERGY_SIZE_Y / 2 * 3);

			ao->direct = sf::Vector2f(1, 0);																					// 투사체, 오른쪽

			ao->enemyDirect = sf::Vector2f(0.5, -0.4);
		}
		else {
			ao->objSpr = sf::Vector2f(PIC_SIZE_X * 6, PIC_SIZE_Y * 6);															// 스프라이트 찍어주고
			ao->obj.setTexture(ao->throwTexture);																				// 텍스쳐 넣어주고
			ao->obj.setTextureRect(sf::IntRect(ao->objSpr.x, ao->objSpr.y, 170, 100));											// 사각형 범위 정하고
			ao->obj.scale(1.5f, 1.5f);																							// 크기 늘려주고

			ao->range_s = sf::Vector2f(this->getPosition().x - PIC_SIZE_X - ENERGY_SIZE_X, this->getPosition().y - ENERGY_SIZE_Y / 2 * 3);
			ao->range_e = sf::Vector2f(this->getPosition().x - PIC_SIZE_X, this->getPosition().y + ENERGY_SIZE_Y / 2 * 3);

			ao->direct = sf::Vector2f(-1, 0);																					// 투사체, 왼쪽

			ao->enemyDirect = sf::Vector2f(-0.5, -0.4);
		}

		// 위치 정해주고
		ao->damage = 3;																										// 1 HIT 당 3 데미지
		ao->check = false;																									// check 초기화
		ao->isthrow = true;																									// 투사체고
		ao->hitcount = 10;																									// 총 10회 HIT

		attackObjList.push_back(ao);
	}
	else if (skillNumber == 3) {			// 궁은 따로 이미지를 입혀야 하기 때문에 색다르게 설정
		AttackObject* ao = new AttackObject(skillNumber, 15, 0.7);

		if (!ao->throwTexture.loadFromFile("./images/character/bsd_sprite.png")) printf("Error loading vx_characters\n");	// 이미지 불러오고
		if (this->getFacing()) {
			ao->objSpr = sf::Vector2f(PIC_SIZE_X * 1, PIC_SIZE_Y * 8);														// 스프라이트 찍어주고
			ao->obj.setTexture(ao->throwTexture);																			// 텍스쳐 넣어주고
			ao->obj.setTextureRect(sf::IntRect(ao->objSpr.x, ao->objSpr.y, 170, 100));										// 사각형 범위 정하고

			ao->range_s = sf::Vector2f(this->getPosition().x + PIC_SIZE_X / 3 * 1, this->getPosition().y - PIC_SIZE_Y);
			ao->range_e = sf::Vector2f(this->getPosition().x + PIC_SIZE_X / 3 * 1, this->getPosition().y + PIC_SIZE_Y);

			ao->direct = sf::Vector2f(1, 0);																				// 투사체, 오른쪽

			ao->enemyDirect = sf::Vector2f(0.8, -0.8);
		}
		else {
			ao->objSpr = sf::Vector2f(PIC_SIZE_X * 0, PIC_SIZE_Y * 8);														// 스프라이트 찍어주고
			ao->obj.setTexture(ao->throwTexture);																			// 텍스쳐 넣어주고
			ao->obj.setTextureRect(sf::IntRect(ao->objSpr.x, ao->objSpr.y, 170, 100));										// 사각형 범위 정하고

			ao->range_s = sf::Vector2f(this->getPosition().x - PIC_SIZE_X / 3 * 1, this->getPosition().y - PIC_SIZE_Y);
			ao->range_e = sf::Vector2f(this->getPosition().x - PIC_SIZE_X / 3 * 1, this->getPosition().y + PIC_SIZE_Y);

			ao->direct = sf::Vector2f(-1, 0);																				// 투사체, 왼쪽

			ao->enemyDirect = sf::Vector2f(-0.8, -0.8);
		}

		ao->obj.scale(2.5f, 2.5f);																							// 크기 키워주기
		ao->damage = 15;																									// 1 HIT 당 15 데미지
		ao->check = false;																									// check 초기화
		ao->isthrow = true;																									// 투사체
		ao->hitcount = 30;																									// 총 4회 HIT

		attackObjList.push_back(ao);																					// 넣어준다
	}
	else if (skillNumber == 4) {

	}
}

void BSD::skill_NormalAttack(int frameCount) { // 혹시나 다른거 할거 있을까봐 따로 빼냄
	calculateSpriteNormalAttack(frameCount);
}

void BSD::skill_EnergyAttack(int frameCount) { // 혹시나 다른거 할거 있을까봐 따로 빼냄
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

void BSD::calculateSpriteNormalAttack(int frameCount) {  // 프레임 카운트는 float인데 int로 넘겨서 적당한 속도로 바뀌게 될거임 알아서 멋지게 꾸며주면됨
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

void BSD::calculateSpriteEnergyAttack(int frameCount) {  // 프레임 카운트는 float인데 int로 넘겨서 적당한 속도로 바뀌게 될거임 알아서 멋지게 꾸며주면됨
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
		if ((*ao)->isthrow == false) {								// 투사체가 아닌 것들
			if ((*ao)->skillNumber == 0) {							// 0번 스킬은 다음과 같이 설정 (캐릭터 따라서 움직여야 하기 때문에)
				if (this->getFacing()) {
					(*ao)->range_s = sf::Vector2f(this->getPosition().x - PIC_SIZE_X / 4 * 3, this->getPosition().y - PIC_SIZE_Y * 2);
					(*ao)->range_e = sf::Vector2f(this->getPosition().x - PIC_SIZE_X / 7, this->getPosition().y);
				}
				else {
					(*ao)->range_s = sf::Vector2f(this->getPosition().x - PIC_SIZE_X / 7 * 6, this->getPosition().y - PIC_SIZE_Y * 2);
					(*ao)->range_e = sf::Vector2f(this->getPosition().x - PIC_SIZE_X / 4, this->getPosition().y);
				}
			}
			if (!isAttacking())						// 투사체가 아니기 때문에 공격이 끝나면 알아서 삭제 시켜야 함
				(*ao)->check = true;
		}
		else {																			// 투사체들
			if ((*ao)->skillNumber == 1) {												// 1번 스킬
				(*ao)->range_s += (*ao)->direct * (*ao)->speed;							// 피격 범위 변경
				(*ao)->range_e += (*ao)->direct * (*ao)->speed;
				(*ao)->obj.setPosition((*ao)->range_s);									// 투사체 위치를 피격 범위에 맞춰 조정
				if ((*ao)->range_e.x < 0 || (*ao)->range_s.x > w_Width || (*ao)->range_e.y > 400 || (*ao)->range_s.y < 0) {	//화면 밖으로 나갈 시
					(*ao)->check = true;
				}
			}
			if ((*ao)->skillNumber == 2) {												// 2번 스킬은 1번 스킬과 동일
				(*ao)->range_s += (*ao)->direct * (*ao)->speed;
				(*ao)->range_e += (*ao)->direct * (*ao)->speed;
				(*ao)->obj.setPosition((*ao)->range_s);
				if ((*ao)->range_e.x < 0 || (*ao)->range_s.x > w_Width || (*ao)->range_e.y > 400 || (*ao)->range_s.y < 0) {
					(*ao)->check = true;
				}
			}
			else if ((*ao)->skillNumber == 3) {											// 3번 스킬
				if ((*ao)->hitcount % 10 <= 1) {										// 피격 전, 혹은 피격 중 일정 시간 내에만 이미지 갱신
					if (this->getFacing()) {
						if ((*ao)->range_e.x - (*ao)->range_s.x < PIC_SIZE_X * 2.5)		// 피격 범위가 이미지 크기 초과하기 전
						{
							if((*ao)->hitcount < 29 && (*ao)->hitcount > 1)					// 피격 중
								(*ao)->range_e += (*ao)->direct * ((*ao)->speed * 0.5f);	// 펀치가 느리게 이동
							else															// 피격 중이 아닐 시
								(*ao)->range_e += (*ao)->direct * (*ao)->speed;				//펀치가 빠르게 이동
						}
						float punchrange = (*ao)->range_e.x - (*ao)->range_s.x;			// 피격 범위
						if (punchrange > PIC_SIZE_X * 2.5)								// 피격 범위가 이미지 크기 초과할 시
						{
							punchrange = PIC_SIZE_X * 2.5;									// 이미지 크기 초과하지 않도록 보정
							if((*ao)->hitcount == 30)	(*ao)->check = true;				// 피격하지 않았을 시 투사체 소멸
						}
						// 오른쪽 펀치이기 때문에 오른쪽부터 왼쪽으로 스프라이트를 읽어오며 화면에서 이동하도록 설정
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
				(*ao)->range_s += (*ao)->direct * (*ao)->speed;													// 이건 혹시나 필요하면 갖다 쓰셈
				(*ao)->range_e += (*ao)->direct * (*ao)->speed;
				if ((*ao)->range_e.x < 0 || (*ao)->range_s.x > w_Width || (*ao)->range_e.y > 400 || (*ao)->range_s.y < 0) {
					(*ao)->check = true;
				}
			}
		}
		(*ao)->frameCount += 0.02;	// 투사체는 캐릭터의 frameCount와 별개니까 따로 생성했고, 속도는 캐릭터랑 똑같음
	}
}

void BSD::detectCollision(Champion &champion, float &enemyFrameCount) { // 여러분이 좋아하는 디텍트컬리젼
	float left = champion.getPosition().x - PIC_SIZE_X;
	float right = champion.getPosition().x;
	float top = champion.getPosition().y - PIC_SIZE_Y*2.0 / 8.0*7.0;
	float bottom = champion.getPosition().y;
	for (auto ao = attackObjList.begin(); ao != attackObjList.end(); ao++) {
		if (((*ao)->range_s.x < left && (*ao)->range_e.x > left) || ((*ao)->range_s.x < right && (*ao)->range_e.x > right)) {
			if (((*ao)->range_s.y < top && (*ao)->range_e.y > top) || ((*ao)->range_s.y < bottom && (*ao)->range_e.y > bottom)) {
				// 맞았음
				if ((*ao)->skillNumber == 0) {	// 평타 맞으면 다음과 같이 됨
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
				else if ((*ao)->skillNumber == 1) {  // 에너지 공격 맞으면 다음과 같이됨
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
				else if ((*ao)->skillNumber == 2) { // BSD 머리 맞으면 다음과 같이 됨
					if (champion.isBarrier())
					{
						if ((*ao)->hitcount == 0) 	(*ao)->check = true;				// 정해진 횟수만큼 HIT했을 경우 투사체 소멸
						else {
							if (enemyFrameCount > 1) {									// FrameCount가 1을 넘어가면 한 번 피격 체크
								(*ao)->hitcount--;										// 정해진 HIT 횟수 감소
								champion.setHp(champion.getHp() - (*ao)->damage*0.2);
								enemyFrameCount = 0;									// FrameCount 초기화
							}
							else	enemyFrameCount += 0.02;							// FrameCount 증가

							(*ao)->check = false;
						}
					}
					else {
						if ((*ao)->hitcount == 0) {										// 정해진 횟수만큼 HIT했을 경우 넉백시키며 소멸
							champion.isKnockBack = true;
							champion.vx = (*ao)->enemyDirect.x;
							champion.vy = (*ao)->enemyDirect.y;
							(*ao)->check = true;
						}
						else {
							if (enemyFrameCount > 2) {									// FrameCount가 2를 넘어가면 한 번 피격 체크
								(*ao)->hitcount--;										// 정해진 HIT 횟수 감소
								champion.setHp(champion.getHp() - (*ao)->damage);

								champion.vx = (*ao)->enemyDirect.x / 7.0;
								champion.vy = (*ao)->enemyDirect.y / 7.0;
								enemyFrameCount = 0;									// FrameCount 초기화

							}
							else	champion.isStun = true;								// FrameCount 도는 동안 스턴 상태
						}
					}
					if (champion.getHp() < 0) champion.setHp(0);
				}
				else if ((*ao)->skillNumber == 3) {  // BSD 펀치 다음과 같이 됨
					if ((*ao)->range_e.x - (*ao)->range_s.x < PIC_SIZE_X * 2.5)			// 피격 범위가 최대 범위를 초과하지 않을 시
					{
						if (champion.isBarrier()) {
							if ((*ao)->hitcount >= 0 && enemyFrameCount > 2)			// FrameCount가 2 이상이며 Hit 횟수가 남아있을 경우
							{
								enemyFrameCount = 0;									// FrameCount 초기화
								if ((*ao)->hitcount % 10 == 0)	champion.setHp(champion.getHp() - (*ao)->damage*0.2);
								(*ao)->hitcount--;										// Hit 횟수 감소
							}
							else enemyFrameCount += 0.02;
						}
						else {
							if ((*ao)->hitcount >= 0 && enemyFrameCount > 2) {			// FrameCount가 2 이상이며 Hit 횟수가 남아있을 경우
								enemyFrameCount = 0;
								if ((*ao)->hitcount % 10 == 0) {						// 0번째, 10번째, 20번째, 30번째 Hit일 경우
									champion.setHp(champion.getHp() - (*ao)->damage);
									champion.vx = (*ao)->enemyDirect.x / 10.0;
									champion.vy = (*ao)->enemyDirect.y / 10.0;
								}
								(*ao)->hitcount--;										// Hit 횟수 감소
							}
							else champion.isStun = true;								// 아닐 시 계속 스턴
						}
					}
					else if ((*ao)->range_e.x - (*ao)->range_s.x >= PIC_SIZE_X * 2.5)	// 피격 범위가 최대 범위를 초과할 시
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