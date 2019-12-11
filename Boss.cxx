#include "Boss.h"
#include <string>

using namespace std;

Boss::Boss(string _name, int _armor, int _magicResistance, float _spellPower, int _attackRange, float _attackSpeed, int _health, int _attackDamage, int _x, int _y, int _caseID, int _gold, int _rage, int _mana) : Monster(_name,_armor, _magicResistance, _spellPower, _attackRange, _attackSpeed, _health, _attackDamage, _x, _y, _caseID, _gold, _rage), mana(_mana){};


void Boss::fight(list<Character*> allies, list<Character*> ennemies){
	//Gère les actions du champion lors du combat.


	if (size(ennemies) == 0) {
		//Si pas d'ennemi


	}
	else {
		//Récupération de l'ennemi le plus proche
		float distMin = this->distance(*ennemies.begin());
		Character * nearestEnnemy = *ennemies.begin();
		for (list<Character*>::iterator it = ennemies.begin(); it != ennemies.end(); ++it) {
			float d = this->distance(*it);
			if (d < distMin) {
				distMin = d;
				nearestEnnemy = *it;
			}
		}




		if (distMin > attackRange) {
			//L'ennemi est en-dehors de la range d'attaque
			//Déplacement vers l'ennemi le plus proche
			this->move(nearestEnnemy);
		}
		else {
			//Attaque de l'ennemi
			if (rage >= Param::maxRage) { //ATTENTION : Mettre ce paramètre dans Param
				rage = 0;
				this->boostedAttack(nearestEnnemy);
			}
			else {
				nearestEnnemy->getHit(attackDamage, "ATTACK_DAMAGE");
				rage += Param::rageByHitForBoss; //ATTENTION : Mettre ce paramètre d'augmentation de rage dans Param
			}

			if (mana == Param::maxMana) { //ATTENTION : Mettre ce paramètre dans Param
				mana = 0;
				this->spell1(ennemies);
			}
			else {
				mana += Param::manaByHit; //ATTENTION : Mettre ce paramètre dans Param
			}
		}
	}
}


void Boss::spell1(list<Character*> ennemies){
  //Inflige des dégâts à tous les ennemis qui sont suffisamment proches du boss

  int spellRange = 100; //ATTENTION : Mettre ce paramètre dans Param
  int spellDamage = 100; //ATTENTION : Mettre ce paramètre dans Param

  for(list<Character*>::iterator it = ennemies.begin(); it != ennemies.end(); ++it){
    if(this->distance(*it) < spellRange){
      (*it)->getHit(spellDamage,"MAGIC_DAMAGE");
    }
  }
}
