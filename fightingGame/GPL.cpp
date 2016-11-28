#include "GPL.hpp"

const int PIC_SIZE_X = 170;
const int PIC_SIZE_Y = 100;

GPL::~GPL(){ }

void GPL::useSkill(int skillnumber, int frameCount, Champion &c){ // ��ų �ߵ�
	if(skillnumber == 0){
		skill_NormalAttack(frameCount, c);
	}
	else if(skillnumber == 1){
		skill_FinalAttack(frameCount, c);
	}
	else if(skillnumber == 2){
		skill_WindofSword(frameCount, c);
	}
	else if(skillnumber == 3){
		skill_Ogonpogotovnosti(frameCount, c);
	}
}
	
void GPL::skill_NormalAttack(int frameCount, Champion &c){ // Ȥ�ó� �ٸ��� �Ұ� ������� ���� ����
	calculateSpriteNormalAttack(frameCount, c);
}

void GPL::skill_FinalAttack(int frameCount, Champion &c){
	calculateSpriteFinalAttack(frameCount, c);
}

void GPL::skill_WindofSword(int frameCount, Champion &c){
	calculateSpriteWindofSword(frameCount, c);
}

void GPL::skill_Ogonpogotovnosti(int frameCount, Champion &c){
	calculateSpriteOgonpogotovnosti(frameCount, c);
}

void GPL::hit_KnockBack(int frameCount, Champion &c){
	calculateSpriteKnockBack(frameCount, c);
}

void GPL::hit_stun(int frameCount, Champion &c){
	calculateSpriteStun(frameCount, c);
}

void GPL::loadCharacter(sf::Sprite &player, Champion &c){
	player.setTextureRect(sf::IntRect(c.getSpr().x, c.getSpr().y,PIC_SIZE_X,PIC_SIZE_Y));
	player.scale(2.0f, 2.0f);
    player.setOrigin(PIC_SIZE_X/2,PIC_SIZE_Y/2);
}

void GPL::calculateSpritePos(Champion &c){
	c.setSpr(PIC_SIZE_X*0, 0);
}

void GPL::calculateSpriteNormalAttack(int frameCount, Champion &c){  // ������ ī��Ʈ�� float�ε� int�� �Ѱܼ� ������ �ӵ��� �ٲ�� �ɰ��� �˾Ƽ� ������ �ٸ��ָ��
	if(frameCount == 0 || frameCount == 1){
		c.setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 2);
	}
	else if(frameCount == 2 || frameCount == 3){
		c.setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 2);
	}
	else if(frameCount == 4 || frameCount == 5){
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 2);
	}
	else if(frameCount == 6 || frameCount == 7){
		c.setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 2);
	}
	else if(frameCount == 8 || frameCount == 9){
		c.setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 2);
	}
	else if(frameCount == 10 || frameCount == 11){
		c.setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 2);
	}
	else{
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 0);
	}	
}

void GPL::calculateSpriteBlock(Champion &c){
	c.setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 0);
}

void GPL::calculateSpriteFinalAttack(int frameCount, Champion &c){
	if(frameCount == 0 || frameCount == 1){
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 4);	
	}
	else if(frameCount == 2 || frameCount == 3){
		c.setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 4);
	}
	else if(frameCount == 4 || frameCount == 5){
		c.setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 4);
	}
	else if(frameCount == 6 || frameCount == 7){
		c.setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 4);
	}
	else if(frameCount == 8 || frameCount == 9){
		c.setSpr(PIC_SIZE_X * 4, PIC_SIZE_Y * 4);
	}
	else if(frameCount == 10 || frameCount == 11){
		c.setSpr(PIC_SIZE_X * 4, PIC_SIZE_Y * 0);
	}
	else{
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 0);
	}
}

void GPL::calculateSpriteWindofSword(int frameCount, Champion &c){
	if(frameCount == 0){
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 5);
	}
	else if(frameCount == 1){
		c.setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 4);
	}
	else if(frameCount == 2){
		c.setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 2);
	}
	else if(frameCount == 3){
		c.setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 4);
	}
	else if(frameCount == 4){
		c.setSpr(PIC_SIZE_X * 5, PIC_SIZE_Y * 5);
	}
	else if(frameCount == 5){
		c.setSpr(PIC_SIZE_X * 5, PIC_SIZE_Y * 0);
	}
	else if(frameCount == 6){
		c.setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 5);
	}
	else if(frameCount == 7){
		c.setSpr(PIC_SIZE_X * 4, PIC_SIZE_Y * 4);
	}
	else if(frameCount == 8){
		c.setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 5);
	}
	else if(frameCount == 9){
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 3);
	}
	else if(frameCount == 10){
		c.setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 3);
	}
	else if(frameCount == 11){
		c.setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 2);
	}
	else if(frameCount == 12){
		c.setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 2);
	}
	else if(frameCount == 13){
		c.setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 4);
	}
	else if(frameCount == 14){
		c.setSpr(PIC_SIZE_X * 5, PIC_SIZE_Y * 5);
	}
	else if(frameCount == 15){
		c.setSpr(PIC_SIZE_X * 5, PIC_SIZE_Y * 0);
	}
	else if(frameCount == 16){
		c.setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 5);
	}
	else if(frameCount == 17){
		c.setSpr(PIC_SIZE_X * 4, PIC_SIZE_Y * 4);
	}
	else if(frameCount == 18){
		c.setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 5);
	}
	else if(frameCount == 19){
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 3);
	}
	else if(frameCount == 20){
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 5);
	}
	else if(frameCount == 21){
		c.setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 4);
	}
	else if(frameCount == 22){
		c.setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 3);
	}
	else if(frameCount == 23){
		c.setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 2);
	}
	else{
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 0);
	}
}

void GPL::calculateSpriteOgonpogotovnosti(int frameCount, Champion &c){
	
}

void GPL::calculateSpriteKnockBack(int frameCount, Champion &c){
	if(frameCount < 4){
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 1);	
	}
	else if(frameCount < 8){
		c.setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 1);
	}
	else {
		c.setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 1);
	}
}

void GPL::calculateSpriteStun(int frameCount, Champion &c){
	if(frameCount < 2){
		c.setSpr(PIC_SIZE_X * 6, PIC_SIZE_Y * 0);	
	}
	else if(frameCount < 4){
		c.setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 1);
	}
}

void GPL::setSkillNumber(int skillNumber){
	this->skillNumber = skillNumber;
}

int GPL::getSkillNumber(){
	return skillNumber;
}

int GPL::getSkillFrameTotal(){
	return skillFrame[skillNumber];
}

int GPL::getCanUseSkillCount(int skillNumber){
	return canUseSkillCount[skillNumber];
}

void GPL::updateAOList(Champion &c){
	for(auto ao = c.attackObjList.begin(); ao != c.attackObjList.end(); ao++){
		if((*ao)->isthrow == false){								// ����ü�� �ƴ� �͵�
			if((*ao)->skillNumber == 0){							// 0,1,2�� ��ų�� ������ ���� ���� (ĳ���� ���� �������� �ϱ� ������)
				if(c.getFacing()){
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
					(*ao)->range_s = sf::Vector2f(c.getPosition().x-PIC_SIZE_X/3, c.getPosition().y-PIC_SIZE_Y);
					(*ao)->range_e = sf::Vector2f(c.getPosition().x-PIC_SIZE_X/3+PIC_SIZE_X, c.getPosition().y-PIC_SIZE_Y/4);
				}
				else{
					(*ao)->range_s = sf::Vector2f(c.getPosition().x-PIC_SIZE_X+PIC_SIZE_X/3-PIC_SIZE_X, c.getPosition().y-PIC_SIZE_Y);
					(*ao)->range_e = sf::Vector2f(c.getPosition().x-PIC_SIZE_X+PIC_SIZE_X/3, c.getPosition().y-PIC_SIZE_Y/4);
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
			if(!c.isAttacking())						// ����ü�� �ƴϱ� ������ ������ ������ �˾Ƽ� ���� ���Ѿ� ��
				(*ao)->check = true;
		}
		else{
			if((*ao)->skillNumber == 3){			// ���� ������ ������ �Ϻη� �ɰ�����
				if((*ao)->frameCount < 2){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 0, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 4){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 1, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 6){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 0, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 8){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 1, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 10){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 0, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 12){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 1, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 14){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 0, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 16){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 1, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 18){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 2, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 20){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 1, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 22){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 2, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 24){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 1, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 26){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 2, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 28){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 1, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 30){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 2, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 32){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 3, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 34){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 2, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 36){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 3, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 38){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 2, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 40){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 3, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 42){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 2, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 44){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 3, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 46){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 4, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 48){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 3, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 50){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 4, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 52){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 3, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 54){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 4, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 56){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 3, PIC_SIZE_Y * 6);
				}
				else if((*ao)->frameCount < 58){
					(*ao)->objSpr = sf::Vector2f(PIC_SIZE_X * 4, PIC_SIZE_Y * 6);
				}
				else{
					(*ao)->check = true;
				}
				(*ao)->obj.setTextureRect(sf::IntRect((*ao)->objSpr.x, (*ao)->objSpr.y,PIC_SIZE_X,PIC_SIZE_Y*2)); // ������ �÷����� �׸� ���� �������ּ�
				(*ao)->obj.setPosition(c.w_Width/2, c.w_Height/2);
			}
			else{
				(*ao)->range_s += (*ao)->direct * (*ao)->speed;													// �̰� Ȥ�ó� �ʿ��ϸ� ���� ����
				(*ao)->range_e += (*ao)->direct * (*ao)->speed;
				if((*ao)->range_e.x < 0 || (*ao)->range_s.x > c.w_Width || (*ao)->range_e.y > 400 || (*ao)->range_s.y < 0){
					(*ao)->check = true;
				}
			}
		}
		(*ao)->frameCount += 0.02;	// ����ü�� ĳ������ frameCount�� �����ϱ� ���� �����߰�, �ӵ��� ĳ���Ͷ� �Ȱ���
	}
}

void GPL::detectCollision(class Champion &champion, std::list<struct AttackObject*> &aoList, std::list<struct hitImage*> &hitList, float &enemyFrameCount, int time, bool sound){ // �������� �����ϴ� ����Ʈ�ø���
	float left		= champion.getPosition().x - PIC_SIZE_X/4.0*3.0;
	float right		= champion.getPosition().x;
	float top		= champion.getPosition().y - PIC_SIZE_Y*2.0/8.0*7.0;
	float bottom	= champion.getPosition().y;
	for(auto ao = aoList.begin(); ao!=aoList.end(); ao++){
		if(((*ao)->range_s.x < left && (*ao)->range_e.x > left) || ((*ao)->range_s.x < right && (*ao)->range_e.x > right)){
			if(((*ao)->range_s.y < top && (*ao)->range_e.y > top) || ((*ao)->range_s.y < bottom && (*ao)->range_e.y > bottom)){
				// �¾���
				if((*ao)->skillNumber == 0){	// ��Ÿ ������ ������ ���� ��
					hitImage* hit = new hitImage(champion.getPosition());
					hitList.push_back(hit);
					(*ao)->check = true;
					if(champion.isBarrier()) champion.setHp(champion.getHp()-(*ao)->damage*0.2);
					else{
						if(sound) mGPL.play();
						champion.isKnockBack = true;
						enemyFrameCount = 0;
						champion.setHp(champion.getHp()-(*ao)->damage);
						champion.vx = (*ao)->enemyDirect.x;
						champion.vy = (*ao)->enemyDirect.y;
					}
					if(champion.getHp() < 0) champion.setHp(0);
				}
				else if((*ao)->skillNumber == 1){  // �������ϰ� ������ ������ ���̵�
					(*ao)->check = true;
					hitImage* hit = new hitImage(champion.getPosition());
					hitList.push_back(hit);
					if(champion.isBarrier()) champion.setHp(champion.getHp()-(*ao)->damage*0.2);
					else{
						if(sound) arrowGPL.play();	
						champion.isKnockBack = true;
						enemyFrameCount = 0;
						champion.setHp(champion.getHp()-(*ao)->damage);
						champion.vx = (*ao)->enemyDirect.x;
						champion.vy = (*ao)->enemyDirect.y;
					}
					if(champion.getHp() < 0) champion.setHp(0);
				}
				else if((*ao)->skillNumber == 2){ // �ٶ��� ��ó ������ ������ ���� ��
					if(time%80 == 0){
						hitImage* hit = new hitImage(champion.getPosition());
						hitList.push_back(hit);
						if(sound) arrowGPL.play();
					}
					(*ao)->check = false;
					if(champion.isBarrier()) champion.setHp(champion.getHp()-(*ao)->damage*0.2);
					else{
						champion.isStun = true;
						enemyFrameCount = 0;
						champion.setHp(champion.getHp()-(*ao)->damage);
					}
					if(champion.getHp() < 0) champion.setHp(0);
				}
				else if((*ao)->skillNumber == 3){  // �ø����� ������ ���� �� (��� ���� ����)
					int ran = rand()%30;
					int ran2 = rand()%30;
					champion.isStun = true;
					enemyFrameCount = 0;
					sf::Vector2f direct = sf::Vector2f(champion.w_Width/2+(ran-15) - champion.getPosition().x, champion.w_Height/2+(ran2-15) - champion.getPosition().y);
					champion.setPosition(champion.getPosition().x + direct.x * champion.getSpeed()/8, champion.getPosition().y + direct.y * champion.getSpeed());
				}
			}
		}
	}
};

void GPL::setCanUseSkillCount(int skillNumber, int maxCount) {
	canUseSkillCount[skillNumber] = maxCount;
}