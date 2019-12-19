#include "Champion.h"
#include <string>
#include <list>
#include "Param.h"
#include "Race.h"
#include "Character.h"
#include <GL\glew.h>
#include <GL\freeglut.h>
#include "Game.h"
#include "NodeGraph.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

Champion::Champion(string _name, int _armor, int _magicResistance, float _spellPower, int _attackRange, float _attackSpeed, int _health, int _attackDamage, int _i, int _j, int _caseID, int _level, int _cost, Race * _race1, Race * _race2) : Character(_name, _armor, _magicResistance, _spellPower, _attackRange, _attackSpeed, _health, _attackDamage, _i, _j, _caseID){
  level = _level;
  races[0] = _race1;
  races[1] = _race2;
  cost = _cost;
  setColor();
}

Champion::Champion(Champion * c) : Character(c->name,c->armor,c->magicResistance,c->spellPower,c->attackRange,c->attackSpeed,c->health,c->attackDamage,c->i,c->j,c->caseID){
	level = c->level;
	cost = c->cost;
	races[0] = c->races[0];
	races[1] = c->races[1];
	
}

Champion::~Champion(){
  delete races[0];
  delete races[1];
  delete this;
}

Race * Champion::getRace(int i) {
	return races[i];
}



void Champion::fight(list<Character*> allies, list<Character*> ennemies){
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
			nearestEnnemy->getHit(attackDamage, "ATTACK_DAMAGE");
		}
	}
	
}


void Champion::evolve(){
  //Fait evoluer le champion au niveau supérieur et modifie ses stats
	level++;
	this->reset(i, j);
}

void Champion::reset(int _i, int _j) {
	//Reinitialise le champion (stats et position)
	alive = true;
	health = initialHealth + Param::healthBonusByLevel * (level - 1);
	maxHealth = health;
	setIJ(_i, _j);
	armor = initialArmor + Param::armorBonusByLevel * (level - 1);
	magicResistance = initialMagicResistance + Param::magicResistanceBonusByLevel * (level - 1);
	spellPower = initialSpellPower + Param::spellPowerBonusByLevel * (level - 1);
	attackRange = initialAttackRange + Param::attackRangeBonusByLevel * (level - 1);
	attackSpeed = initialAttackSpeed + Param::attackSpeedBonusByLevel * (level - 1);
	attackDamage = initialAttackDamage + Param::attackDamageBonusByLevel * (level - 1);
}

int Champion::buy(){
	//gère le cout du champion pendant l'achat
  return -cost;
}

int Champion::sell(){
	
  return cost*level;
}


void Champion::display() const{
	//Affichage du champion
	//Gere aussi l'affichage selon le niveau
	if (alive) {
		glMatrixMode(GL_MODELVIEW);

		glPushMatrix();

		glLoadIdentity();

		glColor4f(color[0], color[1], color[2], color[3]);

		float rayon = (float)health / (float)maxHealth * 4 + 1;
		float rlevel = rayon / 2;
		
		glTranslatef(x, rayon, y);
		glutSolidSphere(rayon, 20, 20);
		glBegin(GL_TRIANGLES);
			 glVertex3f(0.8*rayon, 0.7*rayon, 0);
			 glVertex3f(0.5*rayon, -0.2*rayon, 0);
			 glVertex3f(1.5*rayon, -0.2*rayon, 0.5*rayon); //point "main"
			glEnd();
			glBegin(GL_TRIANGLES);
			 glVertex3f(0.8*rayon, 0.7*rayon, 0);
			 glVertex3f(0.5*rayon, 0.7*rayon, 0.5*rayon);
			 glVertex3f(1.5*rayon, -0.2*rayon, 0.5*rayon);//point "main"
			glEnd();
			glBegin(GL_TRIANGLES);
			 glVertex3f(-0.8*rayon, 0.7*rayon, 0);
			 glVertex3f(-0.5*rayon, -0.2*rayon, 0);
			 glVertex3f(-1.5*rayon, -0.2*rayon, 0.5*rayon);//point "main"
			glEnd();
			glBegin(GL_TRIANGLES);
			 glVertex3f(-0.8*rayon, 0.7*rayon, 0);
			 glVertex3f(-0.5*rayon, 0.7*rayon, 0.5*rayon);
			 glVertex3f(-1.5*rayon, -0.2*rayon, 0.5*rayon);//point "main"
			glEnd();

		if (level == 4) {
			glTranslatef(-rlevel - 0.5, 0.8*rayon + rlevel, -rlevel - 0.5);
			glutSolidSphere(rlevel, 20, 20);
			glTranslatef(2 * rlevel + 1, 0, 0);
			glutSolidSphere(rlevel, 20, 20);
			glTranslatef(0, 0, 2 * rlevel + 1);
			glutSolidSphere(rlevel, 20, 20);
			glTranslatef(-2 * rlevel - 1, 0, 0);
			glutSolidSphere(rlevel, 20, 20);
		}

		if (level == 3) {
			glTranslatef(-rlevel - 0.5, 0.8*rayon + rlevel, -rlevel - 0.5);
			glutSolidSphere(rlevel, 20, 20);
			glTranslatef(2 * rlevel + 1, 0, 0);
			glutSolidSphere(rlevel, 20, 20);
			glTranslatef(-rlevel - 1, 0, 2 * rlevel + 1);
			glutSolidSphere(rlevel, 20, 20);
		}
		
		if (level == 2) {
			glTranslatef(- rlevel - 0.5, 0.8*rayon + rlevel, 0);
			glutSolidSphere(rlevel, 20, 20);
			glTranslatef(2 * rlevel + 1, 0, 0);
			glutSolidSphere(rlevel, 20, 20);
		}

		if (level == 1) {
			glTranslatef(0, 1.5*rayon, 0);
			glutSolidSphere(rayon/2, 20, 20);
		}

		glPopMatrix();
	}
}

void Champion::move(Character *target){
	//Calcul du chemin le plus rapide
	list<NodeGraph*> path = Game::currentInstance->getBoard()->getShorterPath(i,j,target);
	if (path.empty()) {
		
	}
	else {
		NodeGraph * nextNode = *path.begin();
		if (Game::currentInstance->getBoard()->findCharacter(nextNode->getI(), nextNode->getJ()) == nullptr) {
			setIJ(nextNode->getI(), nextNode->getJ());
		}
	}
}

int Champion::die(){
	//Met l'état du champion à "mort"
	this -> alive = false;
	return 0;
}
