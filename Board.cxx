#include "Board.h"
#include "Param.h"
#include "Game.h"
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
#include "Case.h"

using namespace std;

Board::Board() {
	//Creation d'un Board en lui attribuant des cases
	for (int i = 0; i < Param::nbRows; i++) {
		for (int j = 0; j < Param::nbColumns; j++) {
			cases.push_back(new Case(j, i));
		}
	}
};

list<Race*> Board::getRaces() {
	//Accesseur à la liste des races
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

int Board::count(Race * const race) {
	//
	int count = 0;
	list<string> champNames;
	for (auto it = champions.begin(); it != champions.end(); it++) {
		if ((*it)->getRace(0) == race || (*it)->getRace(1) == race) {
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
	}
	return count;
}

void Board::clearMonsters() {
	//Efface l'ancienne liste de monstres
	monsters.clear();
}

void Board::reinitChampions() {
	//Reinitialise les champions à l'aide de la méthode reset
	int i = 0;
	int j = 0;
	for (auto it = champions.begin(); it != champions.end(); it++) {
		if (i == 9) {
			i = 0;
			j++;
		}
		else {
			i++;
		}
		(*it)->reset(i, j);
	}
}

void Board::applyRaceBonus() {
	//Applique les bonus de races en appelant la méthode
	//addBonus pour chaque champion concerné
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

void Board::removeChampion(list<Champion*>::iterator it) {
	//Retire un champions du board
	//ATTENTION : ça peut delete l'objet sur lequel pointe le pointeur
	Game::garbageChampions.push_back(*it);
	champions.erase(it);
}

void Board::addChampion(Champion * champion) {
	//Ajoute un champion sur le board

	//On compte le nombre de champion du même type sur le board
	int count = 0;
	list<list<Champion*>::iterator> listIteratorToDelete;
	if (champion->getLevel() != Param::levelMax) {
		for (auto it = champions.begin(); it != champions.end(); it++) {
			cout << (*it)->getLevel() << endl;
			cout << champion->getLevel() << endl;
			if ((*it)->getName() == champion->getName() && (*it)->getLevel() == champion->getLevel()) {
				count++;
				listIteratorToDelete.push_back(it);
			}
		}
	}

	//Ajout des nouveaux champions sur le board à un emplacement vide
	Champion * newChampion = new Champion(champion);
	int i = newChampion->getI();
	int j = newChampion->getJ();
	while (findChampion(i, j) != nullptr) {
		if (i == 9) {
			i = 0;
			j++;
		}
		else {
			i++;
		}
	}

	//Si on a déjà deux champions du même type sur le board alors on delete les champions sur le board et on evolve le nouveau
	if (count == 2) {
		for (auto it = listIteratorToDelete.begin(); it != listIteratorToDelete.end(); it++) {
			this->removeChampion(*it);
		}
		newChampion->evolve();
		addChampion(newChampion);
	}
	else {
		newChampion->setIJ(i, j);
		champions.push_back(newChampion);
	}
}

Champion* Board::findChampion(int _i, int _j) {
	//Cherche si un champion se trouve sur case d'indices pris en arguments
	//et retourne un pointeur vers celui-ci si c'est le cas
	Champion* champ = nullptr;
	for (list<Champion*>::iterator itr = champions.begin(); itr != champions.end(); itr++) {
		if ((*itr)->getI() == _i && (*itr)->getJ() == _j) {
			champ = (*itr);
		}
	}
	return champ;
}

Character* Board::findCharacter(int _i, int _j) {
	//Cherche si un character se trouve sur case d'indices pris en arguments
	//et retourne un pointeur vers celui-ci si c'est le cas
	Character * c = (Character*)findChampion(_i, _j);

	if (c == nullptr) {
		Monster* m = nullptr;
		for (list<Monster*>::iterator itr = monsters.begin(); itr != monsters.end(); itr++) {
			if ((*itr)->getI() == _i && (*itr)->getJ() == _j && (*itr)->isAlive()) {
				m = (*itr);
			}
		}

		c = (Character*)m;
	}
	else {
		if (c->isAlive() == false) {
			c = nullptr;
		}
	}

	return c;
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

	
	glutSwapBuffers();
	return win;
}


GLvoid Board::display(){
	//Affiche un board en affichant d'abord le plateau puis les cases
	//une par une en appelant leur fonction d'affichage
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

  glVertex3f(0, 0, 0);
  glVertex3f(Param::getBoardDim("x"), 0, 0);
  glVertex3f(Param::getBoardDim("x"), -10, 0);
  glVertex3f(0, -10, 0);
  

  glEnd();
  //dessin des cases


  for (auto it = cases.begin(); it != cases.end(); it++) {
	  (*it)->display();
  }

  
  for (list<Champion*>::iterator it = champions.begin(); it!= champions.end(); it++){
	  (*it)->display();
  }

  for (list<Monster*>::iterator it = monsters.begin(); it!=monsters.end(); it++){
    (*it)->display();
  }

}

void Board::setColorCase(int i, int j, float c1, float c2, float c3) {
	cases.at(i*Param::nbColumns + j)->setColor(c1, c2, c3);
};


list<NodeGraph*> Board::getShorterPath(int i, int j, Character * target) {
	return graph->getShorterPath(graph->getNode(i,j),graph->getNode(target->getI(),target->getJ()));
}
