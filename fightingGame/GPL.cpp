#include "GPL.hpp"

const int PIC_SIZE_X = 170;
const int PIC_SIZE_Y = 100;

GPL::~GPL(){ }

void GPL::useSkill(int skillnumber, int frameCount){
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
	
void GPL::skill_NormalAttack(int frameCount){
	// AttackObject 생성
	// list에 추가

	calculateSpriteNormalAttack(frameCount);
}

void GPL::skill_FinalAttack(int frameCount){
	// AttackObject 생성
	// list에 추가

	calculateSpriteFinalAttack(frameCount);
}

void GPL::skill_WindofSword(int frameCount){
	// AttackObject 생성
	// list에 추가

	calculateSpriteWindofSword(frameCount);
}

void GPL::skill_Ogonpogotovnosti(int frameCount){

}

void GPL::skill_Dash(int frameCount){

}

void GPL::loadCharacter(sf::Sprite &player){
	player.setTextureRect(sf::IntRect(this->getSpr().x, this->getSpr().y,170,100));
	player.scale(2.0f, 2.0f);
    player.setOrigin(85,50);
}

void GPL::calculateSpritePos(int step){
	this->setSpr(PIC_SIZE_X*step, 0);
}

void GPL::calculateSpriteNormalAttack(int frameCount){
	if(frameCount == 0 || frameCount == 1){
		this->setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 2);
	}
	else if(frameCount == 2 || frameCount == 3){
		this->setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 2);
	}
	else if(frameCount == 4 || frameCount == 5){
		this->setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 2);
	}
	else if(frameCount == 6 || frameCount == 7){
		this->setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 2);
	}
	else if(frameCount == 8 || frameCount == 9){
		this->setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 2);
	}
	else if(frameCount == 10 || frameCount == 11){
		this->setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 2);
	}
	else{
		this->setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 0);
	}	
}

void GPL::calculateSpriteBlock(){
	this->setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 0);
}

void GPL::calculateSpriteFinalAttack(int frameCount){
	if(frameCount == 0 || frameCount == 1){
		this->setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 4);	
	}
	else if(frameCount == 2 || frameCount == 3){
		this->setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 4);
	}
	else if(frameCount == 4 || frameCount == 5){
		this->setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 4);
	}
	else if(frameCount == 6 || frameCount == 7){
		this->setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 4);
	}
	else if(frameCount == 8 || frameCount == 9){
		this->setSpr(PIC_SIZE_X * 4, PIC_SIZE_Y * 4);
	}
	else if(frameCount == 10 || frameCount == 11){
		this->setSpr(PIC_SIZE_X * 4, PIC_SIZE_Y * 0);
	}
	else{
		this->setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 0);
	}	
}

void GPL::calculateSpriteWindofSword(int frameCount){
	if(frameCount == 0){
		this->setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 5);
	}
	else if(frameCount == 1){
		this->setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 4);
	}
	else if(frameCount == 2){
		this->setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 2);
	}
	else if(frameCount == 3){
		this->setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 4);
	}
	else if(frameCount == 4){
		this->setSpr(PIC_SIZE_X * 5, PIC_SIZE_Y * 5);
	}
	else if(frameCount == 5){
		this->setSpr(PIC_SIZE_X * 5, PIC_SIZE_Y * 0);
	}
	else if(frameCount == 6){
		this->setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 5);
	}
	else if(frameCount == 7){
		this->setSpr(PIC_SIZE_X * 4, PIC_SIZE_Y * 4);
	}
	else if(frameCount == 8){
		this->setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 5);
	}
	else if(frameCount == 9){
		this->setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 3);
	}
	else if(frameCount == 10){
		this->setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 3);
	}
	else if(frameCount == 11){
		this->setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 2);
	}
	else if(frameCount == 12){
		this->setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 2);
	}
	else if(frameCount == 13){
		this->setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 4);
	}
	else if(frameCount == 14){
		this->setSpr(PIC_SIZE_X * 5, PIC_SIZE_Y * 5);
	}
	else if(frameCount == 15){
		this->setSpr(PIC_SIZE_X * 5, PIC_SIZE_Y * 0);
	}
	else if(frameCount == 16){
		this->setSpr(PIC_SIZE_X * 2, PIC_SIZE_Y * 5);
	}
	else if(frameCount == 17){
		this->setSpr(PIC_SIZE_X * 4, PIC_SIZE_Y * 4);
	}
	else if(frameCount == 18){
		this->setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 5);
	}
	else if(frameCount == 19){
		this->setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 3);
	}
	else if(frameCount == 20){
		this->setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 5);
	}
	else if(frameCount == 21){
		this->setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 4);
	}
	else if(frameCount == 22){
		this->setSpr(PIC_SIZE_X * 1, PIC_SIZE_Y * 3);
	}
	else if(frameCount == 23){
		this->setSpr(PIC_SIZE_X * 3, PIC_SIZE_Y * 2);
	}
	else{
		this->setSpr(PIC_SIZE_X * 0, PIC_SIZE_Y * 0);
	}
}

void GPL::calculateSpriteOgonpogotovnosti(int frameCount){

}

void GPL::calculateSpriteDash(int frameCount){

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