// ChessQuest.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>

#include "Game.h"
#include "Param.h"
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <string>
using namespace std;



int main(int argc, char** argv) {
	Game * game = new Game();

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

	glutMainLoop();

	delete game;

	return 1;
}


// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Conseils pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
