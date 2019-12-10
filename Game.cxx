#include "Game.h"
#include "Board.h"
#include "Param.h"
#include "Champion.h"
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <string>
#include <list>
#include <iterator>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;


Game* Game::currentInstance = nullptr;

GLboolean Game::boutonClick = false;
GLint Game::oldX = -1;
GLint Game::oldY = -1;
GLboolean Game::championDrag = false;
GLdouble Game::Ax = Param::getBoardDim("x") / 2; //coordonn�es de la cam�ra
GLdouble Game::Ay = 100;
GLdouble Game::Az = -50;

Game::Game(){
  board = new Board();
  currentInstance = this;
}

Game::~Game(){
  delete board;
  //delete dungeon;
  delete this;
}

GLvoid Game::display(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  board->display();
  this->displayHUD();
  this->displayCards();
  this->displayInfo();
  glutSwapBuffers();
}

GLvoid Game::drawText(float x, float y, int length, const char *text){
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0.0f, Param::windowWidth, 0.0f, Param::windowHeight);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
   glColor3f(1.0f, 1.0f, 1.0f);
  glRasterPos2f(x, y);
  for (int i = 0; i<length; i++) {
      glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
  }
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}

GLvoid Game::displayCards(){
	
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0.0f, Param::windowWidth, 0.0f, Param::windowHeight);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  glDisable(GL_DEPTH_TEST);			// à enlever puis remettre pour afficher le texte par dessus la carte

  list<Champion*>::iterator it = championCards.begin();
  for (int k = 0; k < 5; k++) { //affichage des 5 cartes de champion
	  if ((*it) != nullptr) {
		  glColor3f(0.8f, 0.8f, 0.8f);
		  glBegin(GL_QUADS);					//affichage de la carte
		  glVertex2f(50.0f + k * 170, 250.0f);
		  glVertex2f(50.0f + k * 170, 50.0f);
		  glVertex2f(200.0f + k * 170, 50.0f);
		  glVertex2f(200.0f + k * 170, 250.0f);
		  glEnd();

		  glColor3f(0.0f, 0.0f, 0.0f);
		  string cardText = (*it)->getName();				//affichage du texte de la carte
		  glRasterPos2f(65.0f + k * 170, 200.0f);
		  for (int i = 0; i < cardText.size(); i++) {
			  glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)cardText.data()[i]);
		  }
	  }
	  advance(it, 1);
  }

  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  
}

GLvoid Game::displayInfo() {
	std::string goldText = "Gold : ";
	goldText += std::to_string(getGold());
	drawText(50.0f, 900.0f, goldText.size(), goldText.data());
	std::string roundText = "Round : ";
	roundText += std::to_string(getRound());
	this->drawText(50.0f, 930.0f, roundText.size(), roundText.data());
}

GLvoid Game::displayHUD(){
  displayInfo();
  displayCards();
}

GLvoid Game::displayCallBack(){
  currentInstance->display();
}

GLvoid Game::reshape(int w, int h){
  // On evite une division par 0
   // la fenetre ne peut avoir une largeur de 0
   if (h == 0)
      h = 1;

   // Calcul du ratio
   float ratio =  (w * 1.0) / h;

   // On passe en mode "matrice de projection"
   glMatrixMode(GL_PROJECTION);

   // on charge la matrice identite
   glLoadIdentity();

   // on definit le viewport pour prendre toute la fenetre
   glViewport(0, 0, w, h);

   // on definit la projection perspective
   gluPerspective(65.0f, ratio, 0.1f, 1000.0f);

   // on definit la position de la camera et ou elle regarde
   gluLookAt(Ax, Ay, Az,
 		Param::getBoardDim("x")/2, 0, Param::getBoardDim("y")/4,
 		0, 1, 0);


   // on repasse en mode "matrice modelview"
   glMatrixMode(GL_MODELVIEW);
}

void Game::clavier(unsigned char key, int xx, int yy){
  switch(key){
    case 27 :
    exit (0);
    break;
  }
}

GLvoid Game::souris(int bouton, int etat, int x, int y) {
	// Test pour voir si le bouton gauche de la souris est appuy�
   //TODO
	if (bouton == GLUT_LEFT_BUTTON) {
    if (etat == GLUT_DOWN){
      boutonClick = true;
  		oldX = x;
  		oldY = y;
    }
    else { //if (etat == GLUT_UP)
      // si on relache le bouton gauche
      // TODO
  		boutonClick = false;
  		oldX = -1;
  		oldY = -1;
  	}
	}
}

GLvoid Game::deplacementSouris(int x, int y) {
	// si le bouton gauche est appuye et qu'on se deplace
	// alors on doit modifier les angles de rotations du cube
	// en fonction de la derniere position de la souris
	// et de sa position actuelle
	if (boutonClick && y > 643) {  //&& test pour voir si x et y correspondent à une partie du HUD
					//643 c'est une valeur prise empiriquement en étudiant la position de la souris
		int selec = currentInstance -> selectionCards(x, y);
		if (selec >= 0) {
			list<Champion*>::iterator itr = currentInstance->championCards.begin();
			advance(itr, selec);
			if ((*itr) != nullptr) {
				currentInstance->board->addChampion(*itr);
				(*itr) = nullptr;
			}
		}
	}
	/*else if (boutonClick){ //si on ne clique pas sur le HUD, on test si on sélectionne un champion sur le board
		//Projection des coordonnées de la souris sur le plan du board
		GLdouble Bx, By, Bz; //coordon�es de a souris sur le plan de l'écran
		GLdouble Mx, My, Mz, t; //point d'intersection du 'rayon' de la souris et du plan du board
    Bx = x;
		GLint viewport[4];
		GLdouble mvmatrix[16], projmatrix[16];
		glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
		glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);
		glGetIntegerv(GL_VIEWPORT, viewport);
		gluUnProject(x, viewport[3] - y, 0, mvmatrix, projmatrix, viewport, &Bx, &By, &Bz); // ici x et y sont les coordonn�es de ma souris captur�es avec SDL

		t = -Ay / (By - Ay); // on calcule t en fonction de la position de la camera(Az) et de (Bz)
		Mx = t * (Bx - Ax) + Ax; //on calcule les positions de M  avec t
		My = 0;
		Mz = t * (Bz - Az) + Az;
		int case_i = (int)(Mx / (Param::dimCase + 2*Param::borderSpacingCase));
		int case_j = (int)(Mz / (Param::dimCase + 2*Param::borderSpacingCase));
    Champion* champ = board->findChampion(case_i, case_j); //on trouve le champion qui est sur la case qu'on vise
    if (!championDrag){
      if (0 < case_i && 0 < case_j && case_i < Param::nbColumns && case_j < Param::nbRows) {
    		if (champ != nullptr) {
    			champ->dragndrop(x, y);
          championDrag = true;
          glutPostRedisplay();
    		}
      }
    }

      else{

      }
	}

	// Appeler le re-affichage de la scene OpenGL
	glutPostRedisplay();
*/}

void Game::initChampions(){
	champions.push_back(new Champion("PE", 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0));
	champions.push_back(new Champion("Thomas", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
}

void Game::setCards() {
	list<Champion*>::iterator it;
	srand(time(NULL));
	int r;
	for (int k = 0; k < 5; k++) {
		r = rand() % 2;
		it = champions.begin();
		advance(it, r);
		championCards.push_back(*it);
	}
}

int Game::selectionCards(int x, int y) {
	int k = -1;
	if (x > 50 && y < 843) {
		int i = (int)((x - 50) / 170);		//indice de la carte
		int j = x - 50 - i * 170;		//permet de vérifier si on est sur la carte ou à coté
		if (j < 150) {
			k = i;
		}
	}
	return k;
}

void Game::run(){

}
