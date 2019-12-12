#include "Board.h"
#include "Param.h"
#include "Champion.h"
#include "Monster.h"
#include "Graph.h"
#include <list>
#include <iterator>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <thread>
#include <chrono>
#include <iostream>
#include "Race.h"
#include <algorithm>

using namespace std;


Board::Board() {};

list<Race*> Board::getRaces() {
	list<Race*> races;
	for (auto it = champions.begin(); it != champions.end(); it++) {
		Champion * c = *it;
		for (int i = 0; i <= 1; i++) {
			if (find(races.begin(), races.end(), c->getRace(i)) == races.end()) {
				//La race n'est pas déjà présente dans races
				races.push_back(c->getRace(i));
			}
		}
	}

	return races;
}

int Board::count(Race * race) {
	int count = 0;
	for (auto it = champions.begin(); it != champions.end(); it++) {
		if ((*it)->getRace(0) == race || (*it)->getRace(1) == race) {
			count++;
		}
	}
	return count;
}

void Board::clearMonsters() {
	//On efface l'ancienne liste de monstres
	monsters.clear();
}

void Board::reinitChampions() {
	int i = 0;
	int j = 0;
	for (auto it = champions.begin(); it != champions.end(); it++) {
		if (i == 10) {
			i = 0;
			j++;
		}
		(*it)->reset(i, j);
		i++;
	}

	
}

void Board::applyRaceBonus() {
	//Application des bonus de race
	list<Race*> races = getRaces();
	for (auto it = races.begin(); it != races.end(); it++) {
		(*it)->addBonus(champions);
	}
}

void Board::setMonsters(int round) {
	//Ajoute les monstres pour ce round sur le board
	vector<Monster*> vecMonsters = Param::monstersByRounds.at(round-1);
	for (int i = 0; i < vecMonsters.size(); i++) {
		monsters.push_back(vecMonsters.at(i));
	}
}

void Board::removeChampion(int indice) {
	//ATTENTION : ça peut delete l'objet sur lequel pointe le pointeur
	//champions.erase(indice);
}

void Board::addChampion(Champion * champion) {
	//ATTENTION on ne peut pas avoir 2 PE indépendants pour l'instant
	Champion * newChampion = new Champion(champion);
	int i = newChampion->getI();
	int j = newChampion->getJ();
	while (findChampion(i, j) != nullptr) {
		if (i == 10) {
			i = 0;
			j++;
		}
		i++;
	}
	newChampion->setIJ(i, j);
	champions.push_back(newChampion);
}

Champion* Board::findChampion(int _i, int _j) {
	//Retourne le pointer vers le champion présent sur la case i,j
	Champion* champ = nullptr;
	for (list<Champion*>::iterator itr = champions.begin(); itr != champions.end(); itr++) {
		if ((*itr)->getI() == _i && (*itr)->getJ() == _j) {
			champ = (*itr);
		}
	}
	return champ;
}

bool Board::fight(){
	//Gère le fight sur le board lors d'un round
	bool win = false;

	
	list<Character*> fightingChampions;
	for (auto it = champions.begin(); it != champions.end(); it++) {
		fightingChampions.push_back((Character*)(*it));
		
	}
	list<Character*> fightingMonsters;
	for (auto it = monsters.begin(); it != monsters.end(); it++) {
		fightingMonsters.push_back((Character*)(*it));
	}
	while (fightingChampions.empty() == false && fightingMonsters.empty() == false) {
		//Tant que l'un des camps n'est pas décédé on les fait se combattre

		for (auto it = fightingChampions.begin(); it != fightingChampions.end(); it++) {
			(*it)->fight(fightingChampions, fightingMonsters);
		}

		for (auto it = fightingMonsters.begin(); it != fightingMonsters.end(); it++) {
			(*it)->fight(fightingMonsters, fightingChampions);
		}

		//On supprime de la liste les champions qui sont morts
		list<Character*> newFightingChampions;
		for (auto it = fightingChampions.begin(); it != fightingChampions.end(); it++) {
			if ((*it)->isAlive()) {
				newFightingChampions.push_back(*it);
			}
		}
		fightingChampions = newFightingChampions;

		//On supprime de la liste les Monsters qui sont morts
		list<Character*> newFightingMonsters;
		for (auto it = fightingMonsters.begin(); it != fightingMonsters.end(); it++) {
			if ((*it)->isAlive()) {
				newFightingMonsters.push_back(*it);
			}
		}
		fightingMonsters = newFightingMonsters;

	}

	//Vérification de la victoire
	win = !fightingChampions.empty();

	
	this_thread::sleep_for(std::chrono::seconds(1));
	glutSwapBuffers();
	return win;
}


GLvoid Board::display(){
  // Effacement du frame buffer
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);

  // on charge la matrice identite
  glLoadIdentity();


  //dessin du plateau de jeu
  glColor3f(Param::boardColor[0], Param::boardColor[1], Param::boardColor[2]);

  glBegin(GL_QUADS);

  glVertex3f(0, 0, 0);
  glVertex3f(Param::getBoardDim("x"), 0, 0);
  glVertex3f(Param::getBoardDim("x"), 0, Param::getBoardDim("y"));
  glVertex3f(0, 0, Param::getBoardDim("y"));

  glEnd();
  //dessin des cases


  glColor3f(Param::caseColor[0], Param::caseColor[1], Param::caseColor[2]);
  glBegin(GL_QUADS);
  for (int i=0; i<Param::nbRows; i++){
    for (int j=0; j<Param::nbColumns; j++){
      glVertex3f(j*(Param::dimCase+Param::borderSpacingCase*2)+Param::borderSpacingCase, 0.1f, i*(Param::dimCase+Param::borderSpacingCase*2)+Param::borderSpacingCase);
      glVertex3f((j+1)*(Param::dimCase+Param::borderSpacingCase*2)-Param::borderSpacingCase, 0.1f,i*(Param::dimCase+Param::borderSpacingCase*2)+Param::borderSpacingCase);
      glVertex3f((j+1)*(Param::dimCase+Param::borderSpacingCase*2)-Param::borderSpacingCase, 0.1f, (i+1)*(Param::dimCase+Param::borderSpacingCase*2)-Param::borderSpacingCase);
      glVertex3f(j*(Param::dimCase+Param::borderSpacingCase*2)+Param::borderSpacingCase, 0.1f, (i+1)*(Param::dimCase+Param::borderSpacingCase*2)-Param::borderSpacingCase);
    }
  }
  glEnd();

  
  for (list<Champion*>::iterator it = champions.begin(); it!= champions.end(); it++){
	  (*it)->display();
  }

  for (list<Monster*>::iterator it = monsters.begin(); it!=monsters.end(); it++){
    (*it)->display();
  }

}


list<NodeGraph*> Board::getShorterPath(int i, int j, Character * target) {
	return graph->getShorterPath(graph->getNode(i,j),graph->getNode(target->getI(),target->getJ()));
}