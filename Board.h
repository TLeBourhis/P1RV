#include <list>
#include "Champion.h"
#include "Monster.h"
#include <GL\glew.h>
#include <GL\freeglut.h>
#ifndef BOARD_H
#define BOARD_H

class Board{
private:
  std::list<Champion*> champions;
  std::list<Monster*> monsters;
  //std::list<Monster> monsters;

public:
  void resetMonsters();
  void addChampion(Champion * champion);
  void removeChampion(int indice);
  Champion* findChampion(int _i, int _j);
  bool fight();
  GLvoid display();

  //constructeurs
  Board(); //prend en arguments des bails de la classe Paramètres

  //Destructeurs


  //Accesseurs

};


#endif /* end of include guard: BOARD_H */
