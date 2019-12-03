#include "Board.h"
#include "Param.h"
#include "Champion.h"
#include <list>
#include <iterator>
#include <GL\glew.h>
#include <GL\freeglut.h>
using namespace std;


Board::Board(){
  champions.push_back(new Champion("PE",0,0,0,0,0,0,0,5,5,0,0,0));
  champions.push_back(new Champion("PE",0,0,0,0,0,0,0,5,6,0,0,0));
  champions.push_back(new Champion("PE",0,0,0,0,0,0,0,1,2,0,0,0));
  champions.push_back(new Champion("PE",0,0,0,0,0,0,0,9,3,0,0,0));
}

void Board::resetMonsters(){

}

void Board::addChampion(Champion * champion){

}

void Board::removeChampion(int indice){

}

Champion* Board::findChampion(int _i, int _j) {
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
  list<Champion*> fightingChampions = new list<Champion*>(champions);
  list<Monster*> fightingMonsters = new list<Monster*>(monsters);

  while(fightingChampions.isEmpty() == false && fightingMonster.isEmpty() == false){
    //Tant que l'un des camps n'est pas décédé on les fait se combattre

    for(list<Champion*>::iterator it = fightingChampions.begin(); it != fightingChampions.end(); it++){
      (*it)->fight(fightingChampions,fightingMonsters);
    }

    for(list<Monster*>::iterator it = fightingMonsters.begin(); it != fightingMonsters.end(); it++){
      (*it)->fight(fightingMonsters,fightingChampions);
    }

    //On supprime de la liste les champions qui sont morts
    list<Champion*> newFightingChampions = new list<Champion*>();
    for(list<Champion*>::iterator it = fightingChampions.begin(); it != fightingChampions.end(); it++){
      if((*it)->isAlive() == false){
        newFightingChampions.push_back(*it);
      }
    }
    fightingChampions = newFightingChampions;

    //On supprime de la liste les Monsters qui sont morts
    list<Monster*> newFightingMonsters = new list<Monster*>();
    for(list<Monster*>::iterator it = fightingMonsters.begin(); it != fightingMonsters.end(); it++){
      if((*it)->isAlive() == false){
        newFightingMonsters.push_back(*it);
      }
    }
    fightingMonsters = newFightingMonsters;
  }

  //Vérification de la victoire
  win = !fightingChampions.isEmpty();

  //ATTENTION : gestion du gain ici ou ailleurs ?

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

  for (list<Champion*>::iterator it = champions.begin(); it!=champions.end(); it++){
    (*it)->display();
  }

  glutSwapBuffers();
}




void Board::removeChampion(int indice){
    
}
