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
	setColor();
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


void Champion::displayCard(int i) const{
  //Affiche les "cards" du champion lors de la pioche.




  // Effacement du frame buffer
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //Affichage des bordures de la carte:
  glColor3f(1.0f,1.0f,1.0f);
  glBegin(GL_QUADS);

  glEnd();

  glutSwapBuffers();
}

void Champion::evolve(){
  //Fait evoluer le champion au niveau supérieur et modifie ses stats

}

void Champion::dragndrop(int _x, int _y){
  //Gère le piquer/déplacer du champion suite à l'action de l'utilisateur
	i = abs(_x / (Param::dimCase + 2 * Param::borderSpacingCase));
	j = abs(_y / (Param::dimCase + 2 * Param::borderSpacingCase));
}

int Champion::buy(){

  return -cost;
}

int Champion::sell(){

  return cost*level;
}


void Champion::display() const{
	if (alive) {
		glMatrixMode(GL_MODELVIEW);

		glPushMatrix();

		glLoadIdentity();

		glColor4f(color[0], color[1], color[2], color[3]);

		
		glTranslatef(i*(2 * Param::borderSpacingCase + Param::dimCase) + Param::borderSpacingCase + Param::dimCase / 2, 5.0f, j*(2 * Param::borderSpacingCase + Param::dimCase) + Param::borderSpacingCase + Param::dimCase / 2);
		float rayon = (float)health/(float)maxHealth*4+1;


		
		glutSolidSphere(rayon, 20, 20);

		glPopMatrix();
	}
}

void Champion::move(int _x, int _y){

}

void Champion::move(Character *target){
	//Calcul du chemin le plus rapide
	list<NodeGraph*> path = Game::currentInstance->getBoard()->getShorterPath(i,j,target);
	if (path.empty()) {
		
	}
	else {
		NodeGraph * nextNode = *path.begin();
		i = nextNode->getI();
		j = nextNode->getJ();
	}
}

int Champion::die(){
	this -> alive = false;
	return 0;
}
