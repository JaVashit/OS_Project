#include "Apache.hpp"

const int PIC_SIZE_X = 170;
const int PIC_SIZE_Y = 100;
int rangeX = (rand() % 10) - 5;
Apache::~Apache() { }

void Apache::useSkill(int skillnumber, int frameCount, Champion &c) { // 스킬 발동
	if (skillnumber == 0) {
		skill_NormalAttack(frameCount, c);
	}
	else if (skillnumber == 1) {
		skill_Assassination(frameCount,c);
	}
	else if (skillnumber == 2) {
		skill_Teleport(frameCount, c);
	}
	else if (skillnumber == 3) {
		skill_SpinAttack(frameCount, c);
	}
}

void Apache::skill_NormalAttack(int frameCount, Champion &c) { // 혹시나 다른거 할거 있을까봐 따로 빼냄
	calculateSpriteNormalAttack(frameCount, c);
}

void Apache::skill_SpinAttack(int frameCount, Champion &c) {
	calculateSpriteSpinAttack(frameCount, c);
}

void Apache::skill_Teleport(int frameCount, Champion &c) {
	calculateSpriteTeleport(frameCount, c);
}

void Apache::skill_Assassination(int frameCount, Champion &c) {
	calculateSpriteAssassination(frameCount, c);
}

void Apache::hit_KnockBack(int frameCount, Champion &c) {
	calculateSpriteKnockBack(frameCount, c);
}

void Apache::hit_stun(int frameCount, Champion &c) {
	calculateSpriteStun(frameCount, c);
}

void Apache::loadCharacter(sf::Sprite &player, Champion &c) {
	player.setTextureRect(sf::IntRect(c.getSpr().x, c.getSpr().y, PIC_SIZE_X, PIC_SIZE_Y));
	player.scale(2.0f, 2.0f);
	player.setOrigin(PIC_SIZE_X/2, PIC_SIZE_Y/2);
}

void Apache::calculateSpritePos(Champion &c) {
	c.setSpr(PIC_SIZE_X*0, 0);
}

void Apache::calculateSpriteNormalAttack(int frameCount, Champion &c) {  // 프레임 카운트는 float인데 int로 넘겨서 적당한 속도로 바뀌게 될거임 알아서 멋지게 꾸며주면됨
	if (frameCount == 0 || frameCount == 1) {
		c.setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 2);
	}
	else if (frameCount == 2 || frameCount == 3) {
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 2);
	}
	else if (frameCount == 4 || frameCount == 5) {
		c.setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 2);
	}
	else {
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 0);
	}
}

void Apache::calculateSpriteBlock(Champion &c) {
	c.setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 0);
}

void Apache::calculateSpriteSpinAttack(int frameCount, Champion &c) {
	if (frameCount == 0 || frameCount == 1) {
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 7);
		if (c.getFacing())
			c.setPosition(c.getPosition().x + 1, c.getPosition().y);
		else
			c.setPosition(c.getPosition().x - 1, c.getPosition().y);
	}
	else if (frameCount == 2 || frameCount == 3) {
		c.setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 7);
		if (c.getFacing())
			c.setPosition(c.getPosition().x + 1, c.getPosition().y);
		else
			c.setPosition(c.getPosition().x - 1, c.getPosition().y);
	}
	else if (frameCount == 4 || frameCount == 5) {
		c.setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 7);
		if (c.getFacing())
			c.setPosition(c.getPosition().x + 1, c.getPosition().y);
		else
			c.setPosition(c.getPosition().x - 1, c.getPosition().y);
	}
	else if (frameCount == 6 || frameCount == 7) {
		c.setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 7);
		if (c.getFacing())
			c.setPosition(c.getPosition().x + 1, c.getPosition().y);
		else
			c.setPosition(c.getPosition().x - 1, c.getPosition().y);
	}
	else if (frameCount == 8 || frameCount == 9) {
		c.setSpr(PIC_SIZE_X * 4, PIC_SIZE_Y * 7);
		if (c.getFacing())
			c.setPosition(c.getPosition().x + 1, c.getPosition().y);
		else
			c.setPosition(c.getPosition().x - 1, c.getPosition().y);
	}
	else if (frameCount == 10 || frameCount == 11) {
		c.setSpr(PIC_SIZE_X * 5, PIC_SIZE_Y * 7);
		if (c.getFacing())
			c.setPosition(c.getPosition().x + 1, c.getPosition().y);
		else
			c.setPosition(c.getPosition().x - 1, c.getPosition().y);
	}
	else {
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 0);
	}
}

void Apache::calculateSpriteTeleport(int frameCount, Champion &c) {

	if (frameCount == 0 || frameCount == 1) {
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 8);
		mApache.play();
	}
	else if (frameCount == 2 || frameCount == 3) {
		c.setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 8);
	}
	else if (frameCount == 4 || frameCount == 5) {
		c.setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 8);
		if (c.getFacing())
			c.setPosition(c.getPosition().x - rangeX, c.getPosition().y);
		else
			c.setPosition(c.getPosition().x + rangeX, c.getPosition().y);
	}
	else if (frameCount == 6 || frameCount == 7) {
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 8);
	}
	else if (frameCount == 8 || frameCount == 9) {
		c.setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 8);

	}
	else {
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 0);
		rangeX = (rand() % 10) - 5;
	}

}

void Apache::calculateSpriteAssassination(int frameCount, Champion &c) {
	if (frameCount == 0 || frameCount == 1) {
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 5);
	}
	else if (frameCount == 2 || frameCount == 3) {
		c.setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 5);
	}
	else if (frameCount == 4 || frameCount == 5) {
		c.setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 5);
		if (c.getFacing())
			c.setPosition(c.getPosition().x - 0.7, c.getPosition().y + 1);
		else
			c.setPosition(c.getPosition().x + 0.7, c.getPosition().y + 1);
	}
	else if (frameCount == 6 || frameCount == 7) {
		c.setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 5);
		if (c.getFacing())
			c.setPosition(c.getPosition().x - 1.3, c.getPosition().y + 1.7);
		else
			c.setPosition(c.getPosition().x + 1.3, c.getPosition().y + 1.7);
	}
	else if (frameCount == 8 || frameCount == 9) {
		c.setSpr(PIC_SIZE_X * 4, PIC_SIZE_Y * 5);
		if (c.getFacing())
			c.setPosition(c.getPosition().x - 0.8, c.getPosition().y - 1);
		else
			c.setPosition(c.getPosition().x + 0.8, c.getPosition().y - 1);
	}
	else if (frameCount == 10 || frameCount == 11) {
		c.setSpr(PIC_SIZE_X * 5, PIC_SIZE_Y * 5);
		if (c.getFacing())
			c.setPosition(c.getPosition().x - 0.5, c.getPosition().y - 1);
		else
			c.setPosition(c.getPosition().x + 0.5, c.getPosition().y - 1);
	}
	else if (frameCount == 13 || frameCount == 14) {
		c.setSpr(PIC_SIZE_X * 6, PIC_SIZE_Y * 5);
		if (c.getFacing())
			if (c.getFacing())
				c.setPosition(c.getPosition().x , c.getPosition().y - 0.7);
			else
				c.setPosition(c.getPosition().x , c.getPosition().y - 0.7);
	}
	else {
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 0);
	}
}

void Apache::calculateSpriteKnockBack(int frameCount, Champion &c) {
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

void Apache::calculateSpriteStun(int frameCount, Champion &c) {
	if (frameCount < 2) {
		c.setSpr(PIC_SIZE_X * 6, PIC_SIZE_Y * 0);
	}
	else if (frameCount < 4) {
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 1);
	}
}

void Apache::setSkillNumber(int skillNumber) {
	this->skillNumber = skillNumber;
}

int Apache::getSkillNumber() {
	return skillNumber;
}

int Apache::getSkillFrameTotal() {
	return skillFrame[skillNumber];
}

int Apache::getCanUseSkillCount(int skillNumber) {
	return canUseSkillCount[skillNumber];
}

void Apache::setCanUseSkillCount(int skillNumber, int maxCount) {
	canUseSkillCount[skillNumber] = maxCount;
}

void Apache::updateAOList(Champion &c) {
	for (auto ao = c.attackObjList.begin(); ao != c.attackObjList.end(); ao++) {
		if ((*ao)->isthrow == false) {								// 투사체가 아닌 것들
			if ((*ao)->skillNumber == 0) {							// 0,1,2번 스킬은 다음과 같이 설정 (캐릭터 따라서 움직여야 하기 때문에)
				if (c.getFacing()) {
					(*ao)->range_s = sf::Vector2f(c.getPosition().x - PIC_SIZE_X / 4, c.getPosition().y - PIC_SIZE_Y * 2);
					(*ao)->range_e = sf::Vector2f(c.getPosition().x + PIC_SIZE_X / 2, c.getPosition().y);
				}
				else {
					(*ao)->range_s = sf::Vector2f(c.getPosition().x - PIC_SIZE_X / 2 - PIC_SIZE_X / 4 * 3, c.getPosition().y - PIC_SIZE_Y * 2);
					(*ao)->range_e = sf::Vector2f(c.getPosition().x + PIC_SIZE_X / 4 - PIC_SIZE_X / 4 * 3, c.getPosition().y);
				}
			}
			else if ((*ao)->skillNumber == 1) {
				if (c.getFacing()) {
					(*ao)->range_s = sf::Vector2f(c.getPosition().x - PIC_SIZE_X / 4, c.getPosition().y - PIC_SIZE_Y * 2);
					(*ao)->range_e = sf::Vector2f(c.getPosition().x + PIC_SIZE_X / 2, c.getPosition().y);
					(*ao)->enemyDirect = sf:: Vector2f(5, 0);
				}
				else {
					(*ao)->range_s = sf::Vector2f(c.getPosition().x - PIC_SIZE_X / 2 - PIC_SIZE_X / 4 * 3, c.getPosition().y - PIC_SIZE_Y * 2);
					(*ao)->range_e = sf::Vector2f(c.getPosition().x + PIC_SIZE_X / 4 - PIC_SIZE_X / 4 * 3, c.getPosition().y);
					(*ao)->enemyDirect = sf::Vector2f(5, 0);
				}
			}
			else if ((*ao)->skillNumber == 2) {
				if (c.getFacing()) {
					(*ao)->range_s = sf::Vector2f(c.getPosition().x - PIC_SIZE_X / 4, c.getPosition().y - PIC_SIZE_Y * 2);
					(*ao)->range_e = sf::Vector2f(c.getPosition().x + PIC_SIZE_X / 2, c.getPosition().y);
					(*ao)->enemyDirect = sf::Vector2f(5, 0);
				}
				else {
					(*ao)->range_s = sf::Vector2f(c.getPosition().x - PIC_SIZE_X / 2 - PIC_SIZE_X / 4 * 3, c.getPosition().y - PIC_SIZE_Y * 2);
					(*ao)->range_e = sf::Vector2f(c.getPosition().x + PIC_SIZE_X / 4 - PIC_SIZE_X / 4 * 3, c.getPosition().y);
					(*ao)->enemyDirect = sf::Vector2f(-5, 0);
				}
			}
			else if ((*ao)->skillNumber == 3) {
				if (c.getFacing()) {
					(*ao)->range_s = sf::Vector2f(c.getPosition().x - PIC_SIZE_X / 4, c.getPosition().y - PIC_SIZE_Y * 2);
					(*ao)->range_e = sf::Vector2f(c.getPosition().x + PIC_SIZE_X / 2, c.getPosition().y);
				}
				else {
					(*ao)->range_s = sf::Vector2f(c.getPosition().x - PIC_SIZE_X / 2 - PIC_SIZE_X / 4 * 3, c.getPosition().y - PIC_SIZE_Y * 2);
					(*ao)->range_e = sf::Vector2f(c.getPosition().x + PIC_SIZE_X / 4 - PIC_SIZE_X / 4 * 3, c.getPosition().y);
				}
			}
			if (!c.isAttacking())						// 투사체가 아니기 때문에 공격이 끝나면 알아서 삭제 시켜야 함
				(*ao)->check = true;
		}

		(*ao)->frameCount += 0.02;	// 투사체는 캐릭터의 frameCount와 별개니까 따로 생성했고, 속도는 캐릭터랑 똑같음
	}
}

void Apache::detectCollision(class Champion &champion, std::list<struct AttackObject*> &aoList, std::list<struct hitImage*> &hitList, float &enemyFrameCount, int time) { // 여러분이 좋아하는 디텍트컬리젼
	float left = champion.getPosition().x - PIC_SIZE_X / 4.0*3.0;
	float right = champion.getPosition().x;
	float top = champion.getPosition().y - PIC_SIZE_Y*2.0 / 8.0*7.0;
	float bottom = champion.getPosition().y;
	for (auto ao = aoList.begin(); ao != aoList.end(); ao++) {
		if (((*ao)->range_s.x < left && (*ao)->range_e.x > left) || ((*ao)->range_s.x < right && (*ao)->range_e.x > right)) {
			if (((*ao)->range_s.y < top && (*ao)->range_e.y > top) || ((*ao)->range_s.y < bottom && (*ao)->range_e.y > bottom)) {
				// 맞았음
				if ((*ao)->skillNumber == 0) {	// 평타 맞으면 다음과 같이 됨
					hitImage* hit = new hitImage(champion.getPosition());
					hitList.push_back(hit);
					(*ao)->check = true;
					if (champion.isBarrier()) champion.setHp(champion.getHp() - (*ao)->damage*0.2);
					else {
						attackApache.play();
						champion.isKnockBack = true;
						enemyFrameCount = 0;
						champion.setHp(champion.getHp() - (*ao)->damage);
						champion.vx = (*ao)->enemyDirect.x;
						champion.vy = (*ao)->enemyDirect.y;
					}
					if (champion.getHp() < 0) champion.setHp(0);
				}
				else if ((*ao)->skillNumber == 1) {  // 최후의일격 맞으면 다음과 같이됨
					(*ao)->check = true;
					hitImage* hit = new hitImage(champion.getPosition());
					hitList.push_back(hit);
					if (champion.isBarrier()) champion.setHp(champion.getHp() - (*ao)->damage*0.2);
					else {
						attack2Apache.play();
						champion.isKnockBack = true;
						enemyFrameCount = 0;
						champion.setHp(champion.getHp() - (*ao)->damage);
						champion.vx = (*ao)->enemyDirect.x;
						champion.vy = (*ao)->enemyDirect.y;
					}
					if (champion.getHp() < 0) champion.setHp(0);
				}
				else if ((*ao)->skillNumber == 3) { // 바람의 상처 맞으면 다음과 같이 됨
					(*ao)->check = true;
					hitImage* hit = new hitImage(champion.getPosition());
					hitList.push_back(hit);
					if (champion.isBarrier()) champion.setHp(champion.getHp() - (*ao)->damage*0.2);
					else {
						finalApache.play();
						champion.isKnockBack = true;
						enemyFrameCount = 0;
						champion.setHp(champion.getHp() - (*ao)->damage);
						champion.vx = (*ao)->enemyDirect.x;
						champion.vy = (*ao)->enemyDirect.y;
					}
					if (champion.getHp() < 0) champion.setHp(0);
				}
			}
		}
	}

};