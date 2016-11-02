#include "Champion.h"

template <typename T>
Champion<T>::Champion(int player, int m_number){
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

	attack = false;
	barrier = false;
}

template <typename T>
sf::Vector2<T> Champion<T>::getPosition(){
	return this->pos;
}

template <typename T>
void Champion<T>::setPosition(float _x, float _y){
	pos.x = _x;
	pos.y = _y;
}

template <typename T>
int Champion<T>::getHp(){
	return this->hp;
}

template <typename T>
void Champion<T>::setHp(int _hp){
	this->hp = _hp;
}

template <typename T>
int Champion<T>::getMp(){
	return this->mp;
}

template <typename T>
void Champion<T>::setMp(int _mp){
	this->mp = _mp;
}

template <typename T>
bool Champion<T>::isAttacking(){
	return attack;
}

template <typename T>
bool Champion<T>::isBarrier(){
	return barrier;
}

template <typename T>
void Champion<T>::setAttack(bool a){
	attack = a;
}

template <typename T>
void Champion<T>::setBarrier(bool b){
	barrier = b;
}

template <typename T>
void Champion<T>::drawChampion(){
	//draw champion
}

template <typename T>
bool Champion<T>::isDeath(){
	if(hp<=0) return true;
	else return false;
}