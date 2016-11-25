#include "Jang.h"

const int PIC_SIZE_X = 170;
const int PIC_SIZE_Y = 100;

Jang::~Jang(){ }

// 스킬 사용 시 스킬 번호 넘겨주는 함수
void Jang::useSkill(int skillnumber, int frameCount){
	if(skillnumber == 0){
		skill_NormalAttack(frameCount); // 일반 공격 'Q' 버튼
	}
	else if(skillnumber == 1 && bSkill[0]){
		skill_RotateKick(frameCount); // 특수 공격 '1' 버튼
	}
	else if(skillnumber == 2 && bSkill[1]){
		skill_doubleComboAttack(frameCount); // 특수 공격 '2' 버튼
	}
	else if(skillnumber == 3 && bSkill[2]){
		skill_SpecialAttack(frameCount); // 특수 공격 '3' 버튼 -> 다른 함수에서 사용
	}
	else if(skillnumber == 4){
		skill_Dash(frameCount); // 대시 공격 없음
	}
}

// 공격 판정 시 효과 지속이 얼마나 되며, 몇 프레임 단위로 상태가 변하는 지 결정
void Jang::crowdControlHit(float &frameCount){
	if(this->isStun){
		hit_stun((int)frameCount);
		frameCount+=0.001;
		if(frameCount>4) this->isStun = false;
	}
	else if(this->isKnockBack){
		hit_KnockBack((int)frameCount);
		frameCount+=0.001;
		if(frameCount>20) this->isKnockBack = false;
	}
}

// 공격에 대한 기본 정보의 리스트
void Jang::insertAOList(int skillNumber){
	if(skillNumber == 0){					//일반 공격 'Q' 초기 설정
		AttackObject* ao = new AttackObject(skillNumber, 10, 1);
		ao->damage = 3;					// 일반 공격 데미지 10으로 초기화
		ao->check = false;					// 공격 판정 확인
		ao->direct = sf::Vector2f(0,0);		// 현재 방향에 대한 초기화
		ao->isthrow = false;				// 투사체(장거리 공격)에 대한 것 초기화
		if(this->getFacing()){				// 우측을 바라보고 있는 상태
			ao->range_s = sf::Vector2f(this->getPosition().x-PIC_SIZE_X/4, this->getPosition().y-PIC_SIZE_Y*2); // 시작 좌표 설정
			ao->range_e = sf::Vector2f(this->getPosition().x+PIC_SIZE_X/2, this->getPosition().y);				// 끝 좌표 설정
			ao->enemyDirect = sf::Vector2f(0.2, -1);	// 적 넉백 시 위치 벡터
		}
		else{	// 왼쪽을 바라보는 상태
			ao->range_s = sf::Vector2f(this->getPosition().x-PIC_SIZE_X/2-PIC_SIZE_X/4*3, this->getPosition().y-PIC_SIZE_Y*2);
			ao->range_e = sf::Vector2f(this->getPosition().x+PIC_SIZE_X/4-PIC_SIZE_X/4*3, this->getPosition().y);
			ao->enemyDirect = sf::Vector2f(-0.2, -1);
		}
		attackObjList.push_back(ao);		// 초기화 후 리스트에 입력
	}
	else if(skillNumber == 1){				// 특수 공격 '1' 초기 설정
		AttackObject* ao = new AttackObject(skillNumber, 20, 1);
		ao->damage = 10;
		ao->check = false;
		ao->direct = sf::Vector2f(0,0);
		ao->isthrow = false;
		if(this->getFacing()){
			ao->range_s = sf::Vector2f(this->getPosition().x-PIC_SIZE_X/3, this->getPosition().y-PIC_SIZE_Y);
			ao->range_e = sf::Vector2f(this->getPosition().x-PIC_SIZE_X/3+PIC_SIZE_X, this->getPosition().y-PIC_SIZE_Y/4);
			ao->enemyDirect = sf::Vector2f(0.2, -1);
		}
		else{
			ao->range_s = sf::Vector2f(this->getPosition().x-PIC_SIZE_X+PIC_SIZE_X/3-PIC_SIZE_X, this->getPosition().y-PIC_SIZE_Y);
			ao->range_e = sf::Vector2f(this->getPosition().x-PIC_SIZE_X+PIC_SIZE_X/3, this->getPosition().y-PIC_SIZE_Y/4);
			ao->enemyDirect = sf::Vector2f(-0.2, -1);
		}
		attackObjList.push_back(ao);
	}
	else if(skillNumber == 2){				// 특수 공격 '2' 초기 설정
		AttackObject* ao = new AttackObject(skillNumber, 0.02, 1);
		ao->damage = 0.02;
		ao->check = false;
		ao->direct = sf::Vector2f(0,0);
		ao->isthrow = false;
		if(this->getFacing()){
			ao->range_s = sf::Vector2f(this->getPosition().x-PIC_SIZE_X/4, this->getPosition().y-PIC_SIZE_Y*2);
			ao->range_e = sf::Vector2f(this->getPosition().x+PIC_SIZE_X/2, this->getPosition().y);
			ao->enemyDirect = sf::Vector2f(1, -1);
		}
		else{
			ao->range_s = sf::Vector2f(this->getPosition().x-PIC_SIZE_X/2-PIC_SIZE_X/4*3, this->getPosition().y-PIC_SIZE_Y*2);
			ao->range_e = sf::Vector2f(this->getPosition().x+PIC_SIZE_X/4-PIC_SIZE_X/4*3, this->getPosition().y);
			ao->enemyDirect = sf::Vector2f(-1, -1);
		}
		attackObjList.push_back(ao);
	}
	else if(skillNumber == 3){			// 특수 공격 '3' 이미지를 입혀야 하기 때문에 특별히 따로 이미지 설정
		AttackObject* ao = new AttackObject(skillNumber, 0, 0);
		if (!ao->throwTexture.loadFromFile("./images/character/Jang_sprite.png")) printf( "Error loading vx_characters\n");	// 해당 이미지 불러오기
		ao->objSpr = sf::Vector2f(PIC_SIZE_X * 0, PIC_SIZE_Y * 6);															// 스프라이트 작성
		ao->obj.setTexture(ao->throwTexture);																				// 텍스쳐(스프라이트) 설정
		ao->obj.setTextureRect(sf::IntRect(ao->objSpr.x, ao->objSpr.y,170,200));											// 텍스쳐(스프라이트)의 크기와 좌표를 설정
		ao->obj.scale(4.0f, 4.0f);																							// 텍스쳐(스프라이트)의 크기 설정
		ao->obj.setOrigin(85,100);																							// 스프라이트의 중심이 중앙에 위치하도록 설정
		ao->obj.setPosition(w_Width/2, w_Height/2);																			// 스프라이트의 포지션 설정
		ao->damage = 0.003;																										// 데미지 상태는 없음
		ao->check = false;																									// 공격 판정 초기화
		ao->direct = sf::Vector2f(0,0);																						// 투사체 방향은 없음
		ao->isthrow = true;																									// 투사체의 작동 유무 확인
		ao->range_s = sf::Vector2f(-w_Width, -w_Height);																	// 공격의 범위 시작 점
		ao->range_e = sf::Vector2f(w_Width, w_Height);																		// 공격의 범위 끝 점
		ao->enemyDirect = sf::Vector2f(0, 0);																				// 적의 투사체 방향
		attackObjList.push_back(ao);																						// 리스트에 추가
	}
	else if(skillNumber == 4){
		// 사용하지 않음
	}
}

/* 공격 리스트 */
void Jang::skill_NormalAttack(int frameCount){
	calculateSpriteNormalAttack(frameCount);
}

void Jang::skill_RotateKick(int frameCount){
	calculateSpriteRotateKick(frameCount);
}

void Jang::skill_doubleComboAttack(int frameCount){
	calculateSpritedoubleComboAttack(frameCount);
}

void Jang::skill_SpecialAttack(int frameCount){
	// 다른 함수에서 사용
}

void Jang::skill_Dash(int frameCount){
	// 대시 공격 없음
}
/* 공격 리스트 */

// 공격 판정 시 넉백 효과
void Jang::hit_KnockBack(int frameCount){
	calculateSpriteKnockBack(frameCount);
}

// 공격 판정 시 스턴 효과
void Jang::hit_stun(int frameCount){
	calculateSpriteStun(frameCount);
}

// 캐릭터 스프라이트 불러오는 부분
void Jang::loadCharacter(sf::Sprite &player){
	player.setTextureRect(sf::IntRect(this->getSpr().x, this->getSpr().y,170,100));
	player.scale(2.0f, 2.0f);
    player.setOrigin(85,50);
}

// 캐릭터 스프라이트의 위치 계산하는 부분
void Jang::calculateSpritePos(int step){
	this->setSpr(PIC_SIZE_X*step, 0);
}

// 일반 공격 'Q' 버튼 선택 시 실행
void Jang::calculateSpriteNormalAttack(int frameCount){
	if(frameCount == 0 || frameCount == 1)
		this->setSpr(PIC_SIZE_X * 4, PIC_SIZE_Y * 0);
	else if(frameCount == 2 || frameCount == 3)
		this->setSpr(PIC_SIZE_X * 5, PIC_SIZE_Y * 0);
	else if(frameCount == 4 || frameCount == 5)
		this->setSpr(PIC_SIZE_X * 4, PIC_SIZE_Y * 0);
	else
		this->setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 0); // 대기 상태	
}

// 방어 'S' 버튼 선택 시 실행
void Jang::calculateSpriteBlock(){
	this->setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 0);
}

// 특수 공격 '1' 버튼 클릭 시 나오는 기술
void Jang::calculateSpriteRotateKick(int frameCount){
	if(frameCount == 0 || frameCount == 1)
		this->setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 3);	
	else if(frameCount == 2 || frameCount == 3)
		this->setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 3);
	else if(frameCount == 4 || frameCount == 5)
		this->setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 3);
	else if(frameCount == 6 || frameCount == 7)
		this->setSpr(PIC_SIZE_X * 4, PIC_SIZE_Y * 3);
	else if(frameCount == 8 || frameCount == 9)
		this->setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 3);
	else if(frameCount == 10 || frameCount == 11)
		this->setSpr(PIC_SIZE_X * 6, PIC_SIZE_Y * 3);
	else if(frameCount == 12 || frameCount == 13)
	{
		this->setSpr(PIC_SIZE_X * 7, PIC_SIZE_Y * 3);
		bSkill[0] = false;
	}
	else
		this->setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 0);	
}

// 특수 공격 '2' 버튼 클릭 시 나오는 기술
void Jang::calculateSpritedoubleComboAttack(int frameCount){
	if(frameCount == 0)
		this->setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 5);
	else if(frameCount == 1)
		this->setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 4);
	else if(frameCount == 2)
		this->setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 4);
	else if(frameCount == 3)
		this->setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 4);
	else if(frameCount == 4){
		this->setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 4);
		this->setPosition(this->getPosition().x, this->getPosition().y-1.0);
	}
	else if(frameCount == 5){
		this->setSpr(PIC_SIZE_X * 4, PIC_SIZE_Y * 4);
		this->setPosition(this->getPosition().x, this->getPosition().y-0.6);
	}
	else if(frameCount == 6){
		this->setSpr(PIC_SIZE_X * 5, PIC_SIZE_Y * 4);
		this->setPosition(this->getPosition().x, this->getPosition().y-0.4);
	}
	else if(frameCount == 7){
		this->setSpr(PIC_SIZE_X * 6, PIC_SIZE_Y * 4);
		this->setPosition(this->getPosition().x, this->getPosition().y);
	}
	else if(frameCount == 8){
		this->setSpr(PIC_SIZE_X * 6, PIC_SIZE_Y * 4);
		this->setPosition(this->getPosition().x, this->getPosition().y+1.0);
	}
	else if(frameCount == 9){
		this->setSpr(PIC_SIZE_X * 6, PIC_SIZE_Y * 4);
		this->setPosition(this->getPosition().x, this->getPosition().y+1.0);
	}
	else if(frameCount == 10)
		this->setSpr(PIC_SIZE_X * 5, PIC_SIZE_Y * 4);
	else if(frameCount == 11)
		this->setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 4);
	else if(frameCount == 12)
		this->setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 4);
	else if(frameCount == 13)
		this->setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 5);
	else if(frameCount == 14)
		this->setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 5);
	else if(frameCount == 15){
		this->setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 5);
		if(this->getFacing())
			this->setPosition(this->getPosition().x+1, this->getPosition().y);
		else
			this->setPosition(this->getPosition().x-1, this->getPosition().y);
	}
	else if(frameCount == 16){
		this->setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 5);
		if(this->getFacing())
			this->setPosition(this->getPosition().x+1, this->getPosition().y);
		else
			this->setPosition(this->getPosition().x-1, this->getPosition().y);
	}
	else if(frameCount == 17){
		this->setSpr(PIC_SIZE_X * 4, PIC_SIZE_Y * 5);
		if(this->getFacing())
			this->setPosition(this->getPosition().x+1, this->getPosition().y);
		else
			this->setPosition(this->getPosition().x-1, this->getPosition().y);
	}
	else if(frameCount == 18){
		this->setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 5);
		if(this->getFacing())
			this->setPosition(this->getPosition().x+1, this->getPosition().y);
		else
			this->setPosition(this->getPosition().x-1, this->getPosition().y);
	}
	else if(frameCount == 19){
		this->setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 5);
		if(this->getFacing())
			this->setPosition(this->getPosition().x+1, this->getPosition().y);
		else
			this->setPosition(this->getPosition().x-1, this->getPosition().y);
	}
	else if(frameCount == 20)
		this->setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 5);
	else if(frameCount == 21)
	{
		this->setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 5);
		bSkill[1] = false;
	}
	else
		this->setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 0);
}

// 특수 공격 '3' 버튼 클릭 시 나오는 기술
void Jang::calculateSpriteSpecialAttack(int frameCount){
	// 다른 함수에서 사용
}

// 넉백 표현
void Jang::calculateSpriteKnockBack(int frameCount){
	if(frameCount < 2)
		this->setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 1);
	else 
		this->setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 1);
}

// 데미지를 입었을 경우
void Jang::calculateSpriteStun(int frameCount){
	if(frameCount < 1){
		this->setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 0);	
	}
	else if(frameCount < 2){
		this->setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 0);
	}
}

// 대시를 할 경우 -> 사용 안함
void Jang::calculateSpriteDash(int frameCount){
	// 대쉬 스프라이트 사용 없음
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

// 리스트를 지워주는 함수
void Jang::deleteAOList(){
	auto iter = attackObjList.begin();
	auto iter2 = iter;
	for(iter; iter!=attackObjList.end(); iter = iter2){
		iter2++;
		if((*iter)->check){
			attackObjList.erase(iter);
		}
	}
}

// 리스트를 계속 업데이트 해주는 함수
void Jang::updateAOList(){
	for(auto ao = attackObjList.begin(); ao != attackObjList.end(); ao++){
		if((*ao)->isthrow == false){								// 투사체가 아닌 것들
			if((*ao)->skillNumber == 0){							// 0,1,2번 스킬은 다음과 같이 설정 (캐릭터 따라서 움직여야 하기 때문에)
				if(this->getFacing()){
					(*ao)->range_s = sf::Vector2f(this->getPosition().x-PIC_SIZE_X/4, this->getPosition().y-PIC_SIZE_Y*2);
					(*ao)->range_e = sf::Vector2f(this->getPosition().x+PIC_SIZE_X/2, this->getPosition().y);
				}
				else{
					(*ao)->range_s = sf::Vector2f(this->getPosition().x-PIC_SIZE_X/2-PIC_SIZE_X/4*3, this->getPosition().y-PIC_SIZE_Y*2);
					(*ao)->range_e = sf::Vector2f(this->getPosition().x+PIC_SIZE_X/4-PIC_SIZE_X/4*3, this->getPosition().y);
				}
			}
			else if((*ao)->skillNumber == 1){
				if(this->getFacing()){
					(*ao)->range_s = sf::Vector2f(this->getPosition().x-PIC_SIZE_X/4, this->getPosition().y-PIC_SIZE_Y*2);
					(*ao)->range_e = sf::Vector2f(this->getPosition().x+PIC_SIZE_X/4, this->getPosition().y);
				}
				else{
					(*ao)->range_s = sf::Vector2f(this->getPosition().x-PIC_SIZE_X/2-PIC_SIZE_X/4*3, this->getPosition().y-PIC_SIZE_Y*2);
					(*ao)->range_e = sf::Vector2f(this->getPosition().x+PIC_SIZE_X/4-PIC_SIZE_X/4*3, this->getPosition().y);
				}
			}
			else if((*ao)->skillNumber == 2){
				if(this->getFacing()){
					(*ao)->range_s = sf::Vector2f(this->getPosition().x-PIC_SIZE_X/4, this->getPosition().y-PIC_SIZE_Y*2);
					(*ao)->range_e = sf::Vector2f(this->getPosition().x+PIC_SIZE_X/2, this->getPosition().y);
					(*ao)->enemyDirect = sf::Vector2f(5, 0);
				}
				else{
					(*ao)->range_s = sf::Vector2f(this->getPosition().x-PIC_SIZE_X/2-PIC_SIZE_X/4*3, this->getPosition().y-PIC_SIZE_Y*2);
					(*ao)->range_e = sf::Vector2f(this->getPosition().x+PIC_SIZE_X/4-PIC_SIZE_X/4*3, this->getPosition().y);
					(*ao)->enemyDirect = sf::Vector2f(-5, 0);
				}
			}
			if(!isAttacking())						// 투사체가 아니기 때문에 공격이 끝나면 알아서 삭제 시켜야 함
				(*ao)->check = true;
		}
		else{
			if((*ao)->skillNumber == 3 && bSkill[2]){			// 특수 공격 스프라이트
				if((*ao)->frameCount < 2){
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
					bSkill[2] = false;
				}
				else{
					(*ao)->check = true;
				}
				(*ao)->obj.setTextureRect(sf::IntRect((*ao)->objSpr.x, (*ao)->objSpr.y,PIC_SIZE_X,PIC_SIZE_Y)); // 성수가 올려놓은 그림 따라서 설정해주셈
				(*ao)->obj.setPosition(w_Width/2, w_Height/2+200);
			}
			else{
				(*ao)->range_s += (*ao)->direct * (*ao)->speed;													// 이건 혹시나 필요하면 갖다 쓰셈
				(*ao)->range_e += (*ao)->direct * (*ao)->speed;
				if((*ao)->range_e.x < 0 || (*ao)->range_s.x > w_Width || (*ao)->range_e.y > 400 || (*ao)->range_s.y < 0){
					(*ao)->check = true;
				}
			}
		}
		(*ao)->frameCount += 0.02;	// 투사체는 캐릭터의 frameCount와 별개니까 따로 생성했고, 속도는 캐릭터랑 똑같음
	}
}

// 충돌처리
void Jang::detectCollision(Champion &champion, float &enemyFrameCount){ 
	float left		= champion.getPosition().x - PIC_SIZE_X/4.0*3.0;
	float right		= champion.getPosition().x;
	float top		= champion.getPosition().y - PIC_SIZE_Y*2.0/8.0*7.0;
	float bottom	= champion.getPosition().y;
	for(auto ao = attackObjList.begin(); ao!=attackObjList.end(); ao++){
		if(((*ao)->range_s.x < left && (*ao)->range_e.x > left) || ((*ao)->range_s.x < right && (*ao)->range_e.x > right)){
			if(((*ao)->range_s.y < top && (*ao)->range_e.y > top) || ((*ao)->range_s.y < bottom && (*ao)->range_e.y > bottom)){
				// 맞았음
				if((*ao)->skillNumber == 0){	// 평타 맞으면 다음과 같이 됨
					(*ao)->check = true;
					if(champion.isBarrier()) champion.setHp(champion.getHp()-(*ao)->damage*0.2);
					else{
						champion.isKnockBack = true;
						enemyFrameCount = 0;
						champion.setHp(champion.getHp()-(*ao)->damage);
						champion.vx = (*ao)->enemyDirect.x;
						champion.vy = (*ao)->enemyDirect.y;
					}
					if(champion.getHp() < 0) champion.setHp(0);
				}
				else if((*ao)->skillNumber == 1 && bSkill[0]){  // 최후의일격 맞으면 다음과 같이됨
					(*ao)->check = true;
					if(champion.isBarrier()) champion.setHp(champion.getHp()-(*ao)->damage*0.2);
					else{
						champion.isKnockBack = true;
						enemyFrameCount = 0;
						champion.setHp(champion.getHp()-(*ao)->damage);
						champion.vx = (*ao)->enemyDirect.x;
						champion.vy = (*ao)->enemyDirect.y;
					}
					if(champion.getHp() < 0) champion.setHp(0);
				}
				else if((*ao)->skillNumber == 2 && bSkill[1]){ // 바람의 상처 맞으면 다음과 같이 됨
					(*ao)->check = false;
					if(champion.isBarrier()) champion.setHp(champion.getHp()-(*ao)->damage*0.2);
					else{ 
						champion.isStun = true;
						enemyFrameCount = 0;
						champion.setHp(champion.getHp()-(*ao)->damage);
					}
					if(champion.getHp() < 0) champion.setHp(0);
				}
				else if((*ao)->skillNumber == 3 && bSkill[2]){  // 궁맞으면 다음과 같이 됨 (벗어날 곳이 없지)
					int ran = rand()%30;
					int ran2 = rand()%30;
					if(champion.isBarrier()) champion.setHp(champion.getHp()-(*ao)->damage*0.2);
					else{ 
						champion.isStun = true;
						enemyFrameCount = 0;
						champion.setHp(champion.getHp()-(*ao)->damage);
					}
					sf::Vector2f direct = sf::Vector2f(w_Width/2+(ran-15) - champion.getPosition().x, w_Height/2+(ran2-15) - champion.getPosition().y);
					champion.setPosition(champion.getPosition().x + direct.x * champion.getSpeed()/8, champion.getPosition().y + direct.y * champion.getSpeed());
					if(champion.getHp() < 0) champion.setHp(0);
				}
			}
		}
	}

};
