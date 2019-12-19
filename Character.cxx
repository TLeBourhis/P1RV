#include "Character.h"
#include "Param.h"
#include <cmath>
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include "Game.h"

using namespace std;

int Character::staticID = 0;

Character::Character(std::string _name, int _armor, int _magicResistance, float _spellPower, int _attackRange, float _attackSpeed, int _health, int _attackDamage, int _i, int _j, int _caseID) {
	staticID++;
	id = staticID;

	name = _name;
	initialArmor = _armor;
	armor = _armor;
	initialMagicResistance = _magicResistance;
	magicResistance = _magicResistance;
	initialSpellPower = _spellPower;
	spellPower = _spellPower;
	initialAttackRange = _attackRange;
	attackRange = _attackRange;
	initialAttackSpeed = _attackSpeed;
	attackSpeed = _attackSpeed;
	alive = true;
	health = _health;
	maxHealth = _health;
	initialHealth = _health;
	initialAttackDamage = _attackDamage;
	attackDamage = _attackDamage;
	i = _i;
	j = _j;
	x = i * (Param::dimCase + 2 * Param::borderSpacingCase) + Param::borderSpacingCase + Param::dimCase / 2; //i correspond au numéro de colonne
	y = j * (Param::dimCase + 2 * Param::borderSpacingCase) + Param::borderSpacingCase + Param::dimCase / 2; //j correspond au numéro de ligne
	setColor();
}

void Character::reset(int _i, int _j) {
	alive = true;
	health = initialHealth;
	maxHealth = initialHealth;
	setIJ(_i, _j);
	armor = initialArmor;
	magicResistance = initialMagicResistance;
	spellPower = initialSpellPower;
	attackRange = initialAttackRange;
	attackSpeed = initialAttackSpeed;
	attackDamage = initialAttackDamage;
}

float Character::getColor(int i) const {
	return color[i];
};

void Character::getHit(int damage, string type) {
	if (this->isAlive()) {
		if (type == "ATTACK_DAMAGE") {
			int dmg = max(damage - armor, 5);
			health -= dmg;
			if (health <= 0) {
				Game::currentInstance->addGold(this->die());
			}
		}
		else {
			int dmg = max(damage - magicResistance, 5);
			health -= dmg;
			if (health <= 0) {
				Game::currentInstance->addGold(this->die());
			}
		}
	}
}

float Character::distance(Character * c) const {
	int _xc = c->i * (Param::dimCase + 2 * Param::borderSpacingCase) + Param::borderSpacingCase + Param::dimCase / 2;
	int _yc = c->j * (Param::dimCase + 2 * Param::borderSpacingCase) + Param::borderSpacingCase + Param::dimCase / 2;
	int _xme = this->i * (Param::dimCase + 2 * Param::borderSpacingCase) + Param::borderSpacingCase + Param::dimCase / 2;
	int _yme = this->j * (Param::dimCase + 2 * Param::borderSpacingCase) + Param::borderSpacingCase + Param::dimCase / 2;
	return sqrt(pow(_xc - _xme, 2) + pow(_yc - _yme, 2));
}

void Character::moveTo(int _x, int _y) {
	this->x = _x;
 	this->y = _y;
}

void Character::setColor() {
	color[0] = Param::colors[name].at(0);
	color[1] = Param::colors[name].at(1);
	color[2] = Param::colors[name].at(2);
	color[3] = Param::colors[name].at(3);
}

void Character::setIJ(int _i, int _j) {
	i = _i;
	j = _j;
	x = i * (Param::dimCase + 2 * Param::borderSpacingCase) + Param::borderSpacingCase + Param::dimCase / 2;
	y = j * (Param::dimCase + 2 * Param::borderSpacingCase) + Param::borderSpacingCase + Param::dimCase / 2;
}
