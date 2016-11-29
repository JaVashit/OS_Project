#include "Jang.h"

const int PIC_SIZE_X = 170; // 스프라이트 이미지 가로 크기
const int PIC_SIZE_Y = 100; // 스프라이트 이미지 세로 크기

Jang::~Jang(){ }

// 스킬 사용 시 스킬 번호 넘겨주는 함수
void Jang::useSkill(int skillnumber, int frameCount, Champion &c){
	if(skillnumber == 0){
		skill_NormalAttack(frameCount, c); // 일반 공격 'Q' 버튼
	}
	else if(skillnumber == 1){
		skill_RotateKick(frameCount, c); // 특수 공격 '1' 버튼
	}
	else if(skillnumber == 2){
		skill_doubleComboAttack(frameCount, c); // 특수 공격 '2' 버튼
	}
	else if(skillnumber == 3){
		skill_SpecialAttack(frameCount, c); // 특수 공격 '3' 버튼 -> 다른 함수에서 사용
	}
}

/* 공격 리스트 */
void Jang::skill_NormalAttack(int frameCount, Champion &c){
	calculateSpriteNormalAttack(frameCount, c);			// 일반 공격 스프라이트 작동
}

void Jang::skill_RotateKick(int frameCount, Champion &c){
	calculateSpriteRotateKick(frameCount, c);			// 특수 공격 1 스프라이트 작동
}

void Jang::skill_doubleComboAttack(int frameCount, Champion &c){
	calculateSpritedoubleComboAttack(frameCount, c);	// 특수 공격 2 스프라이트 작동
}

void Jang::skill_SpecialAttack(int frameCount, Champion &c){
	// 다른 함수에서 사용
}

// 공격 판정 시 넉백 효과
void Jang::hit_KnockBack(int frameCount, Champion &c){
	calculateSpriteKnockBack(frameCount, c);			// 넉백 시 스프라이트 작동
}

// 공격 판정 시 스턴 효과
void Jang::hit_stun(int frameCount, Champion &c){
	calculateSpriteStun(frameCount, c);					// 스턴 시 스프라이트 작동
}

// 캐릭터 스프라이트 불러오는 부분
void Jang::loadCharacter(sf::Sprite &player, Champion &c){
	player.setTextureRect(sf::IntRect(c.getSpr().x, c.getSpr().y,PIC_SIZE_X,PIC_SIZE_Y));	// 텍스쳐를 그려줄 부분의 크기를 지정
	player.scale(2.0f, 2.0f);	// 플레이어의 크기를 2배 증가
	player.setOrigin(PIC_SIZE_X/2,PIC_SIZE_Y/2);	// 원점을 스프라이트 중앙으로 지정
}

// 캐릭터 스프라이트의 위치 계산하는 부분
void Jang::calculateSpritePos(Champion &c){
	c.setSpr(PIC_SIZE_X*0, 0);
}

// 일반 공격 'Q' 버튼 선택 시 실행
void Jang::calculateSpriteNormalAttack(int frameCount, Champion &c){
	if(frameCount == 0 || frameCount == 1)
		c.setSpr(PIC_SIZE_X * 4, PIC_SIZE_Y * 0);
	else if(frameCount == 2 || frameCount == 3)
		c.setSpr(PIC_SIZE_X * 5, PIC_SIZE_Y * 0);
	else if(frameCount == 4 || frameCount == 5)
		c.setSpr(PIC_SIZE_X * 4, PIC_SIZE_Y * 0);
	else
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 0); // 대기 상태	
}

// 방어 'S' 버튼 선택 시 실행
void Jang::calculateSpriteBlock(Champion &c){
	c.setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 0);
}

// 특수 공격 '1' 버튼 클릭 시 나오는 기술
void Jang::calculateSpriteRotateKick(int frameCount, Champion &c){
	if(frameCount == 0 || frameCount == 1)
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 3);	
	else if(frameCount == 2 || frameCount == 3)
		c.setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 3);
	else if(frameCount == 4 || frameCount == 5)
		c.setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 3);
	else if(frameCount == 6 || frameCount == 7)
		c.setSpr(PIC_SIZE_X * 4, PIC_SIZE_Y * 3);
	else if(frameCount == 8 || frameCount == 9)
		c.setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 3);
	else if(frameCount == 10 || frameCount == 11)
		c.setSpr(PIC_SIZE_X * 6, PIC_SIZE_Y * 3);
	else if(frameCount == 12 || frameCount == 13)
	{
		c.setSpr(PIC_SIZE_X * 7, PIC_SIZE_Y * 3);
	}
	else
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 0);	
}

// 특수 공격 '2' 버튼 클릭 시 나오는 기술
void Jang::calculateSpritedoubleComboAttack(int frameCount, Champion &c){
	if(frameCount == 0)
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 5);
	else if(frameCount == 1)
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 4);
	else if(frameCount == 2)
		c.setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 4);
	else if(frameCount == 3)
		c.setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 4);
	else if(frameCount == 4){
		c.setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 4);
		c.setPosition(c.getPosition().x, c.getPosition().y-1.0);
	}
	else if(frameCount == 5){
		c.setSpr(PIC_SIZE_X * 4, PIC_SIZE_Y * 4);
		c.setPosition(c.getPosition().x, c.getPosition().y-0.6);
	}
	else if(frameCount == 6){
		c.setSpr(PIC_SIZE_X * 5, PIC_SIZE_Y * 4);
		c.setPosition(c.getPosition().x, c.getPosition().y-0.4);
	}
	else if(frameCount == 7){
		c.setSpr(PIC_SIZE_X * 6, PIC_SIZE_Y * 4);
		c.setPosition(c.getPosition().x, c.getPosition().y);
	}
	else if(frameCount == 8){
		c.setSpr(PIC_SIZE_X * 6, PIC_SIZE_Y * 4);
		c.setPosition(c.getPosition().x, c.getPosition().y+1.0);
	}
	else if(frameCount == 9){
		c.setSpr(PIC_SIZE_X * 6, PIC_SIZE_Y * 4);
		c.setPosition(c.getPosition().x, c.getPosition().y+1.0);
	}
	else if(frameCount == 10)
		c.setSpr(PIC_SIZE_X * 5, PIC_SIZE_Y * 4);
	else if(frameCount == 11)
		c.setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 4);
	else if(frameCount == 12)
		c.setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 4);
	else if(frameCount == 13)
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 5);
	else if(frameCount == 14)
		c.setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 5);
	else if(frameCount == 15){
		c.setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 5);
		if(c.getFacing())
			c.setPosition(c.getPosition().x+1, c.getPosition().y);
		else
			c.setPosition(c.getPosition().x-1, c.getPosition().y);
	}
	else if(frameCount == 16){
		c.setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 5);
		if(c.getFacing())
			c.setPosition(c.getPosition().x+1, c.getPosition().y);
		else
			c.setPosition(c.getPosition().x-1, c.getPosition().y);
	}
	else if(frameCount == 17){
		c.setSpr(PIC_SIZE_X * 4, PIC_SIZE_Y * 5);
		if(c.getFacing())
			c.setPosition(c.getPosition().x+1, c.getPosition().y);
		else
			c.setPosition(c.getPosition().x-1, c.getPosition().y);
	}
	else if(frameCount == 18){
		c.setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 5);
		if(c.getFacing())
			c.setPosition(c.getPosition().x+1, c.getPosition().y);
		else
			c.setPosition(c.getPosition().x-1, c.getPosition().y);
	}
	else if(frameCount == 19){
		c.setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 5);
		if(c.getFacing())
			c.setPosition(c.getPosition().x+1, c.getPosition().y);
		else
			c.setPosition(c.getPosition().x-1, c.getPosition().y);
	}
	else if(frameCount == 20)
		c.setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 5);
	else if(frameCount == 21)
	{
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 5);
	}
	else
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 0);
}

// 특수 공격 '3' 버튼 클릭 시 나오는 기술
void Jang::calculateSpriteSpecialAttack(int frameCount, Champion &c){
	// 다른 함수에서 사용
}

// 넉백 표현
void Jang::calculateSpriteKnockBack(int frameCount, Champion &c){
	if(frameCount < 2)
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 1);
	else 
		c.setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 1);
}

// 데미지를 입었을 경우
void Jang::calculateSpriteStun(int frameCount, Champion &c){
	if(frameCount < 1){
		c.setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 0);	
	}
	else if(frameCount < 2){
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 0);
	}
}

// 스킬 번호 보내주기
void Jang::setSkillNumber(int skillNumber){
	this->skillNumber = skillNumber;
}

// 스킬 번호 가져오기
int Jang::getSkillNumber(){
	return skillNumber;
}

// 스킬 고유의 총 프레임을 가져오기
int Jang::getSkillFrameTotal(){
	return skillFrame[skillNumber];
}

// 사용 가능한 스킬 횟수를 세준다
int Jang::getCanUseSkillCount(int skillNumber){
	return canUseSkillCount[skillNumber];
}

// 리스트를 계속 업데이트 해주는 함수
void Jang::updateAOList(Champion &c, bool sound){
	for(auto ao = c.attackObjList.begin(); ao != c.attackObjList.end(); ao++){
		if((*ao)->isthrow == false){								// 투사체가 아닌 것들
			if((*ao)->skillNumber == 0){							// 0,1,2번 스킬은 다음과 같이 설정 (캐릭터 따라서 움직여야 하기 때문에)
				if(c.getFacing()){ // 스프라이트가 바라보는 방향으로 시작 점과 끝점을 정해준다.
					(*ao)->range_s = sf::Vector2f(c.getPosition().x-PIC_SIZE_X/4, c.getPosition().y-PIC_SIZE_Y*2);
					(*ao)->range_e = sf::Vector2f(c.getPosition().x+PIC_SIZE_X/2, c.getPosition().y);
				}
				else{
					(*ao)->range_s = sf::Vector2f(c.getPosition().x-PIC_SIZE_X/2-PIC_SIZE_X/4*3, c.getPosition().y-PIC_SIZE_Y*2);
					(*ao)->range_e = sf::Vector2f(c.getPosition().x+PIC_SIZE_X/4-PIC_SIZE_X/4*3, c.getPosition().y);
				}
			}
			else if((*ao)->skillNumber == 1){
				if(c.getFacing()){
					(*ao)->range_s = sf::Vector2f(c.getPosition().x-PIC_SIZE_X/4, c.getPosition().y-PIC_SIZE_Y*2);
					(*ao)->range_e = sf::Vector2f(c.getPosition().x+PIC_SIZE_X/4, c.getPosition().y);
				}
				else{
					(*ao)->range_s = sf::Vector2f(c.getPosition().x-PIC_SIZE_X/2-PIC_SIZE_X/4*3, c.getPosition().y-PIC_SIZE_Y*2);
					(*ao)->range_e = sf::Vector2f(c.getPosition().x+PIC_SIZE_X/4-PIC_SIZE_X/4*3, c.getPosition().y);
				}
			}
			else if((*ao)->skillNumber == 2){
				if(c.getFacing()){
					(*ao)->range_s = sf::Vector2f(c.getPosition().x-PIC_SIZE_X/4, c.getPosition().y-PIC_SIZE_Y*2);
					(*ao)->range_e = sf::Vector2f(c.getPosition().x+PIC_SIZE_X/2, c.getPosition().y);
					(*ao)->enemyDirect = sf::Vector2f(5, 0);
				}
				else{
					(*ao)->range_s = sf::Vector2f(c.getPosition().x-PIC_SIZE_X/2-PIC_SIZE_X/4*3, c.getPosition().y-PIC_SIZE_Y*2);
					(*ao)->range_e = sf::Vector2f(c.getPosition().x+PIC_SIZE_X/4-PIC_SIZE_X/4*3, c.getPosition().y);
					(*ao)->enemyDirect = sf::Vector2f(-5, 0);
				}
			}
			if(!c.isAttacking())	// 투사체가 아니기 때문에 공격이 끝나면 알아서 삭제 시켜야 함
				(*ao)->check = true;
		}
		else{
			if((*ao)->skillNumber == 3){			// 특수 공격 스프라이트
				if((*ao)->frameCount < 2){
					mJang.openFromFile("./SE/SteadyDamage.ogg");
					if(sound) mJang.play();
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 1, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 4){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 2, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 6){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 3, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 8){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 1, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 10){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 2, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 12){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 3, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 14){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 1, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 16){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 2, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 18){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 3, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 20){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 1, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 22){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 2, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 24){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 3, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 26){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 1, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 28){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 2, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 30){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 3, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 32){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 1, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 34){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 2, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 36){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 3, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 38){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 1, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 40){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 2, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 42){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 3, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 44){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 1, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 46){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 2, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 48){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 3, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 50){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 1, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 52){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 2, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 54){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 3, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 56){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 1, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 58){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 2, PIC_SIZE_Y * 6);
				}
				else{
					(*ao)->check = true;
				}
				(*ao)->obj.setTextureRect(sf::IntRect((*ao)->objSpr.x, (*ao)->objSpr.y,PIC_SIZE_X,PIC_SIZE_Y));
				(*ao)->obj.setPosition(c.w_Width/2, c.w_Height/2+200);
			}
			else{
				(*ao)->range_s += (*ao)->direct * (*ao)->speed;	
				(*ao)->range_e += (*ao)->direct * (*ao)->speed;
				if((*ao)->range_e.x < 0 || (*ao)->range_s.x > c.w_Width || (*ao)->range_e.y > 400 || (*ao)->range_s.y < 0){
					(*ao)->check = true;
				}
			}
		}
		(*ao)->frameCount += 0.02;	// 투사체는 캐릭터의 frameCount와 별개니까 따로 생성했고, 속도는 캐릭터랑 똑같음
	}
}

// 충돌처리
void Jang::detectCollision(class Champion &champion, std::list<struct AttackObject*> &aoList, std::list<struct hitImage*> &hitList, float &enemyFrameCount, int time, bool sound){ 
	float left		= champion.getPosition().x - PIC_SIZE_X/4.0*3.0;
	float right		= champion.getPosition().x;
	float top		= champion.getPosition().y - PIC_SIZE_Y*2.0/8.0*7.0;
	float bottom	= champion.getPosition().y;
	for(auto ao = aoList.begin(); ao!=aoList.end(); ao++){
		if(((*ao)->range_s.x < left && (*ao)->range_e.x > left) || ((*ao)->range_s.x < right && (*ao)->range_e.x > right)){ // 좌우 충돌
			if(((*ao)->range_s.y < top && (*ao)->range_e.y > top) || ((*ao)->range_s.y < bottom && (*ao)->range_e.y > bottom)){ // 상하 충돌
				if((*ao)->skillNumber == 0){	// 일반 공격을 맞았을 경우
					hitImage* hit = new hitImage(champion.getPosition());
					hitList.push_back(hit);
					(*ao)->check = true;
					if(champion.isBarrier()) champion.setHp(champion.getHp()-(*ao)->damage*0.2); // 방어 시 데미지
					else{
						mJang.openFromFile("./SE/Attack1.ogg");	// 효과음 선택
						if(sound) mJang.play();					// 효과음 재생
						champion.isKnockBack = true; // 넉백이 된다
						enemyFrameCount = 0;
						champion.setHp(champion.getHp()-(*ao)->damage);
						champion.vx = (*ao)->enemyDirect.x;	// 적의 좌표를 이동 시킨다 -> 넉백 또는 스턴
						champion.vy = (*ao)->enemyDirect.y;
					}
					if(champion.getHp() < 0) champion.setHp(0);
				}
				else if((*ao)->skillNumber == 1){  // 특수 공격 1을 맞았을 경우
					(*ao)->check = true;
					hitImage* hit = new hitImage(champion.getPosition());
					hitList.push_back(hit);
					if(champion.isBarrier()) champion.setHp(champion.getHp()-(*ao)->damage*0.2);
					else{
						mJang.openFromFile("./SE/Attack2.ogg");
						if(sound) mJang.play();
						champion.isKnockBack = true;
						enemyFrameCount = 0;
						champion.setHp(champion.getHp()-(*ao)->damage);
						champion.vx = (*ao)->enemyDirect.x;
						champion.vy = (*ao)->enemyDirect.y;
					}
					if(champion.getHp() < 0) champion.setHp(0);
				}
				else if((*ao)->skillNumber == 2){ // 특수 공격 2를 맞았을 경우
					(*ao)->check = false;
					if(time%80==0){
						hitImage* hit = new hitImage(champion.getPosition());
						hitList.push_back(hit);
					}
					if(champion.isBarrier()) champion.setHp(champion.getHp()-(*ao)->damage*0.2);
					else{ 
						champion.isStun = true;
						enemyFrameCount = 0;
						champion.setHp(champion.getHp()-(*ao)->damage);
					}
					if(champion.getHp() < 0) champion.setHp(0);
				}
				else if((*ao)->skillNumber == 3){  // 궁극기를 맞았을 경우
					int ran = rand()%30;
					int ran2 = rand()%30;
					if(time%80==0){
						hitImage* hit = new hitImage(champion.getPosition());
						hitList.push_back(hit);
					}
					if(champion.isBarrier()) champion.setHp(champion.getHp()-(*ao)->damage*0.2); // 데미지를 서서히 감소시킨다
					else{ 
						champion.isStun = true;
						enemyFrameCount = 0;
						champion.setHp(champion.getHp()-(*ao)->damage);	// 데미지를 서서히 감소시킨다
					}
					sf::Vector2f direct = sf::Vector2f(champion.w_Width/2+(ran-15) - champion.getPosition().x, champion.w_Height/2+(ran2-15) - champion.getPosition().y);
					champion.setPosition(champion.getPosition().x + direct.x * champion.getSpeed()/8, champion.getPosition().y + direct.y * champion.getSpeed());
					if(champion.getHp() < 0) champion.setHp(0);
				}
			}
		}
	}

};

void Jang::setCanUseSkillCount(int skillNumber, int maxCount) {
	canUseSkillCount[skillNumber] = maxCount;
}