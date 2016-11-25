#include "Champion.hpp"

const int MIN_DIST_X = 60;
const int MIN_DIST_Y = 340;
const int ENERGY_SIZE_X = 85;
const int ENERGY_SIZE_Y = 40;
const int PIC_SIZE_X = 170;
const int PIC_SIZE_Y = 100;
const float FRAMESPEED = 0.02;

Champion::Champion(int player, int m_number, int width, int height){  // champion class 
	this->player = player;
	this->modelNumber = m_number;

	w_Width = width;
	w_Height = height;

	if(player == 1){
		facing = 1;
		setPosition(MIN_DIST_X, MIN_DIST_Y);
		setSpr(0, 0);
	}
	else{
		facing = 0;
		setPosition(w_Width-MIN_DIST_X, MIN_DIST_Y);
		setSpr(96, 32);
	}

	winScore = 0;
	hp = 100;
	speed = 0.05;
	ay = 0.002;
	ax = 0.001;
	vy = 0;
	vx = 0;

	attack = false;
	barrier = false;

	selectSkin = false;
	isStun = false;
	isKnockBack = false;
	s_champion = this;

	gpl		= new GPL();
	bsd		= new BSD();
	apache	= new Apache();
	jang	= new Jang();
	lgpl	= new LGPL();
}

Champion::~Champion(){};

sf::Vector2<float> Champion::getPosition(){			// return champion position
	return this->pos;
}

void Champion::setPosition(float _x, float _y){     // set champion position
	pos.x = _x;
	pos.y = _y;
}

void Champion::move(float left, float right, float jump){	// champion moving
	if(left){												// move left
		if(facing==0)
			pos.x = (pos.x - (left*speed));
		else
			pos.x = (pos.x - (left*speed/3*2));
	}
	else if(right){											// move right
		if(facing ==0){
			pos.x = (pos.x + (right*speed/3*2)); 
		}
		else{
			pos.x = (pos.x + (right*speed));
		}
	}
	if(pos.x < MIN_DIST_X){									// exception handling
		pos.x = MIN_DIST_X;
	}
	else if(pos.x >= w_Width-MIN_DIST_X){
		pos.x = w_Width - MIN_DIST_X;
	}
	vy += (jump*2*speed*2);									// jump
}

void Champion::caculatePosXY(){                             // calculate champion pos with vy and vx
	pos.y += vy;
	vy += ay;
	if(pos.y >= MIN_DIST_Y){
		pos.y = MIN_DIST_Y;
		vy = 0;
	}
	if(pos.y == MIN_DIST_Y){
		grounded = true;
		vx = 0;
	}
	else{
		grounded = false;
	}

	if(abs(vx) > 0.1){
		pos.x += vx;
		if(pos.x < MIN_DIST_X){
			pos.x = MIN_DIST_X;
		}
		else if(pos.x >= w_Width-MIN_DIST_X){
			pos.x = w_Width - MIN_DIST_X;
		}
	}
}

sf::Vector2<float> Champion::getSpr(){						// return champion sprite pos
	return this->spr;
}

void Champion::setSpr(float _x, float _y){					// set champion sprite pos
	spr.x = _x;
	spr.y = _y;
}

float Champion::getHp(){									// return champion hp
	return this->hp;
}


void Champion::setHp(float _hp){							// set champion hp
	this->hp = _hp;
}


void Champion::setFacing(int face){							// set champion facing
	facing = face;
}

bool Champion::isAttacking(){								// return champion is attacking?
	return attack;
}


bool Champion::isBarrier(){									// return champion is barriering?
	return barrier;
}


void Champion::setAttack(bool a){							// set champion attacking 
	attack = a;
}


void Champion::setBarrier(bool b){							// set champion barrier
	barrier = b;
}

bool Champion::isDeath(){									// return champion hp <= 0
	if(hp<=0) return true;
	else return false;
}

bool Champion::isGrounded(){								// return champion grounded
	return grounded;
}

void Champion::setGrounded(bool g){							// set champion grounded
	grounded = g;
}

float Champion::getSpeed(){									// return champion speed
	return speed;
}

void Champion::setSpeed(float s){							// set champion speed
	speed = s;
}

void Champion::playerWin(){									// plus one point with win player score
	winScore++;
}

bool Champion::getFacing(){									// return champion facing
	return facing;
}

int Champion::getWinScore(){								// return player score
	return winScore;
}

void Champion::crowdControlHit(float &frameCount){			// champion is stun or knockback 

	if(this->isStun){
		if(modelNumber == 0){ // GPL
			gpl->hit_stun((int)frameCount, *s_champion);
		}
		else if(modelNumber == 1){ // BSD
			bsd->hit_stun((int)frameCount, *s_champion);
		}
		else if(modelNumber == 2){ // LGPL
			lgpl->hit_stun((int)frameCount, *s_champion);
		}
		else if(modelNumber == 3){ // Apache
			apache->hit_stun((int)frameCount, *s_champion);
		}
		else if(modelNumber ==4){ // P.Jang
			jang->hit_stun((int)frameCount, *s_champion);
		}
		frameCount+=FRAMESPEED;
		if(frameCount>4) this->isStun = false;
	}
	else if(this->isKnockBack){
		if(modelNumber == 0){ // GPL
			gpl->hit_KnockBack((int)frameCount, *s_champion);
		}
		else if(modelNumber == 1){ // BSD
			bsd->hit_KnockBack((int)frameCount, *s_champion);
		}
		else if(modelNumber == 2){ // LGPL
			lgpl->hit_KnockBack((int)frameCount, *s_champion);
		}
		else if(modelNumber == 3){ // Apache
			apache->hit_KnockBack((int)frameCount, *s_champion);
		}
		else if(modelNumber ==4){ // P.Jang
			jang->hit_KnockBack((int)frameCount, *s_champion);
		}
		frameCount+=FRAMESPEED;
		if(frameCount>20) this->isKnockBack = false;
	}
}

void Champion::insertAOList(int skillNumber){
	if(modelNumber == 0){ // GPL
		gpl->canUseSkillCount[skillNumber]--;
		if(skillNumber == 0){
			AttackObject* ao = new AttackObject(skillNumber, 10, 1);
			ao->damage = 10;					// 평타 댐지 10
			ao->check = false;					// 아직 안맞았고
			ao->direct = sf::Vector2f(0,0);		// 방향 없고(투사체가 아니니까)
			ao->isthrow = false;				// 투사체 아니고
			if(this->getFacing()){				// 오른쪽 바라보고 있으면
				ao->range_s = sf::Vector2f(this->getPosition().x-PIC_SIZE_X/4, this->getPosition().y-PIC_SIZE_Y*2); // 시작점 끝점 설정
				ao->range_e = sf::Vector2f(this->getPosition().x+PIC_SIZE_X/2, this->getPosition().y);
				ao->enemyDirect = sf::Vector2f(0.2, -1);	// 적이 넉백 될때 0.2와 -1로 설정하는게 보기 아름다움
			}
			else{
				ao->range_s = sf::Vector2f(this->getPosition().x-PIC_SIZE_X/2-PIC_SIZE_X/4*3, this->getPosition().y-PIC_SIZE_Y*2);
				ao->range_e = sf::Vector2f(this->getPosition().x+PIC_SIZE_X/4-PIC_SIZE_X/4*3, this->getPosition().y);
				ao->enemyDirect = sf::Vector2f(-0.2, -1);
			}
			attackObjList.push_back(ao);		// 다 설정해주고 리스트에 집어넣음
		}
		else if(skillNumber == 1){				// 밑으로 마찬가지로 같이 설정
			AttackObject* ao = new AttackObject(skillNumber, 20, 1);
			ao->damage = 30;
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
		else if(skillNumber == 2){
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
		else if(skillNumber == 3){			// 궁은 따로 이미지를 입혀야 하기 때문에 색다르게 설정
			AttackObject* ao = new AttackObject(skillNumber, 0, 0);
			if (!ao->throwTexture.loadFromFile("./images/character/gpl_sprite.png")) printf( "Error loading vx_characters\n");	// 이미지 불러오고
			ao->objSpr = sf::Vector2f(PIC_SIZE_X * 0, PIC_SIZE_Y * 6);															// 스프라이트 찍어주고
			ao->obj.setTexture(ao->throwTexture);																				// 텍스쳐 넣어주고
			ao->obj.setTextureRect(sf::IntRect(ao->objSpr.x, ao->objSpr.y,170,200));											// 사각형 범위 정하고
			ao->obj.scale(1.0f, 1.0f);																							// 크기 늘려주고
			ao->obj.setOrigin(85,100);																							// 좌표에서 넣었으니 다시 중앙으로 옮김
			ao->obj.setPosition(w_Width/2, w_Height/2);																			// 위치 정해주고
			ao->damage = 0;																										// 데미지 없고
			ao->check = false;																									// check 초기화
			ao->direct = sf::Vector2f(0,0);																						// 투사체지만 방향은 없고
			ao->isthrow = true;																									// 투사체고
			ao->range_s = sf::Vector2f(-w_Width, -w_Height);																	// 범위는 맵 전체
			ao->range_e = sf::Vector2f(w_Width, w_Height);
			ao->enemyDirect = sf::Vector2f(0, 0);																				// 의미 없고
			attackObjList.push_back(ao);																						// 넣어준다
		}
	}
	else if(modelNumber == 1){ // BSD
		bsd->canUseSkillCount[skillNumber]--;
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

			attackObjList.push_back(ao);	
		}// 넣어준다
	}
	else if(modelNumber == 2){ // LGPL
		if (skillNumber == 0) {
			AttackObject* ao = new AttackObject(skillNumber, 10, 2.0);

			if (!ao->throwTexture.loadFromFile("./images/character/LGPL_sprite.png")) printf("Error loading vx_characters\n");		// 이미지 불러오고

			if (this->getFacing()) {
				ao->objSpr = sf::Vector2f(PIC_SIZE_X*4, PIC_SIZE_Y * 2);														// 스프라이트 찍어주고
				ao->obj.setTexture(ao->throwTexture);																				// 텍스쳐 넣어주고
				ao->obj.setTextureRect(sf::IntRect(ao->objSpr.x, ao->objSpr.y, 100, 50));											// 사각형 범위 정하고
				ao->obj.scale(1.5f, 1.5f);																							// 크기 늘려주고

				ao->range_s = sf::Vector2f(this->getPosition().x, this->getPosition().y - ENERGY_SIZE_Y / 2 * 3);
				ao->range_e = sf::Vector2f(this->getPosition().x + ENERGY_SIZE_X, this->getPosition().y + ENERGY_SIZE_Y / 2 * 3);

				ao->direct = sf::Vector2f(1, 0);																					// 투사체, 오른쪽

				ao->enemyDirect = sf::Vector2f(0.1, -0.1);
			}
			else {
				ao->objSpr = sf::Vector2f(PIC_SIZE_X*4, PIC_SIZE_Y * 2);														// 스프라이트 찍어주고
				ao->obj.setTexture(ao->throwTexture);																				// 텍스쳐 넣어주고
				ao->obj.setTextureRect(sf::IntRect(ao->objSpr.x, ao->objSpr.y, 100, 50));											// 사각형 범위 정하고
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

		else if (skillNumber == 1) {
			AttackObject* ao = new AttackObject(skillNumber, 20, 0.7);

			if (!ao->throwTexture.loadFromFile("./images/character/LGPL_sprite.png")) printf("Error loading vx_characters\n");		// 이미지 불러오고
			//gpl, lgpl, apache 중 한 개의 스프라이트 선택 위한 난수
			if (this->getFacing()) {
				ao->objSpr = sf::Vector2f(PIC_SIZE_X*1, PIC_SIZE_Y * 7);														// 스프라이트 찍어주고
				ao->obj.setTexture(ao->throwTexture);																				// 텍스쳐 넣어주고
				ao->obj.setTextureRect(sf::IntRect(ao->objSpr.x, ao->objSpr.y, 150, 100));											// 사각형 범위 정하고
				ao->obj.scale(1.5f, 1.5f);																							// 크기 늘려주고

				ao->range_s = sf::Vector2f(this->getPosition().x, this->getPosition().y - ENERGY_SIZE_Y / 2 * 3);
				ao->range_e = sf::Vector2f(this->getPosition().x + ENERGY_SIZE_X, this->getPosition().y + ENERGY_SIZE_Y / 2 * 3);

				ao->direct = sf::Vector2f(1, 0);																					// 투사체, 오른쪽

				ao->enemyDirect = sf::Vector2f(0.1, -0.1);
			}
			else {
				ao->objSpr = sf::Vector2f(PIC_SIZE_X*1, PIC_SIZE_Y * 6);														// 스프라이트 찍어주고
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


		if (skillNumber == 2) {
			AttackObject* ao = new AttackObject(skillNumber, 3, 0.4);

			if (!ao->throwTexture.loadFromFile("./images/character/GPL_sprite.png")) printf("Error loading vx_characters\n");		// 이미지 불러오고
			if (this->getFacing()) {
				ao->objSpr = sf::Vector2f(PIC_SIZE_X * 5, PIC_SIZE_Y * 0);															// 스프라이트 찍어주고
				ao->obj.setTexture(ao->throwTexture);																				// 텍스쳐 넣어주고
				ao->obj.setTextureRect(sf::IntRect(ao->objSpr.x, ao->objSpr.y, 150, 100));											// 사각형 범위 정하고
				ao->obj.scale(1.0, 2.0f);																							// 크기 늘려주고

				ao->range_s = sf::Vector2f(this->getPosition().x - ENERGY_SIZE_X/2, this->getPosition().y  - ENERGY_SIZE_Y );
				ao->range_e = sf::Vector2f(this->getPosition().x , this->getPosition().y );
				ao->direct = sf::Vector2f(1, -2);																					// 투사체, 오른쪽

				ao->enemyDirect = sf::Vector2f(0.5, -0.4);
			}
			else {
				ao->objSpr = sf::Vector2f(PIC_SIZE_X * 5, PIC_SIZE_Y * 0);															// 스프라이트 찍어주고
				ao->obj.setTexture(ao->throwTexture);																				// 텍스쳐 넣어주고
				ao->obj.setTextureRect(sf::IntRect(ao->objSpr.x, ao->objSpr.y, 150, 100));											// 사각형 범위 정하고
				ao->obj.scale(1.0f, 2.0f);																							// 크기 늘려주고

				ao->range_s = sf::Vector2f(this->getPosition().x - PIC_SIZE_X - ENERGY_SIZE_X/2, this->getPosition().y - ENERGY_SIZE_Y );
				ao->range_e = sf::Vector2f(this->getPosition().x , this->getPosition().y );

				ao->direct = sf::Vector2f(-1, -2);																					// 투사체, 왼쪽

				ao->enemyDirect = sf::Vector2f(-0.5, -0.4);
			}

			// 위치 정해주고
			ao->damage = 3;																										// 1 HIT 당 3 데미지
			ao->check = false;																									// check 초기화
			ao->isthrow = true;																									// 투사체고
			ao->hitcount = 10;																									// 총 10회 HIT
			this->setPosition(ao->range_e.x, ao->range_e.y);

			attackObjList.push_back(ao);
		}
		if (skillNumber == 3) {
			AttackObject* ao = new AttackObject(skillNumber, 3, 0.4);

			if (!ao->throwTexture.loadFromFile("./images/character/LGPL_sprite.png")) printf("Error loading vx_characters\n");		// 이미지 불러오고
			if (this->getFacing()) {
				ao->objSpr = sf::Vector2f(PIC_SIZE_X * 3, PIC_SIZE_Y * 8);															// 스프라이트 찍어주고
				ao->obj.setTexture(ao->throwTexture);																				// 텍스쳐 넣어주고
				ao->obj.setTextureRect(sf::IntRect(ao->objSpr.x, ao->objSpr.y, 150, 100));											// 사각형 범위 정하고
				ao->obj.scale(3.0, 1.0f);																							// 크기 늘려주고

				ao->range_s = sf::Vector2f(this->getPosition().x, this->getPosition().y - ENERGY_SIZE_Y / 2 * 3);
				ao->range_e = sf::Vector2f(this->getPosition().x + ENERGY_SIZE_X, this->getPosition().y + ENERGY_SIZE_Y / 2 * 3);

				ao->direct = sf::Vector2f(1, -0.1);																					// 투사체, 오른쪽

				ao->enemyDirect = sf::Vector2f(0.5, -0.4);
			}
			else {
				ao->objSpr = sf::Vector2f(PIC_SIZE_X * 3, PIC_SIZE_Y * 8);															// 스프라이트 찍어주고
				ao->obj.setTexture(ao->throwTexture);																				// 텍스쳐 넣어주고
				ao->obj.setTextureRect(sf::IntRect(ao->objSpr.x, ao->objSpr.y, 150, 100));											// 사각형 범위 정하고
				ao->obj.scale(3.0f, 1.0f);																							// 크기 늘려주고

				ao->range_s = sf::Vector2f(this->getPosition().x - PIC_SIZE_X - ENERGY_SIZE_X, this->getPosition().y - ENERGY_SIZE_Y / 2 * 3);
				ao->range_e = sf::Vector2f(this->getPosition().x - PIC_SIZE_X, this->getPosition().y + ENERGY_SIZE_Y / 2 * 3);

				ao->direct = sf::Vector2f(-1, -0.1);																					// 투사체, 왼쪽

				ao->enemyDirect = sf::Vector2f(-0.5, -0.4);
			}

			// 위치 정해주고
			ao->damage = 3;																										// 1 HIT 당 3 데미지
			ao->check = false;																									// check 초기화
			ao->isthrow = true;																									// 투사체고
			ao->hitcount = 10;																									// 총 10회 HIT

			attackObjList.push_back(ao);
		}
	}
	else if(modelNumber == 3){ // Apache
		apache->canUseSkillCount[skillNumber]--;
		if (skillNumber == 0) {
			AttackObject* ao = new AttackObject(skillNumber, 10, 1);
			ao->damage = 10;					// 평타 댐지 10
			ao->check = false;					// 아직 안맞았고
			ao->direct = sf::Vector2f(0, 0);		// 방향 없고(투사체가 아니니까)
			ao->isthrow = false;				// 투사체 아니고
			if (this->getFacing()) {				// 오른쪽 바라보고 있으면
				ao->range_s = sf::Vector2f(this->getPosition().x - PIC_SIZE_X / 4, this->getPosition().y - PIC_SIZE_Y * 2); // 시작점 끝점 설정
				ao->range_e = sf::Vector2f(this->getPosition().x + PIC_SIZE_X / 2, this->getPosition().y);
				ao->enemyDirect = sf::Vector2f(0.2, -1);	// 적이 넉백 될때 0.2와 -1로 설정하는게 보기 아름다움
			}
			else {
				ao->range_s = sf::Vector2f(this->getPosition().x - PIC_SIZE_X / 2 - PIC_SIZE_X / 4 * 3, this->getPosition().y - PIC_SIZE_Y * 2);
				ao->range_e = sf::Vector2f(this->getPosition().x + PIC_SIZE_X / 4 - PIC_SIZE_X / 4 * 3, this->getPosition().y);
				ao->enemyDirect = sf::Vector2f(-0.2, -1);
			}
			attackObjList.push_back(ao);		// 다 설정해주고 리스트에 집어넣음
		}
		else if (skillNumber == 1) {				// 밑으로 마찬가지로 같이 설정
			AttackObject* ao = new AttackObject(skillNumber, 20, 1);
			ao->damage = 10;
			ao->check = false;
			ao->direct = sf::Vector2f(1, 0);
			ao->isthrow = false;
			if (this->getFacing()) {
				ao->range_s = sf::Vector2f(this->getPosition().x - PIC_SIZE_X / 3, this->getPosition().y - PIC_SIZE_Y);
				ao->range_e = sf::Vector2f(this->getPosition().x - PIC_SIZE_X / 3 + PIC_SIZE_X, this->getPosition().y - PIC_SIZE_Y / 4);
				ao->enemyDirect = sf::Vector2f(0.2, -1);
			}
			else {
				ao->range_s = sf::Vector2f(this->getPosition().x - PIC_SIZE_X + PIC_SIZE_X / 3 - PIC_SIZE_X, this->getPosition().y - PIC_SIZE_Y);
				ao->range_e = sf::Vector2f(this->getPosition().x - PIC_SIZE_X + PIC_SIZE_X / 3, this->getPosition().y - PIC_SIZE_Y / 4);
				ao->enemyDirect = sf::Vector2f(-0.2, -1);
			}
			attackObjList.push_back(ao);
		}
		else if (skillNumber == 2) {
			AttackObject* ao = new AttackObject(skillNumber, 0, 1);
			ao->damage = 0;
			ao->check = false;
			ao->direct = sf::Vector2f(0, 0);
			ao->isthrow = false;
			attackObjList.push_back(ao);
		}
		else if (skillNumber == 3) {			// 궁은 따로 이미지를 입혀야 하기 때문에 색다르게 설정
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
	}
	else if(modelNumber ==4){ // P.Jang
		jang->canUseSkillCount[skillNumber]--;
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
	}
}

void Champion::updateAOList(){					// update Attack Objcect List
	if(modelNumber == 0){ // GPL
		gpl->updateAOList(*s_champion);
	}
	else if(modelNumber == 1){ // BSD
		bsd->updateAOList(*s_champion);
	}
	else if(modelNumber == 2){ // LGPL
		lgpl->updateAOList(*s_champion);
	}
	else if(modelNumber == 3){ // Apache
		apache->updateAOList(*s_champion);
	}
	else if(modelNumber ==4){ // P.Jang
		jang->updateAOList(*s_champion);
	}
}

void Champion::deleteAOList(){
	auto iter = attackObjList.begin();
	auto iter2 = iter;
	for(iter; iter!=attackObjList.end(); iter = iter2){
		iter2++;
		if((*iter)->check){
			attackObjList.erase(iter);
		}
	}
}

void Champion::useSkill(int frameCount){				// champion use skill
	if(modelNumber == 0){ // GPL
		gpl->useSkill(skillNumber, frameCount, *s_champion);
	}
	else if(modelNumber == 1){ // BSD
		bsd->useSkill(skillNumber, frameCount, *s_champion);
	}
	else if(modelNumber == 2){ // LGPL
		lgpl->useSkill(skillNumber, frameCount, *s_champion);
	}
	else if(modelNumber == 3){ // Apache
		apache->useSkill(skillNumber, frameCount, *s_champion);
	}
	else if(modelNumber ==4){ // P.Jang
		jang->useSkill(skillNumber, frameCount, *s_champion);
	}
}

void Champion::calculateSpriteBlock(){					// champion barrier
	if(modelNumber == 0){ // GPL
		gpl->calculateSpriteBlock(*s_champion);
	}
	else if(modelNumber == 1){ // BSD
		bsd->calculateSpriteBlock(*s_champion);
	}
	else if(modelNumber == 2){ // LGPL
		lgpl->calculateSpriteBlock(*s_champion);
	}
	else if(modelNumber == 3){ // Apache
		apache->calculateSpriteBlock(*s_champion);
	}
	else if(modelNumber ==4){ // P.Jang
		jang->calculateSpriteBlock(*s_champion);
	}
}

int Champion::getCanUseSkillCount(int skillNumber){			// return champion can use skill count of skill number
	if(modelNumber == 0){ // GPL
		gpl->getCanUseSkillCount(skillNumber);
	}
	else if(modelNumber == 1){ // BSD
		bsd->getCanUseSkillCount(skillNumber);
	}
	else if(modelNumber == 2){ // LGPL
		lgpl->getCanUseSkillCount(skillNumber);
	}
	else if(modelNumber == 3){ // Apache
		apache->getCanUseSkillCount(skillNumber);
	}
	else if(modelNumber ==4){ // P.Jang
		jang->getCanUseSkillCount(skillNumber);
	}
}

void Champion::loadCharacter(sf::Sprite& s){				// load character sprite
	if(modelNumber == 0){ // GPL
		gpl->loadCharacter(s, *s_champion);
	}
	else if(modelNumber == 1){ // BSD
		bsd->loadCharacter(s, *s_champion);
	}
	else if(modelNumber == 2){ // LGPL
		lgpl->loadCharacter(s, *s_champion);
	}
	else if(modelNumber == 3){ // Apache
		apache->loadCharacter(s, *s_champion);
	}
	else if(modelNumber ==4){ // P.Jang
		jang->loadCharacter(s, *s_champion);
	}
}

void Champion::setSkillNumber(int skillNumber){				// set skill number
	this->skillNumber = skillNumber;
	if(modelNumber == 0){ // GPL
		gpl->setSkillNumber(skillNumber);
	}
	else if(modelNumber == 1){ // BSD
		bsd->setSkillNumber(skillNumber);
	}
	else if(modelNumber == 2){ // LGPL
		lgpl->setSkillNumber(skillNumber);
	}
	else if(modelNumber == 3){ // Apache
		apache->setSkillNumber(skillNumber);
	}
	else if(modelNumber ==4){ // P.Jang
		jang->setSkillNumber(skillNumber);
	}
}

int Champion::getSkillFrameTotal(){						// return total skill frame
	int ret = 0;
	if(modelNumber == 0){ // GPL
		ret = gpl->getSkillFrameTotal();
	}
	else if(modelNumber == 1){ // BSD
		ret = bsd->getSkillFrameTotal();
	}
	else if(modelNumber == 2){ // LGPL
		ret = lgpl->getSkillFrameTotal();
	}
	else if(modelNumber == 3){ // Apache
		ret = apache->getSkillFrameTotal();
	}
	else if(modelNumber ==4){ // P.Jang
		ret = jang->getSkillFrameTotal();
	}
	return ret;
}

void Champion::calculateSpritePos(){					// calculate sprite pos 
	if(modelNumber == 0){ // GPL
		gpl->calculateSpritePos(*s_champion);
	}
	else if(modelNumber == 1){ // BSD
		bsd->calculateSpritePos(*s_champion);
	}
	else if(modelNumber == 2){ // LGPL
		lgpl->calculateSpritePos(*s_champion);
	}
	else if(modelNumber == 3){ // Apache
		apache->calculateSpritePos(*s_champion);
	}
	else if(modelNumber ==4){ // P.Jang
		jang->calculateSpritePos(*s_champion);
	}
}

void Champion::detectCollision(Champion &c, float &enemyFrameCount){
	if(modelNumber == 0){ // GPL
		gpl->detectCollision(c, this->attackObjList, enemyFrameCount);
	}
	else if(modelNumber == 1){ // BSD
		bsd->detectCollision(c, this->attackObjList, enemyFrameCount);
	}
	else if(modelNumber == 2){ // LGPL
		lgpl->detectCollision(c, this->attackObjList, enemyFrameCount);
	}
	else if(modelNumber == 3){ // Apache
		apache->detectCollision(c, this->attackObjList, enemyFrameCount);
	}
	else if(modelNumber ==4){ // P.Jang
		jang->detectCollision(c, this->attackObjList, enemyFrameCount);
	}
}

int Champion::getModelNumber(){
	return modelNumber;
}