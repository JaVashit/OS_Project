#ifndef CHARAC_H
#define CHARAC_H

class Character
{

public:
    Character(int);
    void LoadCharacter(sf::Sprite&);
    void CalculateSpritePos(int);
    void CalculateSpritePunch();
    void CalculateSpriteBlock();
    void NextSkin();
    
    sf::Vector2f pos;   //Position
    sf::Vector2f vel;   //Speed
    sf::Vector2f spr;   //Sprite position in .png
    float hp;           //Player hp
    bool facing;        //0 left, 1 right
private:
    int model;
};

#endif