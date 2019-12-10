#include <GL\glew.h>
#include <GL\freeglut.h>
#include "Board.h"
#include "Param.h"
#include <list>

class Game{
private:
  static Game* currentInstance;
  Board *board;

  int round;
  int gold;

  static GLboolean boutonClick;
  static GLint oldX;
  static GLint oldY;
  static GLboolean championDrag;
  static GLdouble Ax;
  static GLdouble Ay;
  static GLdouble Az;
  //Dungeon *dungeon;
  std::list<Champion> champions; //On ne veut pas modifier les champions piochés
  std::list<Champion*> championCards; //Liste des 5 cartes affichées

  GLvoid display();
  GLvoid displayHUD();
  GLvoid displayCards();
  GLvoid displayInfo();
  GLvoid drawText(float x, float y, int length, const char *text);

public:
    static GLvoid displayCallBack();
    static GLvoid reshape(int w, int h);
    static void clavier(unsigned char key, int xx, int yy);
	  static GLvoid souris(int bouton, int etat, int x, int y);
    static GLvoid deplacementSouris(int x, int y);
	
	
    void initChampions();
    void setCards();
    int selectionCards(int x, int y);
	
    void run();

    int getGold() { return gold; };
    int getRound() { return round; };
	
    //Constructeur
    Game();

    //Destructeur
    ~Game();
};
