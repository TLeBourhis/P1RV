#include "Race.h"

#include "Champion.h"
#include "Game.h"
#include <iostream>

using namespace std;

Race::Race(string _name, int _bT1, int _bT2, string _b1, string _b2) {
	name = _name;

	bonusTreshold[0] = _bT1;
	bonusTreshold[1] = _bT2;
	bonus[0] = _b1;
	bonus[1] = _b2;
}

void Race::addBonus(list<Champion*> champions) const {
	//Gère les bonus à prendre en compte, avec les différents seuils
	list<Champion*> champs = this->getChampionsFromRace(champions);
	int n = count(champs);
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

int Race::count(list<Champion*> champions) const {
	int count = 0;
	list<string> champNames;
	for (auto it = champions.begin(); it != champions.end(); it++) {
		if (champNames.empty()) {
			count++;
			champNames.push_back((*it)->getName());
		}
		else {
			if (find(champNames.begin(), champNames.end(), (*it)->getName()) == champNames.end()) {
				count++;
				champNames.push_back((*it)->getName());
			}
		}
	}
	return count;
}

void Race::addBonusTo(Champion * c, int i) const {
	//Ajoute les bonnus de races aux champions concernés
	string add = bonus[i].substr(0, bonus[i].find(" "));
	string caracteristic = bonus[i].substr(bonus[i].find(" ") + 1, bonus[i].size());


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

list<Champion*> Race::getChampionsFromRace(list<Champion*> champions) const {
	//Retourne la liste des champions d'une même race
	list<Champion*> champs;
	for (auto it = champions.begin(); it != champions.end(); it++) {
		if ((*it)->getRace(0) == this || (*it)->getRace(1) == this) {
			champs.push_back(*it);
		}
	}
	return champs;
}


void Race::display() const {

}

bool Race::operator==(Race const& r) {
	return name == r.name;
}
