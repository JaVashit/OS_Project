#include "LGPL.hpp"

const int PIC_SIZE_X = 170;
const int PIC_SIZE_Y = 100;
const int ENERGY_SIZE_X = 85;
const int ENERGY_SIZE_Y = 40;

LGPL::~LGPL() { }

void LGPL::useSkill(int skillnumber, int frameCount, Champion &c) { // 스킬 발동
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

void LGPL::skill_NormalAttack(int frameCount, Champion &c) { // 혹시나 다른거 할거 있을까봐 따로 빼냄
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

void LGPL::calculateSpriteNormalAttack(int frameCount, Champion &c) {  // 프레임 카운트는 float인데 int로 넘겨서 적당한 속도로 바뀌게 될거임 알아서 멋지게 꾸며주면됨
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

void LGPL::calculateSpriteMagnetic(int frameCount, Champion &c) {  // 프레임 카운트는 float인데 int로 넘겨서 적당한 속도로 바뀌게 될거임 알아서 멋지게 꾸며주면됨
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
		if ((*ao)->isthrow == false) {								// 투사체가 아닌 것들
			
		}
		else {																			// 투사체들
			if ((*ao)->skillNumber == 0) {												// 1번 스킬
				(*ao)->range_s += (*ao)->direct * (*ao)->speed;							// 피격 범위 변경
				(*ao)->range_e += (*ao)->direct * (*ao)->speed;
				(*ao)->obj.setPosition((*ao)->range_s);									// 투사체 위치를 피격 범위에 맞춰 조정
				if ((*ao)->range_e.x < 0 || (*ao)->range_s.x > c.w_Width || (*ao)->range_e.y > 400 || (*ao)->range_s.y < 0) {	//화면 밖으로 나갈 시
					(*ao)->check = true;
				}

			}
			if ((*ao)->skillNumber == 1) {												// 2번 스킬은 1번 스킬과 동일
				(*ao)->range_s += (*ao)->direct * (*ao)->speed;
				(*ao)->range_e += (*ao)->direct * (*ao)->speed;
				(*ao)->obj.setPosition((*ao)->range_s);
				if ((*ao)->range_e.x < 0 || (*ao)->range_s.x > c.w_Width-200 || (*ao)->range_e.y > 400 || (*ao)->range_s.y < 0) {
					(*ao)->check = true;
				}
			}    
			if ((*ao)->skillNumber == 2) {												// 2번 스킬은 1번 스킬과 동일
				(*ao)->range_s += (*ao)->direct * (*ao)->speed;
				(*ao)->range_e += (*ao)->direct * (*ao)->speed;
				(*ao)->obj.setPosition((*ao)->range_s);
				if ((*ao)->range_e.x < 0 || (*ao)->range_s.x > c.w_Width-200 || (*ao)->range_e.y > 400 || (*ao)->range_s.y < 0) {
					(*ao)->check = true;
				}
			}  
			if ((*ao)->skillNumber == 3) {												// 2번 스킬은 1번 스킬과 동일
				(*ao)->range_s += (*ao)->direct * (*ao)->speed ;
				(*ao)->range_e += (*ao)->direct * (*ao)->speed;
				(*ao)->obj.setPosition((*ao)->range_s);
				if ((*ao)->range_e.x < 0 || (*ao)->range_s.x > c.w_Width-200 || (*ao)->range_e.y > 400 || (*ao)->range_s.y < 0) {
					(*ao)->check = true;
				}
			}      
		}
		(*ao)->frameCount += 0.2;	// 투사체는 캐릭터의 frameCount와 별개니까 따로 생성했고, 속도는 캐릭터랑 똑같음
	}
}

void LGPL::detectCollision(Champion &champion, std::list<AttackObject*> &aoList, float &enemyFrameCount) { // 여러분이 좋아하는 디텍트컬리젼
	float left = champion.getPosition().x - PIC_SIZE_X;
	float right = champion.getPosition().x;
	float top = champion.getPosition().y - PIC_SIZE_Y*2.0 / 8.0*7.0;
	float bottom = champion.getPosition().y;
	for (auto ao = aoList.begin(); ao != aoList.end(); ao++) {
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
				else if ((*ao)->skillNumber == 2 ||(*ao)->skillNumber == 3) { // LGPL 머리 맞으면 다음과 같이 됨
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
			}
		}
	}
};