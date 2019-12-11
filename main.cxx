#include "Game.h"
#include "Param.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <string>
#include <thread>
using namespace std;

void run(Game * game) {
	game->run();
}


int main(int argc, char** argv){
  Game * game = new Game();
  
  thread v(run, game);

  // Initialisation de GLUT
  glutInit(&argc, argv);
  // Choix du mode d'affichage (ici RVB)
  //glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

  // Position initiale de la fenetre GLUT
  glutInitWindowPosition(Param::windowPositionInitial[0], Param::windowPositionInitial[1]);
  // Taille initiale de la fenetre GLUT
  glutInitWindowSize(Param::windowWidth, Param::windowHeight);
  // Creation de la fenetre GLUT
  glutCreateWindow("Chess Quest");

  //
  glEnable(GL_DEPTH_TEST);

  // D�finition de la couleur d'effacement du framebuffer
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  glutDisplayFunc(Game::displayCallBack);
  glutReshapeFunc(Game::reshape);
  glutIdleFunc(Game::displayCallBack);

  // pour que l'on puisse rester appuye sur les touches
  glutIgnoreKeyRepeat(1);

  // Declaration des callbacks clavier
  glutKeyboardFunc(Game::clavier);
  // Nouveaux callbacks
  glutMouseFunc(Game::souris);
  glutMotionFunc(Game::deplacementSouris);

  glutMainLoop();

  delete game;

  return 1;
}



