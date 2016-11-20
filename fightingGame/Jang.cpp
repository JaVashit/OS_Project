#include "Jang.h"

const int PIC_SIZE_X = 170;
const int PIC_SIZE_Y = 100;

Jang::~Jang(){ }

void Jang::useSkill(int skillnumber, int frameCount){
	if(skillnumber == 0){
		skill_NormalAttack(frameCount);
	}
	else if(skillnumber == 1){
		skill_FinalAttack(frameCount);
	}
	else if(skillnumber == 2){
		skill_WindofSword(frameCount);
	}
	else if(skillnumber == 3){
		skill_Ogonpogotovnosti(frameCount);
	}
	else if(skillnumber == 4){
		skill_Dash(frameCount);
	}
}
	
/* 20161119 */
void Jang::crowdControlHit(float &frameCount){		//cc�¾�����
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

void Jang::insertAOList(int skillNumber){
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
		if (!ao->throwTexture.loadFromFile("./images/character/Jang_sprite.png")) printf( "Error loading vx_characters\n");	// �̹��� �ҷ�����
		ao->objSpr = sf::Vector2f(PIC_SIZE_X * 0, PIC_SIZE_Y * 6);															// ��������Ʈ ����ְ�
		ao->obj.setTexture(ao->throwTexture);																				// �ؽ��� �־��ְ�
		ao->obj.setTextureRect(sf::IntRect(ao->objSpr.x, ao->objSpr.y,170,200));											// �簢�� ���� ���ϰ�
		ao->obj.scale(4.0f, 4.0f);																							// ũ�� �÷��ְ�
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
	else if(skillNumber == 4){
		
	}
}
/* 20161119 */

void Jang::skill_NormalAttack(int frameCount){
	// AttackObject ����
	// list�� �߰�

	calculateSpriteNormalAttack(frameCount);
}

void Jang::skill_FinalAttack(int frameCount){
	// AttackObject ����
	// list�� �߰�

	calculateSpriteFinalAttack(frameCount);
}

void Jang::skill_WindofSword(int frameCount){
	// AttackObject ����
	// list�� �߰�

	calculateSpriteWindofSword(frameCount);
}

void Jang::skill_Ogonpogotovnosti(int frameCount){

}

void Jang::skill_Dash(int frameCount){

}

/* 20161119 */
void Jang::hit_KnockBack(int frameCount){
	calculateSpriteKnockBack(frameCount);
}

void Jang::hit_stun(int frameCount){
	calculateSpriteStun(frameCount);
}
/* 20161119 */

void Jang::loadCharacter(sf::Sprite &player){
	player.setTextureRect(sf::IntRect(this->getSpr().x, this->getSpr().y,170,100));
	player.scale(2.0f, 2.0f);
    player.setOrigin(85,50);
}

void Jang::calculateSpritePos(int step){
	this->setSpr(PIC_SIZE_X*step, 0);
}

// �Ϲ� ���� 'Q' ��ư ���� �� ����
void Jang::calculateSpriteNormalAttack(int frameCount){
	if(frameCount == 0 || frameCount == 1)
		this->setSpr(PIC_SIZE_X * 4, PIC_SIZE_Y * 0);
	else if(frameCount == 2 || frameCount == 3)
		this->setSpr(PIC_SIZE_X * 5, PIC_SIZE_Y * 0);
	else if(frameCount == 4 || frameCount == 5)
		this->setSpr(PIC_SIZE_X * 4, PIC_SIZE_Y * 0);
	else
		this->setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 0); // ��� ����	
}

// ��� 'S' ��ư ���� �� ����
void Jang::calculateSpriteBlock(){
	this->setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 0);
}

// Ư�� ���� '1' ��ư Ŭ�� �� ������ ���
void Jang::calculateSpriteFinalAttack(int frameCount){
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
		this->setSpr(PIC_SIZE_X * 7, PIC_SIZE_Y * 3);
	else
		this->setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 0);	
}

// Ư�� ���� '2' ��ư Ŭ�� �� ������ ���
void Jang::calculateSpriteWindofSword(int frameCount){
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
		this->setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 5);
	else
		this->setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 0);
}

// Ư�� ���� '3' ��ư Ŭ�� �� ������ ���
void Jang::calculateSpriteOgonpogotovnosti(int frameCount){

}

/* 20161119 */
// �˹� ǥ��
void Jang::calculateSpriteKnockBack(int frameCount){
	if(frameCount < 2)
		this->setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 1);
	else 
		this->setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 1);
}

// �������� �Ծ��� ���
void Jang::calculateSpriteStun(int frameCount){
	if(frameCount < 2){
		this->setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 0);	
	}
	else if(frameCount < 4){
		this->setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 0);
	}
}
/* 20161119 */

void Jang::calculateSpriteDash(int frameCount){

}

void Jang::setSkillNumber(int skillNumber){
	this->skillNumber = skillNumber;
}

int Jang::getSkillNumber(){
	return skillNumber;
}

int Jang::getSkillFrameTotal(){
	return skillFrame[skillNumber];
}

/* 20161119 */
int Jang::getNecessaryMana(int skillNumber){
	return necessaryMana[skillNumber];
}

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

void Jang::updateAOList(){
	for(auto ao = attackObjList.begin(); ao != attackObjList.end(); ao++){
		if((*ao)->isthrow == false){								// ����ü�� �ƴ� �͵�
			if((*ao)->skillNumber == 0){							// 0,1,2�� ��ų�� ������ ���� ���� (ĳ���� ���� �������� �ϱ� ������)
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
			if(!isAttacking())						// ����ü�� �ƴϱ� ������ ������ ������ �˾Ƽ� ���� ���Ѿ� ��
				(*ao)->check = true;
		}
		else{
			if((*ao)->skillNumber == 3){			// ���� ������ ������ �Ϻη� �ɰ�����
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
				}
				else{
					(*ao)->check = true;
				}
				(*ao)->obj.setTextureRect(sf::IntRect((*ao)->objSpr.x, (*ao)->objSpr.y,PIC_SIZE_X,PIC_SIZE_Y*2)); // ������ �÷����� �׸� ���� �������ּ�
				(*ao)->obj.setPosition(w_Width/2, w_Height/2+200);
			}
			else{
				(*ao)->range_s += (*ao)->direct * (*ao)->speed;													// �̰� Ȥ�ó� �ʿ��ϸ� ���� ����
				(*ao)->range_e += (*ao)->direct * (*ao)->speed;
				if((*ao)->range_e.x < 0 || (*ao)->range_s.x > w_Width || (*ao)->range_e.y > 400 || (*ao)->range_s.y < 0){
					(*ao)->check = true;
				}
			}
		}
		(*ao)->frameCount += 0.02;	// ����ü�� ĳ������ frameCount�� �����ϱ� ���� �����߰�, �ӵ��� ĳ���Ͷ� �Ȱ���
	}
}

void Jang::detectCollision(Champion &champion, float &enemyFrameCount){ // �������� �����ϴ� ����Ʈ�ø���
	float left		= champion.getPosition().x - PIC_SIZE_X/4.0*3.0;
	float right		= champion.getPosition().x;
	float top		= champion.getPosition().y - PIC_SIZE_Y*2.0/8.0*7.0;
	float bottom	= champion.getPosition().y;
	for(auto ao = attackObjList.begin(); ao!=attackObjList.end(); ao++){
		if(((*ao)->range_s.x < left && (*ao)->range_e.x > left) || ((*ao)->range_s.x < right && (*ao)->range_e.x > right)){
			if(((*ao)->range_s.y < top && (*ao)->range_e.y > top) || ((*ao)->range_s.y < bottom && (*ao)->range_e.y > bottom)){
				// �¾���
				if((*ao)->skillNumber == 0){	// ��Ÿ ������ ������ ���� ��
					(*ao)->check = true;
					if(champion.isBarrier()) champion.setHp(champion.getHp()-(*ao)->damage*0.2);
					else{
						champion.isKnockBack = true;
						enemyFrameCount = 0;
						champion.setHp(champion.getHp()-(*ao)->damage);
						if(this->getMp()<96)
							this->setMp(this->getMp()+5);
						champion.vx = (*ao)->enemyDirect.x;
						champion.vy = (*ao)->enemyDirect.y;
					}
					if(champion.getHp() < 0) champion.setHp(0);
				}
				else if((*ao)->skillNumber == 1 && this->getMp()>30){  // �������ϰ� ������ ������ ���̵�
					(*ao)->check = true;
					if(champion.isBarrier()) champion.setHp(champion.getHp()-(*ao)->damage*0.2);
					else{
						champion.isKnockBack = true;
						enemyFrameCount = 0;
						champion.setHp(champion.getHp()-(*ao)->damage);
						if(this->getMp()>30)
							this->setMp(this->getMp()-30);
						champion.vx = (*ao)->enemyDirect.x;
						champion.vy = (*ao)->enemyDirect.y;
					}
					if(champion.getHp() < 0) champion.setHp(0);
				}
				else if((*ao)->skillNumber == 2 && this->getMp()>50){ // �ٶ��� ��ó ������ ������ ���� ��
					(*ao)->check = false;
					if(champion.isBarrier()) champion.setHp(champion.getHp()-(*ao)->damage*0.2);
					else{ 
						champion.isStun = true;
						enemyFrameCount = 0;
						champion.setHp(champion.getHp()-(*ao)->damage);
						if(this->getMp()>50)
							this->setMp(this->getMp()-50);
					}
					if(champion.getHp() < 0) champion.setHp(0);
				}
				else if((*ao)->skillNumber == 3 && this->getMp()>80){  // �ø����� ������ ���� �� (��� ���� ����)
					int ran = rand()%30;
					int ran2 = rand()%30;
					champion.isStun = true;
					enemyFrameCount = 0;
					if(this->getMp()>80)
						this->setMp(this->getMp()-80);
					sf::Vector2f direct = sf::Vector2f(w_Width/2+(ran-15) - champion.getPosition().x, w_Height/2+(ran2-15) - champion.getPosition().y);
					champion.setPosition(champion.getPosition().x + direct.x * champion.getSpeed()/8, champion.getPosition().y + direct.y * champion.getSpeed());
				}
			}
		}
	}

};
/* 20161119 */