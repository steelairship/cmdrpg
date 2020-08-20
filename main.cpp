
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "stdlib.h"
#include <time.h>
#include "entity.cpp"
using namespace std;

entity player;
void town(entity &player);

void save(entity &player){
	cout << "enter file name: ";
	string name;
	cin.ignore();
	cin.clear();
	getline(cin, name);
	cout << name;
	if(name.find(' ') != string::npos){
		cout << "file name cannot include spaces";
	}
	ofstream file;
	file.open(name);
	file << "name: " << player.name << endl;
	file << "gold: " << player.money << endl;
	file << "maxHealth: " << player.maxHealth << endl;
	file << "health: " << player.health << endl;
	file << "mana: " << player.mana << endl;
	file << "maxMana: " << player.maxMana << endl;
	file << "exp: " << player.exp << endl;
	file << "damage: " << player.damage << endl;
	file << "offset: " << player.offset << endl;
	file << "luck: " << player.luck << endl;
	file << "weapon: " << player.weapon << endl;
	file.close();
}

void load(entity &player){
	string name;
	string line;
	vector<string> data;
	cout << "enter file name: ";
	cin >> name;
	//getline(cin, name);
	cout << "name: " << name;
	ifstream file;
	file.open(name);
	while(getline(file, line)){
		data.push_back(line);
	}
	player.name = data[0];
	player.money = stoi(data[1]);
	player.maxHealth = stoi(data[2]);
	player.health = stoi(data[3]);
	player.mana = stoi(data[4]);
	player.maxMana = stoi(data[5]);
	player.exp = stoi(data[6]);
	player.damage = stoi(data[7]);
	player.offset = stoi(data[8]);
	player.luck = stoi(data[9]);
	player.weapon = data[10];
	town(player);
	file.close();
}

void attack(entity &player, entity &enemy){
	int attack = 0;
	attack = enemy.attack();
	player.health = player.health - attack;
	cout << "you took " << attack << " damage" << endl;
	attack = player.attack();
	enemy.health = enemy.health - attack;
	cout << enemy.name << " took " << attack << " damage" << endl;

}

void info(entity &palyer){
	cout << "health: " << player.health << endl;
	cout << "mana: " << player.mana << endl;
	cout << "gold: " << player.money << endl;
	cout << "exp: " << player.exp << endl;
	cout << "weapon: " << player.weapon << endl;
}

void endGame(){
	cout << "you have vanquished the mechanical menace and the village of [placeholder] is safe!" << endl;
}

bool final(entity &player){
	string input;
	entity enemy;
	bool win = false;
	int rng = 0;
	int drop = 500;
	enemy.name = "dwarven machine-king";
	enemy.health = 500;
	enemy.exp  = 100;
	enemy.damage = 15;
	enemy.offset = 30;
	cout << "you come face-to-face with the dwarven machine-king!";
	while(win == false){
		cin >> input;
		if(input == "attack"){
			attack(player, enemy);
			if(player.health <= 0){
				cout << "you pass out and then awaken back at the town center" << endl;
				win = true;
				return win;
				town(player);
			}
			if(enemy.health <=0){
				cout << " you won!" << endl;
				cout << enemy.name << "dropped " << drop << " gold" << endl;
				cout << "you gained " << enemy.exp << " exp" << endl;
				endGame();
			}
		}
		if(input == "info"){
			info(player);
		}
		if(input == "heal"){
			player.heal();
		}
		if(input == "run"){
			rng = (rand() % 100);
			if(rng >= 0 && rng < 10){
				win = false;
				cout << "you escape from the " << enemy.name << '!';
				return win;
			}
			if(rng >= 10){
				cout << "you failed to evade the " << enemy.name;
			}
		}
		if(win == true && input != "continue"){
			cout << "type help for help" << endl;
		}
	}
}
bool ruinsEncounter(int count, entity &player){
	entity enemy;
	bool win = false;
	//int attack = 0;
	int rng = 0;
	int erng = 0;
	int drop = 0;
	erng = (rand() % 100);
	if(count == 1){
		enemy.name = "steam warrior";
		enemy.health = 80;
		enemy.exp = (rand() % 7) + 8;
		drop = (rand() % 5) + 4;
		enemy.damage = 14;
		enemy.offset = 8;
	}
	if(erng >= 0 && erng < 60){
		enemy.name = "steam warrior";
		enemy.health = 100;
		enemy.exp = (rand() % 7) + 8;
		drop = (rand() % 5) + 4;
		enemy.damage = 14;
		enemy.offset = 10;
	}
	if(erng >= 60){
		enemy.name = "steam centurion";
		enemy.health = 200;
		enemy.exp = (rand() % 8) + 7;
		drop = (rand() % 6) + 5;
		enemy.damage = 16;
		enemy.offset = 12;
	}
	string input;
	cout << "you encounter a " << enemy.name << '!' << endl;
	while(win == false){
		cin >> input;
		if(input == "attack"){
			attack(player, enemy);
			if(player.health <= 0){
				cout << "you pass out and then awaken back at the town center" << endl;
				win = true;
				return win;
				town(player);
			}
			if(enemy.health <=0){
				cout << " you won!" << endl;
				cout << enemy.name << " dropped" << drop << " gold" << endl;
				cout << "gained " << enemy.exp << " exp" << endl;
				player.exp = player.exp + enemy.exp;
				win = true;
				return win;
			}
		}
		if(input == "info"){
			info(player);
		}
		if(input == "heal"){
			player.heal();
		}
		if(input == "run"){
			rng = (rand() % 100);
			if(rng >= 0 && rng < 75){
				win = false;
				cout << "you escape from the " << enemy.name << '!' << endl;
				return win;
			}
			if(rng >= 75){
				cout << "you failed to evade the " << enemy.name << '!' << endl;
			}
		}
		if(win == true && input != "continue"){
			cout << "type help for help" << endl;
		}
	}
}
void ruins(int count, entity &player){
	string input;
	bool encounter = false;
	cout << "you come across the gate to a dwarven ruin" << endl;
	while(count < 2 && input != "back"){
		cin >> input;
		if(input == "continue"){
			count++;
			encounter = ruinsEncounter(count, player);
			if(encounter == false){
				town(player);
			}
		}
		if(input == "back"){
			town(player);
		}
	}
	while(input != "back"){
		cin >> input;
		if(input == "continue"){
			final(player);
		}
		if(input == "back"){
			town(player);
		}
		cout << "press \"continue\" to push onward into the inner sanctum";
	}
}

void ruins(entity &player){
	int count = 0;
	ruins(count, player);
}

bool caveEncounter(int count, entity &player){
	entity enemy;
	bool win = false;
	int prng = 0;
	int erng = 0;
	int drop = 0;
	int rng = 0;
	erng = (rand() % 100);
	if(count == 1){
		enemy.name = "cave spider";
		enemy.health = 40;
		enemy.exp = (rand() % 5) + 6;
		drop = (rand() % 3) + 3;
		enemy.damage = 10;
		enemy.offset = 6;
	}
	if(count > 1){
		if(erng >= 0 && erng < 60){
			enemy.name = "cave spider";
			enemy.health = 50;
			enemy.exp = rand() % 5 + 6;
			drop = (rand() % 3 + 3);
			enemy.damage = 10;
			enemy.offset = 8;
		}
		if(erng >= 60 && erng < 90){
			enemy.name = "troll";
			enemy.health = 75;
			enemy.exp = (rand() % 6) + 7;
			drop = (rand() % 4) + 3;
			enemy.damage = 12;
			enemy.offset = 10;
		}
		if(erng >= 90){
			enemy.name = "golem";
			enemy.health = 100;
			enemy.exp = (rand() % 7) + 8;
			drop = (rand() % 5) + 4;
			enemy.damage = 14;
			enemy.offset = 10;
		}
	}
	string input;
	cout << "you encounter a " << enemy.name << '!' << endl;
	while(win == false){
		cin >> input;
		if(input == "attack"){
			attack(player, enemy);
			if(player.health <= 0){
				cout << "you pass out and then awaken back at the town center" << endl;
				player.exp = 0;
				player.health = player.maxHealth;
				player.mana = player.maxMana;
				win = false;
				return win;
				town(player);
			}
			if(enemy.health <=0){
				cout << " you won!" << endl;
				cout << enemy.name << "dropped " << drop << " gold" << endl;
				cout << "you gained " << enemy.exp << " exp" << endl;
				player.exp = player.exp + enemy.exp;
				player.money = player.money + drop;
				win = true;
				return win;
			}
		}
		if(input == "info"){
			info(player);
		}

		if(input == "heal"){
			player.heal();
		}
		if(input == "run"){
			rng = (rand() % 100);
			if(rng >= 0 && rng < 60){
				win = false;
				cout << "you escape from the " << enemy.name << '!' << endl;
				town(player);
			}
			if(rng >= 60){
				cout << "you failed to evade the " << enemy.name << '!' << endl;
			}
		}
		if(win == true && input != "continue"){
			cout << "type help for help" << endl;
		}
	}
}

void cave(int count, entity &player){
	string input;
	bool encounter = false;
	cout << "you come across the mouth of a foreboding cave" << endl;
	while(count < 3 && input != "back"){
			cin >> input;
		if(input == "continue"){
			count++;
			encounter = caveEncounter(count, player);
			if(encounter == false){
				town(player);
			}
		}
		if(input == "back"){
			town(player);
		}
	}
	while(input != "back"){
		cout << "you come across the gate of a dwarven ruin" << endl;
		cin >> input;
		if(input == "continue"){
			ruins(player);
		}
		if(input == "back"){
			return;
		}
		if(input == "help"){
			cout << "press \"continue\" to enter the cave << endl << press \"back\" to return to town" << endl;
		}
		cout << "press \"help\" if you are lost" << endl;
	}
}
void cave(entity &player){
	int count = 0;
	cave(count, player);
}

//forest area random encounter
bool forestEncounter(int count, entity &player){
	//cout << player.health << endl;
	entity enemy;
	bool win = false;
	int prng = 0;
	int erng = 0;
	int drop = 0;
	int rng = 0;
	erng = (rand() % 100);
	if(count == 1){
		enemy.health = 5;
		enemy.name = "rat";
		enemy.exp = (rand() % 3) + 1;
		drop = (rand() % 2) + 1;
		//erng = (rand() % 6);
		enemy.damage = 4;
		enemy.offset = 0;
	}
	if(count > 1){
		if(erng >= 0 && erng < 70){
			enemy.health = 10;
			enemy.name = "rat";
			enemy.exp = (rand() % 3) + 1;
			drop = (rand() % 2) + 1;
			enemy.damage = 6;
			enemy.offset = 1;
		}
		if(erng >= 70 && erng < 95){
			enemy.health = 25;
			enemy.name = "wolf";
			enemy.exp = (rand() % 4) + 4;
			drop = (rand() % 3) + 2;
			enemy.damage = 6;
			enemy.offset = 5;
		}
		if(erng >= 95){
			enemy.health = 50;
			enemy.name = "bear";
			enemy.exp = (rand() % 5) + 5;
			drop = (rand() % 3) + 4;
			enemy.damage = 6;
			enemy.offset = 10;


		}
	}
	string input;
	//input = "continue";
	cout << "you encounter a " << enemy.name << '!' << endl;
	while(win == false){
		cin >> input;
		if(input == "attack"){
			attack(player, enemy);
			if(player.health <= 0){
				cout << "you pass out and then awaken back at the town center" << endl;
				player.exp = 0;
				player.health = player.maxHealth;
				player.mana = player.maxMana;
				win = false;
				return win;
			}
			if(enemy.health <=0){
				cout << " you won!" << endl;
				cout << enemy.name << " dropped " << drop << "gold" << endl; //placeholder for gold amount dropped
				cout << "you gained " << enemy.exp << "exp" << endl;
				player.exp = player.exp + enemy.exp;
				player.money = player.money + drop;
				win = true;
				return win;
			}
		}
		if(input == "info"){
			info(player);
		}
		if(input == "heal"){
			player.heal();
		}
		if(input == "run"){
			rng = (rand() % 100);
			if(rng >= 0 && rng < 75){
				win = false;
				cout << "you escape from the " << enemy.name << '!' << endl;
				return win;
			}
			if(rng >= 75){
				cout << "you failed to evade the " << enemy.name << '!' << endl;
			}
		}
		if(win == true && input != "continue"){
			cout << "type help for help" << endl;
		}
	}
}

//forest area
void forest(int count, entity &player){
	string input;
	bool encounter = false;
	while(count < 4 && input != "back"){
		cin >> input;
		if(input == "continue"){
			count++;
			encounter = forestEncounter(count, player);
			if(encounter == false){
				return;
			}

		}
		if(input == "back"){
			return;
		}
	}
		cave(player);
}

void forest(entity &player){
	int count = 0;
	forest(count, player);
}

//town hub
void town(entity &player){
	string input;
	while(input != "quit"){
		cout << "You arrive in the town of Solace" << endl;
		cin >> input;
		if(input == "inn"){
			cout << "Would you like to rest at the inn for 5 gold?" << endl;
			cin >> input;
			if(input == "yes"){
				if(player.money < 5){
					cout <<"you cannot afford to stay at the inn" << endl;
				}else{
					cout << "you rest at the inn" << endl;
					player.money = player.money - 5;
					player.health = player.maxHealth;
					player.mana = player.maxMana;
				}
			}
		}
		if(input == "store" || input == "buy"){
			cout << "you enter the store" << endl;
			//while(input != "back"){
			while(input != "back"){
				getline(cin,input);
				if(input.find("look") != string::npos){
					cout << "iron sword - 10 gold" << endl;
					cout << "steel sword - 20 gold" << endl;
					cout << "dwarven sword - 50 gold" << endl;
					cout << "legendary meteorite sword - 100 gold" << endl;
				}
				if(input.find("iron sword") != string::npos){
					if(player.money < 10){
						cout << "You cannot afford this weapon" << endl;
					}
					if(player.money >= 10){
					player.weapon = "iron sword";
					player.damage = 4;
					player.offset = 1;
					player.money = player.money - 10;
					}
				}

				if(input.find("steel sword") != string::npos){
					if(player.money < 20){
						cout << "You cannot afford this weapon" << endl;
					}
					if(player.money >= 20){
					player.weapon = "steel sword";
					player.damage = 4;
					player.offset = 4;
					player.money = player.money - 20;
					}
				}
				if(input.find("dwarven sword") != string::npos){
					if(player.money < 50){
						cout << "You cannot afford this weapon" << endl;
					}
					if(player.money >= 50){
					player.weapon = "dwarven sword";
					player.damage = 8;
					player.offset = 8;
					player.money = player.money - 50;
					}
				}
				if(input.find("meteorite sword") != string::npos){
					if(player.money < 100){
					cout << "You cannot afford this weapon" << endl;
					}
					if(player.money >= 250){
					player.weapon = "legendary meteorithic sword";
					player.damage = 16;
					player.offset = 20;
					player.money = player.money - 100;
					}
				}else{
				cout << "feel free to \"look\" around" << endl;
				}
				if(input.find("back") != string::npos){
					input = "back";
				}
			}
		}
		if(input == "temple"){
			cout << "you enter the temple and the priest asks which blessing you would like to receive" << endl;
			while(input != "back" && input != "health" && input != "mana"){
				cin >> input;
				if(input == "health"){
					if(player.exp < 10){
						cout << "you do not have enough experience" << endl;
					}
					if(player.exp >= 10){
						cout << "you received the blessing of vitality" << endl;
						player.maxHealth = player.maxHealth + 10;
						player.exp = player.exp - 10;
					}
				}
				if(input == "mana"){
					if(player.exp < 10){
						cout << "you do not have enough experience" << endl;
					}
					if(player.exp >= 10){
						cout << "you receive the blessing of wisdom" << endl;
						player.maxMana = player.maxMana + 10;
						player.exp = player.exp - 10;
					}
				}
				if(input != "health" && input != "mana"){
					cout << "the priest can give blessings that grand a boon to \"health\" or \"mana\" in exchange for experience points" << endl;
				}
			}
		}
		if(input == "leave" || input == "road" || input == "depart"){
			cout << "you leave the town and travel on the road through the forest" << endl;
			forest(player);
		}
		if(input == "info" || input == "stats" || input == "stat"){
			info(player);
		}
		if(input == "help"){
			cout << "store - enter the town general store" << endl;
			cout << "temple - enter the temple and receive a blessing" << endl;
			cout << "inn - rest at the inn to replenish your health and mana" << endl;
			cout << "leave - leave town on the road going into the forest" << endl;
			cout << "info - receive a summary of your stats" << endl;
		}
		if(input == "save"){
			cout << "are you sure you want to save the game?" << endl;
			cin >> input;
			if(input == "yes"){
				save(player);
			}
		}
		if(input == "quit" || input == "exit"){
			cout << "exited the game";
			return;
		}
	}
}
int main(){
	srand(time(NULL));
	string input;
	string dummy;
	/*while(input.find("quit") == string::npos && input.find("exit") == string::npos){
		cout << "COMMAND RPG" << endl << endl;
		cout << "new game" << endl;
		cout << "load game" << endl;
		cout << "quit" << endl << endl;
	    getline(cin, input);
	    if(input.find("new") != string::npos) {
	    	player.money = 10;
	    	player.health = 25;
	    	player.maxHealth = 25;
	    	player.mana = 10;
	    	player.maxMana = 10;
	    	player.exp = 0;
	    	player.weapon = "rusty iron sword";
	    	player.damage = 2;
	    	player.offset = 1;
	        town(player);
	    }
	    if(input.find("load") != string::npos){
	        load(player);
	    }
	}*/
	player.money = 10;
	player.health = 25;
	player.maxHealth = 25;
	player.mana = 10;
	player.maxMana = 10;
	player.exp = 0;
	player.weapon = "rusty iron sword";
	player.damage = 2;
	player.offset = 1;
	town(player);
	cout << "exited the game" << endl;

	return 0;
}
