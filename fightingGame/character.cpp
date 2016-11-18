#include <SFML/Graphics.hpp>
#include <vector>
#include "character.hpp"

// 생성자 -> 초기화 담당
Character::Character(int player){
    
	// 플레이어 1의 초기 인덱스 값
    if (player == 1) {
        pos.x = 50; // 플레이어 1의 위치 x값
        spr.x = 96; // 플레이어 1의 스프라이트 x값
        spr.y = 32; // 플레이어 1의 스프라이트 y값
        facing = 1; // 오른쪽을 바라보고 있는 상태
        model = 1; // 오른쪽을 바라보는 스프라이트의 인덱스
    }
	// 플레이어 2의 초기 인덱스 값
    else {
        pos.x = 750; // 플레이어 2의 위치 x값
        spr.x = 96; // 플레이어 2의 스프라이트 x값
        spr.y = 32; // 플레이어 2의 스프라이트 y값
        facing = 0; // 왼쪽을 바라보고 있는 상태
        model = 2; // 왼쪽을 바라보는 스프라이트의 인덱스
    }
    pos.y = 440; // 최초의 y좌표
    vel.x = 0; // x의 속도
    vel.y = 0; // y의 속도
    hp = 100; // 체력 초기화
    
}

// 캐릭터의 스프라이트를 불러와서 그려준다
void Character::LoadCharacter(sf::Sprite &player){
    
    player.setTextureRect(sf::IntRect(spr.x, spr.y,32,32));
    player.scale(2.f, 2.f);
    player.setOrigin(16,16);
}

// 스프라이트의 위치를 계산
void Character::CalculateSpritePos(int step){
    spr.x = (model-1)%4*96+32+32*step;
    spr.y = (model-1)/4*128+32+32*facing;
}

// 공격 스프라이트의 위치를 계산
void Character::CalculateSpritePunch(){
    spr.x = (model-1)%4*96+32+32*facing;
    spr.y = (model-1)/4*128;
}

// 방어 스프라이트의 위치를 계산
void Character::CalculateSpriteBlock(){
    spr.x = (model-1)%4*96+32+32*facing;
    spr.y = (model-1)/4*128+96;
}

// 다음 스킨을 계산한다
void Character::NextSkin(){
    model = model%8+1;
    CalculateSpritePos(0);  
}