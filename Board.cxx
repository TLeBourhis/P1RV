#include "Board.h"
#include "Param.h"
#include "Champion.h"
#include "Monster.h"
#include <list>
#include <iterator>
#include <GL\glew.h>
#include <GL\freeglut.h>
using namespace std;


Board::Board(){
  monsters.push_back(new Monster("Esteban",0,0,0,0,0,0,0,5,8,0,0,0));
}

void Board::resetMonsters(){

}

void Board::addChampion(Champion * champion){
  champions.push_back(champion);
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
  return true;
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

  for (list<Monster*>::iterator it = monsters.begin(); it!=monsters.end(); it++){
    (*it)->display();
  }
}
