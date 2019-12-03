#include <GL\glew.h>
#include <GL\freeglut.h>
#include "Board.h"
#include <list>

class Game{
private:
  static Game* currentInstance;
  Board *board;

  int round;
  int gold;

  //Dungeon *dungeon;
  std::list<Champion> champions; //On ne veut pas modifier les champions piochés

  GLvoid display();
  GLvoid displayHUD();

public:
  static GLvoid displayCallBack();
  static GLvoid reshape(int w, int h);
  static void clavier(unsigned char key, int xx, int yy);
	static GLvoid souris(int bouton, int etat, int x, int y);
  void run();

  //Constructeur
  Game();

  //Destructeur
  ~Game();
};
