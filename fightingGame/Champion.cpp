#include "Champion.hpp"

# define MIN_DIST_X 40
# define MIN_DIST_Y 440

// ������ -> �ʱ�ȭ ���
Champion::Champion(int player, int m_number, int width, int height){
	this->player = player; // �÷��̾� ����
	this->modelNumber = m_number; // �÷��̾� ��������Ʈ ��ȣ ����

	w_Width = width; // �ʺ�
	w_Height = height; // ����
	
	// �÷��̾� 1
	if(player == 1){
		facing = 1; // �������� �ٶ󺻴�
		setPosition(50.0, MIN_DIST_Y);
		setSpr(0, 64);
		modelNumber = 1;
	}
	// �÷��̾� 2
	else{
		facing = 0; // ������ �ٶ󺻴�
		setPosition(750.0, MIN_DIST_Y);
		setSpr(96, 32);
		modelNumber = 2;
	}

	hp = 100;
	mp = 100;
	speed = 0.01;
	ay = 0.0005;
	vy = 0;

	attack = false;
	barrier = false;

	selectSkin = false;
}

Champion::~Champion(){};

sf::Vector2<float> Champion::getPosition(){
	return this->pos;
}

// ĳ���� ��ǥ�� �����ؼ� ��ȯ�Ѵ�
void Champion::setPosition(float _x, float _y){
	pos.x = _x;
	pos.y = _y;
}

// ĳ���� �������� �۵�
void Champion::move(float left, float right, float jump){
	if(left){
		if(facing==0) // ������ �ٶ� ��
			pos.x = (pos.x - (left*speed)); // ������ �̵��� ��
		else // �������� �ٶ� ��
			pos.x = (pos.x - (left*speed/3*2)); // �ڷ� �̵��� ��
	}
	else if(right){
		if(facing ==0) // ������ �ٶ� ��
			pos.x = (pos.x + (right*speed/3*2)); // �ڷ� �̵��� ��
		else // �������� �ٶ� ��
			pos.x = (pos.x + (right*speed)); // ������ �̵��� ��
	}

	if(pos.x < MIN_DIST_X) // x��ǥ�� �������� �浹�ϴ� �� �˻�
		pos.x = MIN_DIST_X; // �浹�ϸ� �ּ� x�� ��ǥ
	else if(pos.x >= w_Width-MIN_DIST_X) // ���������� �浹�ϴ� �� �˻�
		pos.x = w_Width - MIN_DIST_X; // �浹�ϸ� �ִ� x�� ��ǥ
	vy += (jump*speed/4); // ���� �� ���ϴ� y��
}

// Y��ǥ�� ����ϴ� �Լ�
void Champion::caculatePosY(){
	pos.y += vy; // Y������ ����ؼ� vy�� ��������
	vy += ay; // 
	// �ִ� Y������ Ŀ�� ��쿡�� y���� �ʱ�ȭ �Ѵ�
	if(pos.y >= MIN_DIST_Y){
		pos.y = MIN_DIST_Y; // Y���� �ּҷ� ���Ѵ�
		vy = 0; // �������� 0���� ���Ѵ�
	}

	if(pos.y == MIN_DIST_Y) // ������ �����ϸ� ������ �ִٰ� ����
		grounded = true;
	else // �� ���� �������� ������ ������ ���ٰ� ����
		grounded = false;
}

// ��������Ʈ ��ǥ�� �����´�
sf::Vector2<float> Champion::getSpr(){
	return this->spr;
}

// ��������Ʈ ��ǥ�� �����Ѵ�
void Champion::setSpr(float _x, float _y){
	spr.x = _x;
	spr.y = _y;
}

// ü�� �� ��������
int Champion::getHp(){
	return this->hp;
}

// ü�� �� �����ϱ�
void Champion::setHp(int _hp){
	this->hp = _hp;
}

// ���� �� ��������
int Champion::getMp(){
	return this->mp;
}

// ���� �� �����ϱ�
void Champion::setMp(int _mp){
	this->mp = _mp;
}

// �ٶ󺸴� ���� ����
void Champion::setFacing(int face){
	facing = face;
}

// �����ϴ� �� Ȯ��
bool Champion::isAttacking(){
	return attack;
}

// ����ϴ� �� Ȯ��
bool Champion::isBarrier(){
	return barrier;
}

// ���� ���� ����
void Champion::setAttack(bool a){
	attack = a;
}

// ��� ���� ����
void Champion::setBarrier(bool b){
	barrier = b;
}

// è�ǿ��� �׷����ô� -> ���� �𸣰ڴ� �ϴ���
void Champion::drawChampion(){
	//draw champion
}

// �׾����� Ȯ���غ��ô� -> ������ �� �ƴϸ� ����
bool Champion::isDeath(){
	if(hp<=0) return true;
	else return false;
}

// ���� �ִ��� Ȯ���غ��ô� -> ���� �ֳ�? ����?
bool Champion::isGrounded(){
	return grounded;
}

// ���� �ִ��� ���� ���غ��ô� -> ���̳�? �ƴϳ�?
void Champion::setGrounded(bool g){
	grounded = g;
}

// �ӵ��� �����ͺ��ô�
float Champion::getSpeed(){
	return speed;
}

// �ӵ��� �����غ��ô�
void Champion::setSpeed(float s){
	speed = s;
}

// ĳ���͸� �ҷ��� ���ϴ�
void Champion::loadCharacter(sf::Sprite &player){
    player.setTextureRect(sf::IntRect(spr.x, spr.y,32,32)); // ��������Ʈ ��ǥ���� ũ�⸦ ���غ��ϴ�
    player.scale(2.f, 2.f); // ũ�⸦ Ű�����ϴ�
    player.setOrigin(16,16); // �÷��̾��� ������ �����غ��ϴ�
}

// ��������Ʈ�� ��ġ�� ���
void Champion::calculateSpritePos(int step){
	spr.x = (modelNumber-1)%4*96+32+32*step;
    spr.y = (modelNumber-1)/4*128+32+32*facing;
}

// ���� ��������Ʈ�� ��ġ�� ���
void Champion::calculateSpritePunch(){
    spr.x = (modelNumber-1)%4*96+32+32*facing;
    spr.y = (modelNumber-1)/4*128;
}

// ��� ��������Ʈ�� ��ġ�� ���
void Champion::calculateSpriteBlock(){
    spr.x = (modelNumber-1)%4*96+32+32*facing;
    spr.y = (modelNumber-1)/4*128+96;
}

// ���� ��Ų�� ����Ѵ�
void Champion::nextSkin(){
    modelNumber = modelNumber%8+1; // � ��������Ʈ�� ���� ������ ����
	calculateSpritePos(0);  
}

// �뽬 ��带 ����
void Champion::setDash(bool d){
	dash = d;
}

// �뽬�� �ϰ� ��ȯ
bool Champion::isDash(){
	return dash;
}