#pragma once


#include <GL\glew.h>
#include <GL\freeglut.h>
#include "Board.h"
#include "Param.h"
#include <list>
#include <iostream>

class Game {
private:
	Board *board;

	int round;
	int gold;

	bool endGame;
	bool readyToFight;

	static GLboolean boutonClick;
	static GLint oldX;
	static GLint oldY;
	static GLboolean championDrag;
	static Champion* champTargeted;
	static GLdouble Ax;
	static GLdouble Ay;
	static GLdouble Az;
	//Dungeon *dungeon;
	//std::list<Champion*> champions; //On ne veut pas modifier les champions piochés
	std::list<Champion*> championCards;


	GLvoid display();
	GLvoid displayHUD();
	GLvoid displayCards();
	GLvoid displayInfo();
	GLvoid displayRaces();
	GLvoid displayButtons();
	GLvoid drawText(float x, float y, int length, const char *text, float colorR, float colorV, float colorB);

public:
	static Game* currentInstance;
	static GLvoid displayCallBack();
	static GLvoid reshape(int w, int h);
	static void clavier(unsigned char key, int xx, int yy);
	static GLvoid souris(int bouton, int etat, int x, int y);
	static GLvoid deplacementSouris(int x, int y);
	Board * getBoard() {return board;};
	void run();

	void setReadyToFight(bool b) {readyToFight = b;};

	void setCards();
	int selectionCards(int x, int y);

	int getGold() { return gold; };
	int getRound() { return round; };
	void addGold(int g) { gold += g; };

	//Constructeur
	Game();

	//Destructeur
	~Game();
};