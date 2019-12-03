#include "Game.h"
#include "Board.h"
#include "Param.h"
#include "Champion.h"
#include <GL\glew.h>
#include <GL\freeglut.h>

Game* Game::currentInstance = nullptr;
GLint oldX = 0;
GLint oldY = 0;
GLboolean boutonClick = false;
GLdouble Ax = Param::getBoardDim("x") / 2; //coordonn�es de la cam�ra
GLdouble Ay = 100;
GLdouble Az = -50;

Game::Game(){
  board = new Board();
  currentInstance = this;

  gold = 10; //ATTETION à mettre dans Param
  round = 1;
}

Game::~Game(){
  delete board;
  //delete dungeon;
  delete this;
}

GLvoid Game::display(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  board->display();
  //this->displayHUD();
}

GLvoid Game::displayHUD(){
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0.0f, Param::windowWidth, 0.0f, Param::windowHeight, 1.0f, -1.0f);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glColor3f(1,0,0);
    glBegin(GL_QUADS);
      glVertex3f(0.0f,100.0f,0.0f);
      glVertex3f(0.0f,0.0f,0.0f);
      glVertex3f(100.0f,0.0f,0.0f);
      glVertex3f(100.0f,100.0f,0.0f);
  glEnd();
  glMatrixMode(GL_PROJECTION);
	glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
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

GLvoid souris(int bouton, int etat, int x, int y) {
	// Test pour voir si le bouton gauche de la souris est appuy�
   //TODO
	if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_DOWN) {
		boutonClick = true;
		oldX = x;
		oldY = y;
	}
	// si on relache le bouton gauche
	// TODO
	if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_UP) {
		boutonClick = false;
		oldX = 0;
		oldY = 0;
	}
}

GLvoid deplacementSouris(int x, int y) {
	// si le bouton gauche est appuye et qu'on se deplace
	// alors on doit modifier les angles de rotations du cube
	// en fonction de la derniere position de la souris
	// et de sa position actuelle
	if (boutonClick /*&& test pour voir si x et y correspondent � une partie du HUD*/) {

	}
	else { //si on ne clique pas sur le HUD, on test si on s�lectionne un champion sur le board
		//Projection des coordonn�es de la souris sur le plan du board
		GLdouble Bx, By, Bz; //coordon�es de a souris sur le plan de l'�cran
		GLdouble Mx, My, Mz, t; //point d'intersection du 'rayon' de la souris et du plan du board

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
		float case_i = abs(Mx / (Param::dimCase + 2*Param::borderSpacingCase));
		float case_j = abs(Mz / (Param::dimCase + 2*Param::borderSpacingCase));
		if (0 < case_i && 0 < case_j && case_i < Param::nbColumns && case_j < Param::nbRows) {
			Champion* champ = Board::findChampion(case_i, case_j); //on trouve le champion qui est sur la case qu'on vise
			if (champ != nullptr) {
				champ->dragndrop(x, y);
			}
		}
	}

	// Appeler le re-affichage de la scene OpenGL
	glutPostRedisplay();
}

void Game::run(){

}
