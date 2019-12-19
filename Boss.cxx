#include "Boss.h"
#include <string>
#include <list>
#include "Game.h"
#include <iterator>
#include <chrono>
#include <thread>

using namespace std;

Boss::Boss(string _name, int _armor, int _magicResistance, float _spellPower, int _attackRange, float _attackSpeed, int _health, int _attackDamage, int _i, int _j, int _caseID, int _gold, int _rage, int _mana) : Monster(_name, _armor, _magicResistance, _spellPower, _attackRange, _attackSpeed, _health, _attackDamage, _i, _j, _caseID, _gold, _rage) {
	mana = _mana;
};

void Boss::fight(list<Character*> allies, list<Character*> ennemies){
	//Gère les actions du champion lors du combat.

	this_thread::sleep_for(chrono::milliseconds(Param::sleepTime));

	if (ennemies.empty()) {
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
			if (rage >= Param::maxRage) {
				rage = 0;
				this->boostedAttack(nearestEnnemy);
			}
			else {
				nearestEnnemy->getHit(attackDamage, "ATTACK_DAMAGE");
				rage += Param::rageByHitForBoss;
			}

			if (mana == Param::maxMana) {
				mana = 0;
				this->spell1(ennemies);
			}
			else {
				mana += Param::manaByHit;
			}
		}
	}
}


void Boss::spell1(list<Character*> ennemies){
  //Inflige des dégâts à tous les ennemis qui sont suffisamment proches du boss

  int spellRange = 2; //ATTENTION : Mettre ce paramètre dans Param
  int spellDamage = 200; //ATTENTION : Mettre ce paramètre dans Param

  for (int n = -spellRange; n <= spellRange; n++) {
	  for (int m = -spellRange; m <= spellRange; m++) {
		  if (i + n < Param::nbRows && i + n >= 0 && j + m < Param::nbColumns && j + m >= 0) {
			  Game::currentInstance->getBoard()->setColorCase(i + n, j + m, 1, 0, 0);
		  }
	  }
  }
  this_thread::sleep_for(chrono::milliseconds(1000));

  for (int n = -spellRange; n <= spellRange; n++) {
	  for (int m = -spellRange; m <= spellRange; m++) {
		  for (auto it = ennemies.begin(); it != ennemies.end(); it++) {
			  if ((*it)->getI() == i + n && (*it)->getJ() == j + m) {
				  //L'ennemi est sur l'une des cases
				  (*it)->getHit(spellDamage, "MAGIC_DAMAGE");
			  }
		  }
	  }
  }

  for (int n = -spellRange; n <= spellRange; n++) {
	  for (int m = -spellRange; m <= spellRange; m++) {
		  if (i + n < Param::nbRows && i + n >= 0 && j + m < Param::nbColumns && j + m >= 0) {
			  Game::currentInstance->getBoard()->setColorCase(i + n, j + m, Param::caseColor[0], Param::caseColor[1], Param::caseColor[2]);
		  }
	  }
  }
}

void Boss::display() const {
	if (alive) {
		glMatrixMode(GL_MODELVIEW);

		glPushMatrix();

		glLoadIdentity();

		glColor4f(color[0], color[1], color[2], color[3]);


		float rayon = (float)health / (float)maxHealth * 4 + 1;
		glTranslatef(i*(2 * Param::borderSpacingCase + Param::dimCase) + Param::borderSpacingCase + Param::dimCase / 2, 3 * rayon, j*(2 * Param::borderSpacingCase + Param::dimCase) + Param::borderSpacingCase + Param::dimCase / 2);

		glutSolidTeapot(3 * rayon);

		glPopMatrix();
	}
}
