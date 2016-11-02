#include <SFML/Graphics.hpp>
#include <vector>


template <typename T>
class Champion{
private:
	sf::Vector2 <T> pos;
	bool facing;
	int player;

	int hp;
	int mp;

	bool attack;
	bool barrier;

	int modelNumber;

public:
	Champion(int p, int m_number);
	~Champion();

	void setHp(int);
	int getHp();

	void setMp(int);
	int getMp();

	void setPosition(float, float);
	sf::Vector2<T> getPosition();
	
	void setAttack(bool);
	void setBarrier(bool);
	bool isAttacking();
	bool isBarrier();
	bool isDeath();

	void drawChampion();

};