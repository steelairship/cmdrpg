#include <string>
#include <iostream>
using namespace std;
struct entity{
	string name;
	int money;
	int maxHealth;
	int health;
	int mana;
	int maxMana;
	int exp;
	int damage;
	int offset;
	int luck;
	string weapon;
	void heal(){
		if(mana < 5){
			cout << "your mana is too low" << endl;
		}
		if(mana >= 5){
			cout << "you replenish health!" << endl;
		health = maxHealth;
		mana = mana - 5;
		}
	}
	int attack(){
		srand(time(NULL));
		return (rand() % damage) + offset;
	}

};

/*void initPlayer(){
player diugh;
diugh.money = 10;
diugh.health = 100;
diugh.mana = 100;
}*/

