#include <SFML/Graphics.hpp>
#include <vector>
#include "character.hpp"

// ������ -> �ʱ�ȭ ���
Character::Character(int player){
    
	// �÷��̾� 1�� �ʱ� �ε��� ��
    if (player == 1) {
        pos.x = 50; // �÷��̾� 1�� ��ġ x��
        spr.x = 96; // �÷��̾� 1�� ��������Ʈ x��
        spr.y = 32; // �÷��̾� 1�� ��������Ʈ y��
        facing = 1; // �������� �ٶ󺸰� �ִ� ����
        model = 1; // �������� �ٶ󺸴� ��������Ʈ�� �ε���
    }
	// �÷��̾� 2�� �ʱ� �ε��� ��
    else {
        pos.x = 750; // �÷��̾� 2�� ��ġ x��
        spr.x = 96; // �÷��̾� 2�� ��������Ʈ x��
        spr.y = 32; // �÷��̾� 2�� ��������Ʈ y��
        facing = 0; // ������ �ٶ󺸰� �ִ� ����
        model = 2; // ������ �ٶ󺸴� ��������Ʈ�� �ε���
    }
    pos.y = 440; // ������ y��ǥ
    vel.x = 0; // x�� �ӵ�
    vel.y = 0; // y�� �ӵ�
    hp = 100; // ü�� �ʱ�ȭ
    
}

// ĳ������ ��������Ʈ�� �ҷ��ͼ� �׷��ش�
void Character::LoadCharacter(sf::Sprite &player){
    
    player.setTextureRect(sf::IntRect(spr.x, spr.y,32,32));
    player.scale(2.f, 2.f);
    player.setOrigin(16,16);
}

// ��������Ʈ�� ��ġ�� ���
void Character::CalculateSpritePos(int step){
    spr.x = (model-1)%4*96+32+32*step;
    spr.y = (model-1)/4*128+32+32*facing;
}

// ���� ��������Ʈ�� ��ġ�� ���
void Character::CalculateSpritePunch(){
    spr.x = (model-1)%4*96+32+32*facing;
    spr.y = (model-1)/4*128;
}

// ��� ��������Ʈ�� ��ġ�� ���
void Character::CalculateSpriteBlock(){
    spr.x = (model-1)%4*96+32+32*facing;
    spr.y = (model-1)/4*128+96;
}

// ���� ��Ų�� ����Ѵ�
void Character::NextSkin(){
    model = model%8+1;
    CalculateSpritePos(0);  
}