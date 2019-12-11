#include "Character.h"
#include "Param.h"
#include <cmath>
#include <string>
#include <iostream>
#include "Game.h"

using namespace std;

int Character::staticID = 0;

Character::Character(std::string _name, int _armor, int _magicResistance, float _spellPower, int _attackRange, float _attackSpeed, int _health, int _attackDamage, int _i, int _j, int _caseID) {
	staticID++;
	id = staticID;

	name = _name;
	armor = _armor;
	magicResistance = _magicResistance;
	spellPower = _spellPower;
	attackRange = _attackRange;
	attackSpeed = _attackSpeed;
	alive = true;
	health = _health;
	maxHealth = _health;
	attackDamage = _attackDamage;
	i = _i;
	j = _j;
	caseID = _caseID;
	color[0] = 0.0f;
	color[1] = 0.0f;
	color[2] = 0.0f;
	color[3] = 1.0f;
}

void Character::reset(int _i, int _j) {
	alive = true;
	health = maxHealth;
	i = _i;
	j = _j;
}


void Character::getHit(int damage, string type) {
	cout << "attack" << endl;
	if (type == "ATTACK_DAMAGE") {
		health -= (damage - armor);
		if (health <= 0) {
			Game::currentInstance->addGold(this->die());
		}
	}
	else {
		health -= (damage - magicResistance);
		if (health <= 0) {
			Game::currentInstance->addGold(this->die());
		}
	}

	cout << health << endl;
}

float Character::distance(Character * c) const {
	int _xc = c->i * (Param::dimCase + 2 * Param::borderSpacingCase) + Param::borderSpacingCase + Param::dimCase / 2;
	int _yc = c->j * (Param::dimCase + 2 * Param::borderSpacingCase) + Param::borderSpacingCase + Param::dimCase / 2;
	int _xme = this->i * (Param::dimCase + 2 * Param::borderSpacingCase) + Param::borderSpacingCase + Param::dimCase / 2;
	int _yme = this->j * (Param::dimCase + 2 * Param::borderSpacingCase) + Param::borderSpacingCase + Param::dimCase / 2;
	return sqrt(pow(_xc - _xme, 2) + pow(_yc - _yme, 2));
}

void Character::moveTo(int _x, int _y) {
	this->i = (int)(_x / (Param::dimCase + 2 * Param::borderSpacingCase));
	this->j = (int)(_y / (Param::dimCase + 2 * Param::borderSpacingCase));
}
