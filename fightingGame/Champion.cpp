#include "Champion.hpp"

# define MIN_DIST_X 40
# define MIN_DIST_Y 440

// 생성자 -> 초기화 담당
Champion::Champion(int player, int m_number, int width, int height){
	this->player = player; // 플레이어 생성
	this->modelNumber = m_number; // 플레이어 스프라이트 번호 생성

	w_Width = width; // 너비
	w_Height = height; // 높이
	
	// 플레이어 1
	if(player == 1){
		facing = 1; // 오른쪽을 바라본다
		setPosition(50.0, MIN_DIST_Y);
		setSpr(0, 64);
		modelNumber = 1;
	}
	// 플레이어 2
	else{
		facing = 0; // 왼쪽을 바라본다
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

// 캐릭터 좌표를 지정해서 반환한다
void Champion::setPosition(float _x, float _y){
	pos.x = _x;
	pos.y = _y;
}

// 캐릭터 움직임을 작동
void Champion::move(float left, float right, float jump){
	if(left){
		if(facing==0) // 왼쪽을 바라볼 때
			pos.x = (pos.x - (left*speed)); // 앞으로 이동할 때
		else // 오른쪽을 바라볼 때
			pos.x = (pos.x - (left*speed/3*2)); // 뒤로 이동할 때
	}
	else if(right){
		if(facing ==0) // 왼쪽을 바라볼 때
			pos.x = (pos.x + (right*speed/3*2)); // 뒤로 이동할 때
		else // 오른쪽을 바라볼 때
			pos.x = (pos.x + (right*speed)); // 앞으로 이동할 때
	}

	if(pos.x < MIN_DIST_X) // x좌표가 왼쪽으로 충돌하는 지 검사
		pos.x = MIN_DIST_X; // 충돌하면 최소 x값 좌표
	else if(pos.x >= w_Width-MIN_DIST_X) // 오른쪽으로 충돌하는 지 검사
		pos.x = w_Width - MIN_DIST_X; // 충돌하면 최대 x값 좌표
	vy += (jump*speed/4); // 점프 시 변하는 y값
}

// Y좌표를 계산하는 함수
void Champion::caculatePosY(){
	pos.y += vy; // Y값에는 계속해서 vy가 더해진다
	vy += ay; // 
	// 최대 Y값보다 커질 경우에는 y값을 초기화 한다
	if(pos.y >= MIN_DIST_Y){
		pos.y = MIN_DIST_Y; // Y값은 최소로 정한다
		vy = 0; // 점프값은 0으로 정한다
	}

	if(pos.y == MIN_DIST_Y) // 땅위에 존재하면 땅위에 있다고 설정
		grounded = true;
	else // 땅 위에 존재하지 않으면 땅위에 없다고 설정
		grounded = false;
}

// 스프라이트 좌표를 가져온다
sf::Vector2<float> Champion::getSpr(){
	return this->spr;
}

// 스프라이트 좌표를 지정한다
void Champion::setSpr(float _x, float _y){
	spr.x = _x;
	spr.y = _y;
}

// 체력 값 가져오기
int Champion::getHp(){
	return this->hp;
}

// 체력 값 지정하기
void Champion::setHp(int _hp){
	this->hp = _hp;
}

// 마력 값 가져오기
int Champion::getMp(){
	return this->mp;
}

// 마력 값 지정하기
void Champion::setMp(int _mp){
	this->mp = _mp;
}

// 바라보는 방향 지정
void Champion::setFacing(int face){
	facing = face;
}

// 공격하는 지 확인
bool Champion::isAttacking(){
	return attack;
}

// 방어하는 지 확인
bool Champion::isBarrier(){
	return barrier;
}

// 공격 값을 지정
void Champion::setAttack(bool a){
	attack = a;
}

// 방어 값을 지정
void Champion::setBarrier(bool b){
	barrier = b;
}

// 챔피온을 그려봅시다 -> 뭔지 모르겠다 일단은
void Champion::drawChampion(){
	//draw champion
}

// 죽었는지 확인해봅시다 -> 죽으면 참 아니면 거짓
bool Champion::isDeath(){
	if(hp<=0) return true;
	else return false;
}

// 땅에 있는지 확인해봅시다 -> 땅에 있냐? 없냐?
bool Champion::isGrounded(){
	return grounded;
}

// 땅에 있는지 값을 정해봅시다 -> 땅이냐? 아니냐?
void Champion::setGrounded(bool g){
	grounded = g;
}

// 속도를 가져와봅시다
float Champion::getSpeed(){
	return speed;
}

// 속도를 지정해봅시다
void Champion::setSpeed(float s){
	speed = s;
}

// 캐릭터를 불러와 봅니다
void Champion::loadCharacter(sf::Sprite &player){
    player.setTextureRect(sf::IntRect(spr.x, spr.y,32,32)); // 스프라이트 좌표에서 크기를 정해봅니다
    player.scale(2.f, 2.f); // 크기를 키워봅니다
    player.setOrigin(16,16); // 플레이어의 원점을 지정해봅니다
}

// 스프라이트의 위치를 계산
void Champion::calculateSpritePos(int step){
	spr.x = (modelNumber-1)%4*96+32+32*step;
    spr.y = (modelNumber-1)/4*128+32+32*facing;
}

// 공격 스프라이트의 위치를 계산
void Champion::calculateSpritePunch(){
    spr.x = (modelNumber-1)%4*96+32+32*facing;
    spr.y = (modelNumber-1)/4*128;
}

// 방어 스프라이트의 위치를 계산
void Champion::calculateSpriteBlock(){
    spr.x = (modelNumber-1)%4*96+32+32*facing;
    spr.y = (modelNumber-1)/4*128+96;
}

// 다음 스킨을 계산한다
void Champion::nextSkin(){
    modelNumber = modelNumber%8+1; // 어떤 스프라이트로 변할 것인지 지정
	calculateSpritePos(0);  
}

// 대쉬 모드를 지정
void Champion::setDash(bool d){
	dash = d;
}

// 대쉬를 하고 반환
bool Champion::isDash(){
	return dash;
}