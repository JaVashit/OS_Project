#include <SFML/Graphics.hpp>
#include <vector>
#include "character.hpp"


Character::Character(int player){
    
    if (player == 1) {
        pos.x = 50;
        spr.x = 96;
        spr.y = 32;
        facing = 1;
        model = 1;
    }
    else {
        pos.x = 750;
        spr.x = 96;
        spr.y = 32;
        facing = 0;
        model = 2;
    }
    pos.y = 440;
    vel.x = 0;
    vel.y = 0;
    hp = 100;
    
}

void Character::LoadCharacter(sf::Sprite &player){
    
    player.setTextureRect(sf::IntRect(spr.x, spr.y,32,32));
    player.scale(2.f, 2.f);
    player.setOrigin(16,16);
}

void Character::CalculateSpritePos(int step){
    spr.x = (model-1)%4*96+32+32*step;
    spr.y = (model-1)/4*128+32+32*facing;
}

void Character::CalculateSpritePunch(){
    spr.x = (model-1)%4*96+32+32*facing;
    spr.y = (model-1)/4*128;
}

void Character::CalculateSpriteBlock(){
    spr.x = (model-1)%4*96+32+32*facing;
    spr.y = (model-1)/4*128+96;
}

void Character::NextSkin(){
    model = model%8+1;
    CalculateSpritePos(0);  
}