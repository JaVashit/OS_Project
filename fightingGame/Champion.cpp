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
			ao->damage = 10;					// ��Ÿ ���� 10
			ao->check = false;					// ���� �ȸ¾Ұ�
			ao->direct = sf::Vector2f(0,0);		// ���� ����(����ü�� �ƴϴϱ�)
			ao->isthrow = false;				// ����ü �ƴϰ�
			if(this->getFacing()){				// ������ �ٶ󺸰� ������
				ao->range_s = sf::Vector2f(this->getPosition().x-PIC_SIZE_X/4, this->getPosition().y-PIC_SIZE_Y*2); // ������ ���� ����
				ao->range_e = sf::Vector2f(this->getPosition().x+PIC_SIZE_X/2, this->getPosition().y);
				ao->enemyDirect = sf::Vector2f(0.2, -1);	// ���� �˹� �ɶ� 0.2�� -1�� �����ϴ°� ���� �Ƹ��ٿ�
			}
			else{
				ao->range_s = sf::Vector2f(this->getPosition().x-PIC_SIZE_X/2-PIC_SIZE_X/4*3, this->getPosition().y-PIC_SIZE_Y*2);
				ao->range_e = sf::Vector2f(this->getPosition().x+PIC_SIZE_X/4-PIC_SIZE_X/4*3, this->getPosition().y);
				ao->enemyDirect = sf::Vector2f(-0.2, -1);
			}
			attackObjList.push_back(ao);		// �� �������ְ� ����Ʈ�� �������
		}
		else if(skillNumber == 1){				// ������ ���������� ���� ����
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
		else if(skillNumber == 3){			// ���� ���� �̹����� ������ �ϱ� ������ ���ٸ��� ����
			AttackObject* ao = new AttackObject(skillNumber, 0, 0);
			if (!ao->throwTexture.loadFromFile("./images/character/gpl_sprite.png")) printf( "Error loading vx_characters\n");	// �̹��� �ҷ�����
			ao->objSpr = sf::Vector2f(PIC_SIZE_X * 0, PIC_SIZE_Y * 6);															// ��������Ʈ ����ְ�
			ao->obj.setTexture(ao->throwTexture);																				// �ؽ��� �־��ְ�
			ao->obj.setTextureRect(sf::IntRect(ao->objSpr.x, ao->objSpr.y,170,200));											// �簢�� ���� ���ϰ�
			ao->obj.scale(1.0f, 1.0f);																							// ũ�� �÷��ְ�
			ao->obj.setOrigin(85,100);																							// ��ǥ���� �־����� �ٽ� �߾����� �ű�
			ao->obj.setPosition(w_Width/2, w_Height/2);																			// ��ġ �����ְ�
			ao->damage = 0;																										// ������ ����
			ao->check = false;																									// check �ʱ�ȭ
			ao->direct = sf::Vector2f(0,0);																						// ����ü���� ������ ����
			ao->isthrow = true;																									// ����ü��
			ao->range_s = sf::Vector2f(-w_Width, -w_Height);																	// ������ �� ��ü
			ao->range_e = sf::Vector2f(w_Width, w_Height);
			ao->enemyDirect = sf::Vector2f(0, 0);																				// �ǹ� ����
			attackObjList.push_back(ao);																						// �־��ش�
		}
	}
	else if(modelNumber == 1){ // BSD
		bsd->canUseSkillCount[skillNumber]--;
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

			attackObjList.push_back(ao);	
		}// �־��ش�
	}
	else if(modelNumber == 2){ // LGPL
		if (skillNumber == 0) {
			AttackObject* ao = new AttackObject(skillNumber, 10, 2.0);

			if (!ao->throwTexture.loadFromFile("./images/character/LGPL_sprite.png")) printf("Error loading vx_characters\n");		// �̹��� �ҷ�����

			if (this->getFacing()) {
				ao->objSpr = sf::Vector2f(PIC_SIZE_X*4, PIC_SIZE_Y * 2);														// ��������Ʈ ����ְ�
				ao->obj.setTexture(ao->throwTexture);																				// �ؽ��� �־��ְ�
				ao->obj.setTextureRect(sf::IntRect(ao->objSpr.x, ao->objSpr.y, 100, 50));											// �簢�� ���� ���ϰ�
				ao->obj.scale(1.5f, 1.5f);																							// ũ�� �÷��ְ�

				ao->range_s = sf::Vector2f(this->getPosition().x, this->getPosition().y - ENERGY_SIZE_Y / 2 * 3);
				ao->range_e = sf::Vector2f(this->getPosition().x + ENERGY_SIZE_X, this->getPosition().y + ENERGY_SIZE_Y / 2 * 3);

				ao->direct = sf::Vector2f(1, 0);																					// ����ü, ������

				ao->enemyDirect = sf::Vector2f(0.1, -0.1);
			}
			else {
				ao->objSpr = sf::Vector2f(PIC_SIZE_X*4, PIC_SIZE_Y * 2);														// ��������Ʈ ����ְ�
				ao->obj.setTexture(ao->throwTexture);																				// �ؽ��� �־��ְ�
				ao->obj.setTextureRect(sf::IntRect(ao->objSpr.x, ao->objSpr.y, 100, 50));											// �簢�� ���� ���ϰ�
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

		else if (skillNumber == 1) {
			AttackObject* ao = new AttackObject(skillNumber, 20, 0.7);

			if (!ao->throwTexture.loadFromFile("./images/character/LGPL_sprite.png")) printf("Error loading vx_characters\n");		// �̹��� �ҷ�����
			//gpl, lgpl, apache �� �� ���� ��������Ʈ ���� ���� ����
			if (this->getFacing()) {
				ao->objSpr = sf::Vector2f(PIC_SIZE_X*1, PIC_SIZE_Y * 7);														// ��������Ʈ ����ְ�
				ao->obj.setTexture(ao->throwTexture);																				// �ؽ��� �־��ְ�
				ao->obj.setTextureRect(sf::IntRect(ao->objSpr.x, ao->objSpr.y, 150, 100));											// �簢�� ���� ���ϰ�
				ao->obj.scale(1.5f, 1.5f);																							// ũ�� �÷��ְ�

				ao->range_s = sf::Vector2f(this->getPosition().x, this->getPosition().y - ENERGY_SIZE_Y / 2 * 3);
				ao->range_e = sf::Vector2f(this->getPosition().x + ENERGY_SIZE_X, this->getPosition().y + ENERGY_SIZE_Y / 2 * 3);

				ao->direct = sf::Vector2f(1, 0);																					// ����ü, ������

				ao->enemyDirect = sf::Vector2f(0.1, -0.1);
			}
			else {
				ao->objSpr = sf::Vector2f(PIC_SIZE_X*1, PIC_SIZE_Y * 6);														// ��������Ʈ ����ְ�
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


		if (skillNumber == 2) {
			AttackObject* ao = new AttackObject(skillNumber, 3, 0.4);

			if (!ao->throwTexture.loadFromFile("./images/character/GPL_sprite.png")) printf("Error loading vx_characters\n");		// �̹��� �ҷ�����
			if (this->getFacing()) {
				ao->objSpr = sf::Vector2f(PIC_SIZE_X * 5, PIC_SIZE_Y * 0);															// ��������Ʈ ����ְ�
				ao->obj.setTexture(ao->throwTexture);																				// �ؽ��� �־��ְ�
				ao->obj.setTextureRect(sf::IntRect(ao->objSpr.x, ao->objSpr.y, 150, 100));											// �簢�� ���� ���ϰ�
				ao->obj.scale(1.0, 2.0f);																							// ũ�� �÷��ְ�

				ao->range_s = sf::Vector2f(this->getPosition().x - ENERGY_SIZE_X/2, this->getPosition().y  - ENERGY_SIZE_Y );
				ao->range_e = sf::Vector2f(this->getPosition().x , this->getPosition().y );
				ao->direct = sf::Vector2f(1, -2);																					// ����ü, ������

				ao->enemyDirect = sf::Vector2f(0.5, -0.4);
			}
			else {
				ao->objSpr = sf::Vector2f(PIC_SIZE_X * 5, PIC_SIZE_Y * 0);															// ��������Ʈ ����ְ�
				ao->obj.setTexture(ao->throwTexture);																				// �ؽ��� �־��ְ�
				ao->obj.setTextureRect(sf::IntRect(ao->objSpr.x, ao->objSpr.y, 150, 100));											// �簢�� ���� ���ϰ�
				ao->obj.scale(1.0f, 2.0f);																							// ũ�� �÷��ְ�

				ao->range_s = sf::Vector2f(this->getPosition().x - PIC_SIZE_X - ENERGY_SIZE_X/2, this->getPosition().y - ENERGY_SIZE_Y );
				ao->range_e = sf::Vector2f(this->getPosition().x , this->getPosition().y );

				ao->direct = sf::Vector2f(-1, -2);																					// ����ü, ����

				ao->enemyDirect = sf::Vector2f(-0.5, -0.4);
			}

			// ��ġ �����ְ�
			ao->damage = 3;																										// 1 HIT �� 3 ������
			ao->check = false;																									// check �ʱ�ȭ
			ao->isthrow = true;																									// ����ü��
			ao->hitcount = 10;																									// �� 10ȸ HIT
			this->setPosition(ao->range_e.x, ao->range_e.y);

			attackObjList.push_back(ao);
		}
		if (skillNumber == 3) {
			AttackObject* ao = new AttackObject(skillNumber, 3, 0.4);

			if (!ao->throwTexture.loadFromFile("./images/character/LGPL_sprite.png")) printf("Error loading vx_characters\n");		// �̹��� �ҷ�����
			if (this->getFacing()) {
				ao->objSpr = sf::Vector2f(PIC_SIZE_X * 3, PIC_SIZE_Y * 8);															// ��������Ʈ ����ְ�
				ao->obj.setTexture(ao->throwTexture);																				// �ؽ��� �־��ְ�
				ao->obj.setTextureRect(sf::IntRect(ao->objSpr.x, ao->objSpr.y, 150, 100));											// �簢�� ���� ���ϰ�
				ao->obj.scale(3.0, 1.0f);																							// ũ�� �÷��ְ�

				ao->range_s = sf::Vector2f(this->getPosition().x, this->getPosition().y - ENERGY_SIZE_Y / 2 * 3);
				ao->range_e = sf::Vector2f(this->getPosition().x + ENERGY_SIZE_X, this->getPosition().y + ENERGY_SIZE_Y / 2 * 3);

				ao->direct = sf::Vector2f(1, -0.1);																					// ����ü, ������

				ao->enemyDirect = sf::Vector2f(0.5, -0.4);
			}
			else {
				ao->objSpr = sf::Vector2f(PIC_SIZE_X * 3, PIC_SIZE_Y * 8);															// ��������Ʈ ����ְ�
				ao->obj.setTexture(ao->throwTexture);																				// �ؽ��� �־��ְ�
				ao->obj.setTextureRect(sf::IntRect(ao->objSpr.x, ao->objSpr.y, 150, 100));											// �簢�� ���� ���ϰ�
				ao->obj.scale(3.0f, 1.0f);																							// ũ�� �÷��ְ�

				ao->range_s = sf::Vector2f(this->getPosition().x - PIC_SIZE_X - ENERGY_SIZE_X, this->getPosition().y - ENERGY_SIZE_Y / 2 * 3);
				ao->range_e = sf::Vector2f(this->getPosition().x - PIC_SIZE_X, this->getPosition().y + ENERGY_SIZE_Y / 2 * 3);

				ao->direct = sf::Vector2f(-1, -0.1);																					// ����ü, ����

				ao->enemyDirect = sf::Vector2f(-0.5, -0.4);
			}

			// ��ġ �����ְ�
			ao->damage = 3;																										// 1 HIT �� 3 ������
			ao->check = false;																									// check �ʱ�ȭ
			ao->isthrow = true;																									// ����ü��
			ao->hitcount = 10;																									// �� 10ȸ HIT

			attackObjList.push_back(ao);
		}
	}
	else if(modelNumber == 3){ // Apache
		apache->canUseSkillCount[skillNumber]--;
		if (skillNumber == 0) {
			AttackObject* ao = new AttackObject(skillNumber, 10, 1);
			ao->damage = 10;					// ��Ÿ ���� 10
			ao->check = false;					// ���� �ȸ¾Ұ�
			ao->direct = sf::Vector2f(0, 0);		// ���� ����(����ü�� �ƴϴϱ�)
			ao->isthrow = false;				// ����ü �ƴϰ�
			if (this->getFacing()) {				// ������ �ٶ󺸰� ������
				ao->range_s = sf::Vector2f(this->getPosition().x - PIC_SIZE_X / 4, this->getPosition().y - PIC_SIZE_Y * 2); // ������ ���� ����
				ao->range_e = sf::Vector2f(this->getPosition().x + PIC_SIZE_X / 2, this->getPosition().y);
				ao->enemyDirect = sf::Vector2f(0.2, -1);	// ���� �˹� �ɶ� 0.2�� -1�� �����ϴ°� ���� �Ƹ��ٿ�
			}
			else {
				ao->range_s = sf::Vector2f(this->getPosition().x - PIC_SIZE_X / 2 - PIC_SIZE_X / 4 * 3, this->getPosition().y - PIC_SIZE_Y * 2);
				ao->range_e = sf::Vector2f(this->getPosition().x + PIC_SIZE_X / 4 - PIC_SIZE_X / 4 * 3, this->getPosition().y);
				ao->enemyDirect = sf::Vector2f(-0.2, -1);
			}
			attackObjList.push_back(ao);		// �� �������ְ� ����Ʈ�� �������
		}
		else if (skillNumber == 1) {				// ������ ���������� ���� ����
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
		else if (skillNumber == 3) {			// ���� ���� �̹����� ������ �ϱ� ������ ���ٸ��� ����
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
	}
	else if(modelNumber ==4){ // P.Jang
		jang->canUseSkillCount[skillNumber]--;
		if(skillNumber == 0){					//�Ϲ� ���� 'Q' �ʱ� ����
			AttackObject* ao = new AttackObject(skillNumber, 10, 1);
			ao->damage = 3;					// �Ϲ� ���� ������ 10���� �ʱ�ȭ
			ao->check = false;					// ���� ���� Ȯ��
			ao->direct = sf::Vector2f(0,0);		// ���� ���⿡ ���� �ʱ�ȭ
			ao->isthrow = false;				// ����ü(��Ÿ� ����)�� ���� �� �ʱ�ȭ
			if(this->getFacing()){				// ������ �ٶ󺸰� �ִ� ����
				ao->range_s = sf::Vector2f(this->getPosition().x-PIC_SIZE_X/4, this->getPosition().y-PIC_SIZE_Y*2); // ���� ��ǥ ����
				ao->range_e = sf::Vector2f(this->getPosition().x+PIC_SIZE_X/2, this->getPosition().y);				// �� ��ǥ ����
				ao->enemyDirect = sf::Vector2f(0.2, -1);	// �� �˹� �� ��ġ ����
			}
			else{	// ������ �ٶ󺸴� ����
				ao->range_s = sf::Vector2f(this->getPosition().x-PIC_SIZE_X/2-PIC_SIZE_X/4*3, this->getPosition().y-PIC_SIZE_Y*2);
				ao->range_e = sf::Vector2f(this->getPosition().x+PIC_SIZE_X/4-PIC_SIZE_X/4*3, this->getPosition().y);
				ao->enemyDirect = sf::Vector2f(-0.2, -1);
			}
			attackObjList.push_back(ao);		// �ʱ�ȭ �� ����Ʈ�� �Է�
		}
		else if(skillNumber == 1){				// Ư�� ���� '1' �ʱ� ����
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
		else if(skillNumber == 2){				// Ư�� ���� '2' �ʱ� ����
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
		else if(skillNumber == 3){			// Ư�� ���� '3' �̹����� ������ �ϱ� ������ Ư���� ���� �̹��� ����
			AttackObject* ao = new AttackObject(skillNumber, 0, 0);
			if (!ao->throwTexture.loadFromFile("./images/character/Jang_sprite.png")) printf( "Error loading vx_characters\n");	// �ش� �̹��� �ҷ�����
			ao->objSpr = sf::Vector2f(PIC_SIZE_X * 0, PIC_SIZE_Y * 6);															// ��������Ʈ �ۼ�
			ao->obj.setTexture(ao->throwTexture);																				// �ؽ���(��������Ʈ) ����
			ao->obj.setTextureRect(sf::IntRect(ao->objSpr.x, ao->objSpr.y,170,200));											// �ؽ���(��������Ʈ)�� ũ��� ��ǥ�� ����
			ao->obj.scale(4.0f, 4.0f);																							// �ؽ���(��������Ʈ)�� ũ�� ����
			ao->obj.setOrigin(85,100);																							// ��������Ʈ�� �߽��� �߾ӿ� ��ġ�ϵ��� ����
			ao->obj.setPosition(w_Width/2, w_Height/2);																			// ��������Ʈ�� ������ ����
			ao->damage = 0.003;																										// ������ ���´� ����
			ao->check = false;																									// ���� ���� �ʱ�ȭ
			ao->direct = sf::Vector2f(0,0);																						// ����ü ������ ����
			ao->isthrow = true;																									// ����ü�� �۵� ���� Ȯ��
			ao->range_s = sf::Vector2f(-w_Width, -w_Height);																	// ������ ���� ���� ��
			ao->range_e = sf::Vector2f(w_Width, w_Height);																		// ������ ���� �� ��
			ao->enemyDirect = sf::Vector2f(0, 0);																				// ���� ����ü ����
			attackObjList.push_back(ao);																						// ����Ʈ�� �߰�
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