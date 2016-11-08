#include "Champion.hpp"

Champion::Champion(int player, int m_number){
	this->player = player;
	this->modelNumber = m_number;

	if(player == 1){
		facing = 0;
	}
	else{
		facing = 1;
	}

	hp = 100;
	mp = 0;
	speed = 1.0;

	attack = false;
	barrier = false;

	selectSkin = false;
}

Champion::~Champion(){};

sf::Vector2<float> Champion::getPosition(){
	return this->pos;
}

void Champion::setPosition(float _x, float _y){
	pos.x = _x;
	pos.y = _y;
}

int Champion::getHp(){
	return this->hp;
}


void Champion::setHp(int _hp){
	this->hp = _hp;
}


int Champion::getMp(){
	return this->mp;
}


void Champion::setMp(int _mp){
	this->mp = _mp;
}


bool Champion::isAttacking(){
	return attack;
}


bool Champion::isBarrier(){
	return barrier;
}


void Champion::setAttack(bool a){
	attack = a;
}


void Champion::setBarrier(bool b){
	barrier = b;
}


void Champion::drawChampion(){
	//draw champion
}


bool Champion::isDeath(){
	if(hp<=0) return true;
	else return false;
}


bool Champion::isGrounded(){
	return grounded;
}


void Champion::setGrounded(bool g){
	grounded = g;
}


float Champion::getSpeed(){
	return speed;
}


void Champion::setSpeed(float s){
	speed = s;
}

void Champion::loadCharacter(sf::Sprite &player){
    
    player.setTextureRect(sf::IntRect(spr.x, spr.y,32,32));
    player.scale(2.f, 2.f);
    player.setOrigin(16,16);
}

void Champion::calculateSpritePos(int step){
	spr.x = (modelNumber-1)%4*96+32+32*step;
    spr.y = (modelNumber-1)/4*128+32+32*facing;
}

void Champion::calculateSpritePunch(){
    spr.x = (modelNumber-1)%4*96+32+32*facing;
    spr.y = (modelNumber-1)/4*128;
}

void Champion::calculateSpriteBlock(){
    spr.x = (modelNumber-1)%4*96+32+32*facing;
    spr.y = (modelNumber-1)/4*128+96;
}

void Champion::nextSkin(){
    modelNumber = modelNumber%8+1;
	calculateSpritePos(0);  
}
