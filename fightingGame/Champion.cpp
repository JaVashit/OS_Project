#include "Champion.hpp"

const int MIN_DIST_X = 60;
const int MIN_DIST_Y = 340;

Champion::Champion(int player, int m_number, int width, int height){
	this->player = player;
	this->modelNumber = m_number;

	w_Width = width;
	w_Height = height;

	if(player == 1){
		facing = 1;
		setPosition(MIN_DIST_X, MIN_DIST_Y);
		setSpr(0, 0);
		modelNumber = 1;
	}
	else{
		facing = 0;
		setPosition(w_Width-MIN_DIST_X, MIN_DIST_Y);
		setSpr(96, 32);
		modelNumber = 2;
	}

	winScore = 0;
	hp = 100;
	mp = 100;
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
}

Champion::~Champion(){};

sf::Vector2<float> Champion::getPosition(){
	return this->pos;
}

void Champion::setPosition(float _x, float _y){
	pos.x = _x;
	pos.y = _y;
}

void Champion::move(float left, float right, float jump){
	if(left){
		if(facing==0)
			pos.x = (pos.x - (left*speed));
		else
			pos.x = (pos.x - (left*speed/3*2));
	}
	else if(right){
		if(facing ==0){
			pos.x = (pos.x + (right*speed/3*2)); 
		}
		else{
			pos.x = (pos.x + (right*speed));
		}
	}
	if(pos.x < MIN_DIST_X){
		pos.x = MIN_DIST_X;
	}
	else if(pos.x >= w_Width-MIN_DIST_X){
		pos.x = w_Width - MIN_DIST_X;
	}
	vy += (jump*2*speed*2);
}

void Champion::caculatePosXY(){
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
		/*if(vx>0){
			vx-= 0.1;
		}
		else{
			vx += 0.1;
		}*/
		if(pos.x < MIN_DIST_X){
			pos.x = MIN_DIST_X;
		}
		else if(pos.x >= w_Width-MIN_DIST_X){
			pos.x = w_Width - MIN_DIST_X;
		}
	}
}

sf::Vector2<float> Champion::getSpr(){
	return this->spr;
}

void Champion::setSpr(float _x, float _y){
	spr.x = _x;
	spr.y = _y;
}

float Champion::getHp(){
	return this->hp;
}


void Champion::setHp(float _hp){
	this->hp = _hp;
}


int Champion::getMp(){
	return this->mp;
}

void Champion::setFacing(int face){
	facing = face;
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

void Champion::loadCharacter(sf::Sprite &player, int n){
    player.setTextureRect(sf::IntRect(spr.x, spr.y,32,32));
    player.scale(2.f, 2.f);
    player.setOrigin(16,16);
}

void Champion::calculateSpritePos(int step, int n){
	spr.x = (modelNumber-1)%4*96+32+32*step;
    spr.y = (modelNumber-1)/4*128+32+32*facing;
}

void Champion::calculateSpritePunch(int n){
    spr.x = (modelNumber-1)%4*96+32+32*facing;
    spr.y = (modelNumber-1)/4*128;
}

void Champion::calculateSpriteBlock(int n){
    spr.x = (modelNumber-1)%4*96+32+32*facing;
    spr.y = (modelNumber-1)/4*128+96;
}

void Champion::nextSkin(){
    modelNumber = modelNumber%8+1;
	calculateSpritePos(0, 0);  
}

void Champion::setDash(bool d){
	dash = d;
}

bool Champion::isDash(){
	return dash;
}

void Champion::playerWin(){
	winScore++;
}

bool Champion::getFacing(){
	return facing;
}

int Champion::getWinScore(){
	return winScore;
}