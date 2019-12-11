#pragma once 

#include <list>
#include "Champion.h"
#include "Monster.h"
#include "Graph.h"
#include "Race.h"
#include <GL\glew.h>
#include <GL\freeglut.h>






class Board{
private:
  Graph *graph;
  std::list<Champion*> champions;
  std::list<Monster*> monsters;

public:
  void clearMonsters();
  void setMonsters(int round);
  void addChampion(Champion * champion);
  void removeChampion(int indice);
  Champion* findChampion(int _i, int _j);
  bool fight();
  GLvoid display();
  void initGraph() {graph = new Graph();};
  std::list<NodeGraph*> getShorterPath(int i, int j, Character * c);
  void reinitChampions();
  std::list<Race*> getRaces();
  int count(Race * race);


  //constructeurs
  Board(); //prend en arguments des bails de la classe Paramètres

  //Destructeurs


  //Accesseurs

};

