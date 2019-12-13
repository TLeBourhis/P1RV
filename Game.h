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
	bool help;
	bool victory;

	static GLboolean boutonClick;
	static GLint oldX;
	static GLint oldY;
	static GLboolean championDrag;
	static Champion* champTargeted;
	static GLdouble Ax;
	static GLdouble Ay;
	static GLdouble Az;
	//Dungeon *dungeon;
	std::list<Champion*> championCards;


	GLvoid display();
	GLvoid displayHUD();
	GLvoid displayCards();
	GLvoid displayInfo();
	GLvoid displayRaces();
	GLvoid displayHelp();
	GLvoid displayGameOver();
	GLvoid drawText(float x, float y, int length, const char *text, float colorR, float colorV, float colorB);
	GLvoid displayButtons();

public:
	static Game* currentInstance;
	static std::list<Champion*> garbageChampions;
	static void cleanGarbage();
 	static GLvoid displayCallBack();
	static GLvoid reshape(int w, int h);
	static void clavier(unsigned char key, int xx, int yy);
	static GLvoid souris(int bouton, int etat, int x, int y);
	static GLvoid deplacementSouris(int x, int y);
	Board * getBoard() {return board;};
	void run();

	void setReadyToFight(bool b) {readyToFight = b;};
	bool getReadyToFight() { return readyToFight; };
	void setDisplayHelp(bool b) { help = b; };
	bool getDisplayHelp() { return help; };
	bool getVictory() { return victory; };

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