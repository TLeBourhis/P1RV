#include "Race.h"

#include "Champion.h";
#include <iostream>

using namespace std;

Race::Race(string _name, int _bT1, int _bT2, string _b1, string _b2){
   name = _name;

   bonusTreshold[0] = _bT1;
   bonusTreshold[1] = _bT2;
   bonus[0] = _b1;
   bonus[1] = _b2;
}

void Race::addBonus(list<Champion*> champions) const{
	list<Champion*> champs = this->getChampionsFromRace(champions);
	int n = champs.size();
	if (n >= bonusTreshold[0]) {
		if (n >= bonusTreshold[1]) {
			//On applique le bonus[1]
			for (auto it = champs.begin(); it != champs.end(); it++) {
				addBonusTo(*it, 1);
			}
		}
		else {
			//On applique le bonus[0]
			for (auto it = champs.begin(); it != champs.end(); it++) {
				addBonusTo(*it, 0);
			}
		}
	}
}

void Race::addBonusTo(Champion * c, int i) const{
	string add = bonus[i].substr(0, bonus[i].find(" "));
	string caracteristic = bonus[i].substr(bonus[i].find(" ")+1, bonus[i].size());
	cout << add << "|" << caracteristic << endl;

	//Détermination du caracteristic
	if (caracteristic == "armor") {
		c->addArmor(std::stoi(add));
	}
	if (caracteristic == "magicResistance") {
		c->addMagicResistance(std::stoi(add));
	}
	if (caracteristic == "spellPower") {
		c->addSpellPower(std::stof(add));
	}
	if (caracteristic == "attackRange") {
		c->addAttackRange(std::stoi(add));
	}
	if (caracteristic == "health") {
		c->addHealth(std::stoi(add));
	}
	if (caracteristic == "attackSpeed") {
		c->addAttackSpeed(std::stof(add));
	}
	if (caracteristic == "attackDamage") {
		c->addAttackDamage(std::stoi(add));
	}
}

list<Champion*> Race::getChampionsFromRace(list<Champion*> champions) const{
	list<Champion*> champs;
	for (auto it = champions.begin(); it != champions.end(); it++) {
		if ((*it)->getRace(0) == this || (*it)->getRace(1) == this) {
			champs.push_back(*it);
		}
	}
	return champs;
}


void Race::display() const{

}

bool Race::operator==(Race const& r) {
	return name == r.name;
}